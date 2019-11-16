#pragma once

#include "boolean.hpp"

#include <cstddef>
#include <string>
#include <utility>
#include <vector>


namespace propositions {

    class truth_table_input {
    public:
        truth_table_input(std::string label = std::string(), boolean_value_set values = all_booleans);

        std::string const& label() const;
        boolean_value_set const& values() const;

    private:
        std::string _label;
        boolean_value_set _values;
    };

    bool operator==(truth_table_input const& lhs, truth_table_input const& rhs);


    class truth_table {
    public:
        using table_type = std::vector<std::pair<std::vector<boolean_value>, boolean_value>>;

        truth_table(std::vector<truth_table_input> inputs, table_type table);

        std::vector<truth_table_input> const& inputs() const;
        boolean_value_set outputs() const;
        table_type const& table() const;

        boolean_value const& operator[](std::vector<boolean_value> const& inputs) const;
        template<typename InputIterator>
        boolean_value const& operator[](std::pair<InputIterator, InputIterator> inputs) const;

    private:
        std::vector<truth_table_input> _inputs;
        table_type _table;
    };

    truth_table join_tables(truth_table const& join_op, std::vector<truth_table> const& tables);

}


#include "truthtable.tpp"
