#pragma once

#include "expression.hpp"
#include "operation_detail.hpp"
#include "truthtable.hpp"

#include <memory>
#include <ostream>
#include <string>
#include <vector>


namespace propositions {

    class operation : public compound_expression {};


    class unary_operation : public operation {
    public:
        truth_table const& join() const;
        expression const& rhs() const;
        std::string const& symbol() const;
        virtual std::ostream& to_stream(std::ostream& stream) const override;
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


    class binary_operation : public operation {
    public:
        truth_table const& join() const;
        expression const& lhs() const;
        expression const& rhs() const;
        std::string const& symbol() const;
        virtual std::ostream& to_stream(std::ostream& stream) const override;
        virtual std::string to_string() const override;
        virtual truth_table const& truth() const override;

    protected:
        binary_operation(std::unique_ptr<expression> lhs, std::unique_ptr<expression> rhs, truth_table const* join,
            truth_table truth, std::string symbol);

    private:
        truth_table const* _join;
        std::unique_ptr<expression> _lhs;
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


    class conjunction : public operation_detail::binary_operation_helper<conjunction, binary_operation> {
    public:
        using binary_operation_helper::binary_operation_helper;

    protected:
        static truth_table const _join;
        static std::string const _symbol;
    };


    class disjunction : public operation_detail::binary_operation_helper<disjunction, binary_operation> {
    public:
        using binary_operation_helper::binary_operation_helper;

    protected:
        static truth_table const _join;
        static std::string const _symbol;
    };


    class excl_disjunction : public operation_detail::binary_operation_helper<excl_disjunction, binary_operation> {
    public:
        using binary_operation_helper::binary_operation_helper;

    protected:
        static truth_table const _join;
        static std::string const _symbol;
    };


    class implication : public operation_detail::binary_operation_helper<implication, binary_operation> {
    public:
        using binary_operation_helper::binary_operation_helper;

    protected:
        static truth_table const _join;
        static std::string const _symbol;
    };


    class biconditional : public operation_detail::binary_operation_helper<biconditional, binary_operation> {
    public:
        using binary_operation_helper::binary_operation_helper;

    protected:
        static truth_table const _join;
        static std::string const _symbol;
    };


    extern std::vector<std::unique_ptr<unary_operation> (*)(std::unique_ptr<expression>)> const unary_operations;
    extern std::vector<std::unique_ptr<binary_operation> (*)(std::unique_ptr<expression>, std::unique_ptr<expression>)> const binary_operations;

}
