#include "truthtable_detail.hpp"

#include "boolean.hpp"
#include "truthtable.hpp"

#include <cstddef>
#include <iterator>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/iterator/transform_iterator.hpp>


namespace propositions::truthtable_detail {

    template<class Container,
        std::enable_if_t<std::is_same_v<typename Container::value_type, truth_table_input>, int>>
    input_combination_generator::input_combination_generator(Container const& inputs) :
        _values(std::size(inputs))
    {
        _sets.reserve(std::size(inputs));
        for (auto const& input : inputs) {
            _sets.push_back(input.values());
        }

        _iterators.reserve(std::size(inputs));
        for (auto const& set : _sets) {
            _iterators.push_back(set.begin());
        }

        _done = size() == 0;
    }


    inline auto join_input_generator::operator()(std::vector<std::size_t> const& indices) const
    {
        boost::transform_iterator begin(indices.cbegin(), _single_input_gen);
        boost::transform_iterator end(indices.cend(), _single_input_gen);
        return std::pair{begin, end};
    }


    template<class BoostTuple>
    boolean_value join_output_generator::operator()(BoostTuple const& table_and_input_values) const
    {
        auto const& table = table_and_input_values.get<0>();
        auto const& input_values = table_and_input_values.get<1>();
        return table[input_values];
    }

}
