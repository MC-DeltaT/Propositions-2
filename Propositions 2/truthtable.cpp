#include "truthtable.hpp"

#include "boolean.hpp"
#include "truthtable_detail.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <string>
#include <utility>
#include <vector>

#include <boost/iterator/transform_iterator.hpp>
#include <boost/iterator/zip_iterator.hpp>
#include <boost/tuple/tuple.hpp>


namespace truthtable {

    input_variable::input_variable(std::string label, boolean::value_set values) :
        _label(label),
        _values(values)
    {}

    std::string const& input_variable::label() const
    {
        return _label;
    }

    boolean::value_set const& input_variable::values() const
    {
        return _values;
    }

    bool operator==(input_variable const& lhs, input_variable const& rhs)
    {
        return lhs.label() == rhs.label();
    }


    truth_table::truth_table(std::vector<input_variable> inputs, table_type table) :
        _inputs(inputs),
        _table(table)
    {}

    std::vector<input_variable> const& truth_table::inputs() const
    {
        return _inputs;
    }

    truth_table::table_type const& truth_table::table() const
    {
        return _table;
    }

    boolean::boolean_value const& truth_table::operator[](std::vector<boolean::boolean_value> const& inputs) const
    {
        return (*this)[std::pair{inputs.cbegin(), inputs.cend()}];
    }


    truth_table join_tables(truth_table const& join_op, std::vector<truth_table> const& tables)
    {
        std::vector<std::reference_wrapper<std::vector<input_variable> const>> inputs;
        inputs.reserve(tables.size());
        for (auto const& table : tables) {
            inputs.emplace_back(table.inputs());
        }

        std::vector<std::vector<std::size_t>> input_indices(inputs.size());

        std::vector<input_variable> result_inputs;
        result_inputs.reserve(inputs.size());

        for (std::size_t i = 0; i < inputs.size(); ++i) {
            for (auto const& input : inputs[i].get()) {
                auto const it = std::find(result_inputs.cbegin(), result_inputs.cend(), input);
                if (it == result_inputs.cend()) {
                    result_inputs.push_back(input);
                    input_indices[i].push_back(result_inputs.size() - 1);
                }
                else {
                    input_indices[i].push_back(it - result_inputs.cbegin());
                }
            }
        }

        detail::value_combination_generator value_combinations(result_inputs);

        using base_input_iterator_t = boost::transform_iterator<detail::join_input_generator, decltype(input_indices)::value_type::const_iterator>;
        std::vector<std::pair<base_input_iterator_t, base_input_iterator_t>> base_input_values(tables.size());

        truth_table::table_type result_table;
        result_table.reserve(value_combinations.size());

        while (!value_combinations.done()) {
            auto const& new_input_values = value_combinations.next();
            
            for (std::size_t i = 0; i < input_indices.size(); ++i) {
                base_input_iterator_t begin(input_indices[i].cbegin(), detail::join_input_generator{&new_input_values});
                base_input_iterator_t end(input_indices[i].cend(), detail::join_input_generator{&new_input_values});
                base_input_values[i] = {begin, end};
            }

            boost::zip_iterator table_and_input_begin(boost::make_tuple(tables.cbegin(), base_input_values.cbegin()));
            boost::zip_iterator table_and_input_end(boost::make_tuple(tables.cend(), base_input_values.cend()));
            boost::transform_iterator base_output_begin(table_and_input_begin, detail::join_output_generator{});
            boost::transform_iterator base_output_end(table_and_input_end, detail::join_output_generator{});

            auto const new_output = join_op[std::pair{base_output_begin, base_output_end}];
            result_table.emplace_back(new_input_values, new_output);
        }

        std::vector<boolean::boolean_value> base_outputs(tables.size());

        return truth_table(std::move(result_inputs), std::move(result_table));
    }

}
