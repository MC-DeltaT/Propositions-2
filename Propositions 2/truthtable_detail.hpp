#pragma once

#include "boolean.hpp"
#include "truthtable.hpp"

#include <cstddef>
#include <type_traits>
#include <vector>


namespace truthtable::detail {

    class value_combination_generator {
    public:
        template<class Container,
            std::enable_if_t<std::is_same_v<typename Container::value_type, boolean::value_set>, int> = 0>
        explicit value_combination_generator(Container const& value_sets);

        template<class Container,
            std::enable_if_t<std::is_same_v<typename Container::value_type, input_variable>, int> = 0>
        explicit value_combination_generator(Container const& inputs);

        std::size_t size() const;
        bool done() const;
        std::vector<boolean::boolean_value> const& next();

    private:
        bool _done;
        std::vector<boolean::value_set::iterator> _iterators;
        std::vector<boolean::value_set> _sets;
        std::vector<boolean::boolean_value> _values;
    };

}


#include "truthtable_detail.tpp"
