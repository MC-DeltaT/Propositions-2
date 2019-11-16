#pragma once

#include "expression.hpp"
#include "truthtable.hpp"

#include <memory>
#include <string>


namespace propositions::operation_detail {

    template<class Operation>
    struct operation_property_accessor : private Operation {
        using Operation::_join;
        using Operation::_symbol;
    };


    template<class Operation>
    truth_table const& get_join();
    template<class Operation>
    std::string const& get_symbol();


    template<class Operation, class Base>
    class unary_operation_helper : public Base {
    public:
        unary_operation_helper(std::unique_ptr<expression> rhs);
    };

}


#include "operation_detail.tpp"
