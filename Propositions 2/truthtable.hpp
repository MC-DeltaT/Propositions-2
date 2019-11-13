#pragma once

#include "boolean.hpp"

#include <cstddef>
#include <string>
#include <utility>
#include <vector>


namespace truthtable {

    class input_variable {
    public:
        input_variable(std::string label = std::string(), boolean::value_set values = boolean::all_values);

        std::string const& label() const;
        boolean::value_set const& values() const;

    private:
        std::string _label;
        boolean::value_set _values;
    };

    bool operator==(input_variable const& lhs, input_variable const& rhs);


    class truth_table {
    public:
        using table_type = std::vector<std::pair<std::vector<boolean::boolean_value>, boolean::boolean_value>>;

        truth_table(std::vector<input_variable> inputs, table_type table);

        std::vector<input_variable> const& inputs() const;
        table_type const& table() const;

        boolean::boolean_value const& operator[](std::vector<boolean::boolean_value> const& inputs) const;
        template<typename InputIterator>
        boolean::boolean_value const& operator[](std::pair<InputIterator, InputIterator> inputs) const;

    private:
        std::vector<input_variable> _inputs;
        table_type _table;
    };

    truth_table join_tables(truth_table const& join_op, std::vector<truth_table> const& tables);

}


#include "truthtable.tpp"
