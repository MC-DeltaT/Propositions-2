#include "operation_detail.hpp"

#include "expression.hpp"
#include "truthtable.hpp"

#include <memory>
#include <string>
#include <utility>


namespace propositions::operation_detail {

    template<class Operation>
    truth_table const& get_join()
    {
        return operation_property_accessor<Operation>::_join;
    }

    template<class Operation>
    std::string const& get_symbol()
    {
        return operation_property_accessor<Operation>::_symbol;
    }


    template<class Operation, class Base>
    unary_operation_helper<Operation, Base>::unary_operation_helper(std::unique_ptr<expression> rhs) :
        Base(std::move(rhs), &get_join<Operation>(), join_tables(get_join<Operation>(), {rhs->truth()}), get_symbol<Operation>())
    {}

}
