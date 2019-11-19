#pragma once

#include "expression.hpp"
#include "operation.hpp"
#include "simple_expression.hpp"

#include <functional>
#include <memory>
#include <random>
#include <vector>


namespace propositions::utility_detail {

    extern std::vector<variable> const alphabetic_variables;


    std::unique_ptr<literal> random_literal(std::default_random_engine& rand_eng);

    std::unique_ptr<unary_operation> random_unary_operation(std::unique_ptr<expression> rhs, std::default_random_engine& rand_eng);

    std::unique_ptr<binary_operation> random_binary_operation(std::unique_ptr<expression> lhs, std::unique_ptr<expression> rhs,
        std::default_random_engine& rand_eng);
    
    std::unique_ptr<expression> random_expression(unsigned depth, unsigned max_depth,
        std::vector<std::reference_wrapper<variable const>> const& variables, std::default_random_engine& rand_eng);

}
