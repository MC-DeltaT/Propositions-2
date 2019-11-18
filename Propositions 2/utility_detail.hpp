#pragma once

#include "operation.hpp"
#include "simple_expression.hpp"

#include <array>
#include <functional>
#include <memory>
#include <random>
#include <vector>


namespace propositions::utility_detail {

    template<class UnaryOperation>
    std::unique_ptr<unary_operation> create_unary_operation(std::unique_ptr<expression> rhs);

    template<class BinaryOperation>
    std::unique_ptr<binary_operation> create_binary_operation(std::unique_ptr<expression> lhs, std::unique_ptr<expression> rhs);


    extern std::vector<std::unique_ptr<unary_operation> (*)(std::unique_ptr<expression>)> const unary_operations;
    extern std::vector<std::unique_ptr<binary_operation> (*)(std::unique_ptr<expression>, std::unique_ptr<expression>)> const binary_operations;
    extern std::vector<std::reference_wrapper<literal const>> const literals;
    extern std::vector<variable> const alphabetic_variables;


    std::unique_ptr<expression> random_expression(unsigned depth, unsigned max_depth,
        std::vector<std::reference_wrapper<variable const>> const& variables, std::default_random_engine& rand_eng);

}


#include "utility_detail.tpp"
