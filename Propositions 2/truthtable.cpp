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


namespace propositions {

    truth_table_input::truth_table_input(std::string label, boolean_value_set values) :
        _label(label),
        _values(values)
    {}

    std::string const& truth_table_input::label() const
    {
        return _label;
    }

    boolean_value_set const& truth_table_input::values() const
    {
        return _values;
    }

    bool operator==(truth_table_input const& lhs, truth_table_input const& rhs)
    {
        return lhs.label() == rhs.label();
    }


    truth_table::truth_table(std::vector<truth_table_input> inputs, table_type table) :
        _inputs(inputs),
        _table(table)
    {}

    std::vector<truth_table_input> const& truth_table::inputs() const
    {
        return _inputs;
    }

    truth_table::table_type const& truth_table::table() const
    {
        return _table;
    }

    boolean_value const& truth_table::operator[](std::vector<boolean_value> const& inputs) const
    {
        return (*this)[std::pair{inputs.cbegin(), inputs.cend()}];
    }


    truth_table join_tables(truth_table const& join_op, std::vector<truth_table> const& tables)
    {
        std::vector<std::reference_wrapper<std::vector<truth_table_input> const>> inputs;
        inputs.reserve(tables.size());
        for (auto const& table : tables) {
            inputs.emplace_back(table.inputs());
        }

        std::vector<std::vector<std::size_t>> input_indices(inputs.size());

        std::vector<truth_table_input> result_inputs;
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

        truthtable_detail::input_combination_generator input_combinations(result_inputs);

        truth_table::table_type result_table;
        result_table.reserve(input_combinations.size());

        while (!input_combinations.done()) {
            auto const& new_input_values = input_combinations.next();

            truthtable_detail::join_input_generator input_generator{&new_input_values};
            boost::transform_iterator base_input_begin(input_indices.cbegin(), input_generator);
            boost::transform_iterator base_input_end(input_indices.cend(), input_generator);

            boost::zip_iterator table_and_input_begin(boost::make_tuple(tables.cbegin(), base_input_begin));
            boost::zip_iterator table_and_input_end(boost::make_tuple(tables.cend(), base_input_end));

            truthtable_detail::join_output_generator output_generator;
            boost::transform_iterator base_output_begin(table_and_input_begin, output_generator);
            boost::transform_iterator base_output_end(table_and_input_end, output_generator);

            auto const new_output = join_op[std::pair{base_output_begin, base_output_end}];
            result_table.emplace_back(new_input_values, new_output);
        }

        return truth_table(std::move(result_inputs), std::move(result_table));
    }

}
