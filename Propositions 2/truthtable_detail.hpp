#pragma once

#include "boolean.hpp"
#include "truthtable.hpp"

#include <cstddef>
#include <type_traits>
#include <vector>


namespace propositions::truthtable_detail {

    class input_combination_generator {
    public:
        template<class Container,
            std::enable_if_t<std::is_same_v<typename Container::value_type, truth_table_input>, int> = 0>
        explicit input_combination_generator(Container const& inputs);

        std::size_t size() const;
        bool done() const;
        std::vector<boolean_value> const& next();

    private:
        bool _done;
        std::vector<boolean_value_set::iterator> _iterators;
        std::vector<boolean_value_set> _sets;
        std::vector<boolean_value> _values;
    };


    class join_input_generator {
    public:
        join_input_generator(std::vector<boolean_value> const* new_input_values);

        inline auto operator()(std::vector<std::size_t> const& indices) const;

    private:
        struct single_input_generator {
            std::vector<boolean_value> const* new_input_values = nullptr;

            boolean_value operator()(std::size_t index) const;
        };

        single_input_generator _single_input_gen;
    };


    struct join_output_generator {
        template<class BoostTuple>
        boolean_value operator()(BoostTuple const& table_and_input_values) const;
    };

}


#include "truthtable_detail.tpp"
