#include "utility_detail.hpp"

#include "expression.hpp"
#include "operation.hpp"
#include "simple_expression.hpp"

#include <functional>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include <boost/range/adaptor/transformed.hpp>


namespace propositions::utility_detail {

    std::vector<std::unique_ptr<unary_operation> (*)(std::unique_ptr<expression>)> const unary_operations{
        &create_unary_operation<identity>,
        &create_unary_operation<negation>,
    };

    std::vector<std::unique_ptr<binary_operation> (*)(std::unique_ptr<expression>, std::unique_ptr<expression>)> const binary_operations{
        &create_binary_operation<conjunction>,
        &create_binary_operation<disjunction>,
        &create_binary_operation<excl_disjunction>,
        &create_binary_operation<implication>,
        &create_binary_operation<biconditional>,
    };

    std::vector<std::reference_wrapper<literal const>> const literals{
        std::cref(literal_f),
        std::cref(literal_t)
    };

    std::string const alphabet = "abcdefghijklmnopqrstuvwxyz";
    auto const alphabetic_variable_range = alphabet | boost::adaptors::transformed([](char c) { return variable({c}); });
    std::vector<variable> const alphabetic_variables(alphabetic_variable_range.begin(), alphabetic_variable_range.end());


    std::unique_ptr<expression> random_expression(unsigned depth, unsigned max_depth,
        std::vector<std::reference_wrapper<variable const>> const& variables, std::default_random_engine& rand_eng)
    {
        std::uniform_real_distribution<double> const dist;
        double const simple_cutoff = static_cast<double>(depth) / max_depth;
        double const r = dist(rand_eng);

        if (r <= simple_cutoff) {
            if (variables.size() == 0 || dist(rand_eng) <= 0.5) {
                return std::make_unique<literal>(literals[rand_eng() % literals.size()]);
            }
            else {
                return std::make_unique<variable>(variables[rand_eng() % variables.size()]);
            }
        }
        else if (r <= simple_cutoff + ((1.0 - simple_cutoff) / 3.0)) {
            auto rhs = random_expression(depth + 1, max_depth, variables, rand_eng);
            return unary_operations[rand_eng() % unary_operations.size()](std::move(rhs));
        }
        else {
            auto lhs = random_expression(depth + 1, max_depth, variables, rand_eng);
            auto rhs = random_expression(depth + 1, max_depth, variables, rand_eng);
            return binary_operations[rand_eng() % unary_operations.size()](std::move(lhs), std::move(rhs));
        }
    }

}
