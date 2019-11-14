#include "truthtable_detail.hpp"

#include "boolean.hpp"
#include "truthtable.hpp"

#include <iterator>
#include <type_traits>


namespace truthtable::detail {

    template<class Container,
        std::enable_if_t<std::is_same_v<typename Container::value_type, boolean::value_set>, int>>
    value_combination_generator::value_combination_generator(Container const& value_sets) :
        _sets(std::cbegin(value_sets), std::cend(value_sets)),
        _values(std::size(value_sets))
    {
        _iterators.reserve(std::size(value_sets));
        for (auto const& set : _sets) {
            _iterators.push_back(set.begin());
        }

        _done = size() == 0;
    }

    template<class Container,
        std::enable_if_t<std::is_same_v<typename Container::value_type, input_variable>, int>>
    value_combination_generator::value_combination_generator(Container const& inputs) :
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


    template<class BoostTuple>
    decltype(auto) join_output_generator::operator()(BoostTuple const& table_and_input_values) const
    {
        auto const& table = table_and_input_values.get<0>();
        auto const& input_values = table_and_input_values.get<1>();
        return table[input_values];
    }

}
