#include "operation.hpp"

#include "expression.hpp"
#include "truthtable.hpp"

#include <memory>
#include <string>
#include <utility>


namespace propositions {

    truth_table const& unary_operation::join() const
    {
        return *_join;
    }
    expression const& unary_operation::rhs() const
    {
        return *_rhs;
    }

    std::string const& unary_operation::symbol() const
    {
        return _symbol;
    }

    std::string unary_operation::to_string() const
    {
        auto str = symbol() + _rhs->to_string();
        if (!dynamic_cast<simple_expression const*>(_rhs.get()) && !dynamic_cast<unary_operation const*>(_rhs.get())) {
            str = "(" + str + ")";
        }
        return str;
    }

    truth_table const& unary_operation::truth() const
    {
        return _truth;
    }

    unary_operation::unary_operation(std::unique_ptr<expression> rhs, truth_table const* join, truth_table truth, std::string symbol) :
        _join(join),
        _rhs(std::move(rhs)),
        _truth(truth),
        _symbol(symbol)
    {}


    truth_table const identity::_join({{"rhs"}}, {
            {{F}, F},
            {{T}, T},
        });

    std::string const identity::_symbol = "";


    truth_table const negation::_join({{"rhs"}}, {
            {{F}, T},
            {{T}, F},
        });

    std::string const negation::_symbol = "~";

}
