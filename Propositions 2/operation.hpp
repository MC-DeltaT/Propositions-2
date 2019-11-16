#pragma once

#include "expression.hpp"
#include "operation_detail.hpp"
#include "truthtable.hpp"

#include <memory>
#include <string>


namespace propositions {

    class operation : public compound_expression {};


    class unary_operation : public operation {
    public:
        truth_table const& join() const;
        expression const& rhs() const;
        std::string const& symbol() const;
        virtual std::string to_string() const override;
        virtual truth_table const& truth() const override;

    protected:
        unary_operation(std::unique_ptr<expression> rhs, truth_table const* join, truth_table truth, std::string symbol);

    private:
        truth_table const* _join;
        std::unique_ptr<expression> _rhs;
        std::string _symbol;
        truth_table _truth;
    };


    class identity : public operation_detail::unary_operation_helper<identity, unary_operation> {
    public:
        using unary_operation_helper::unary_operation_helper;

    protected:
        static truth_table const _join;
        static std::string const _symbol;
    };


    class negation : public operation_detail::unary_operation_helper<negation, unary_operation> {
    public:
        using unary_operation_helper::unary_operation_helper;

    protected:
        static truth_table const _join;
        static std::string const _symbol;
    };

}
