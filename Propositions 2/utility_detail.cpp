#include "utility_detail.hpp"

#include "expression.hpp"
#include "operation.hpp"
#include "simple_expression.hpp"

#include <cassert>
#include <cstddef>
#include <functional>
#include <memory>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include <boost/range/adaptor/transformed.hpp>


namespace propositions::utility_detail {

    static std::string const alphabet = "abcdefghijklmnopqrstuvwxyz";
    static auto const alphabetic_variable_range = alphabet | boost::adaptors::transformed([](char c) { return variable({c}); });
    std::vector<variable> const alphabetic_variables(alphabetic_variable_range.begin(), alphabetic_variable_range.end());


    std::unique_ptr<literal> random_literal(std::default_random_engine& rand_eng)
    {
        std::uniform_int_distribution<unsigned> dist(0, 1);
        if (dist(rand_eng) & 1u) {
            return std::make_unique<literal>(literal_f);
        }
        else {
            return std::make_unique<literal>(literal_t);
        }
    }


    std::unique_ptr<unary_operation> random_unary_operation(std::unique_ptr<expression> rhs, std::default_random_engine& rand_eng)
    {
        assert(unary_operations.size() > 0);
        std::uniform_int_distribution<std::size_t> const dist(0, unary_operations.size() - 1);

        return unary_operations[dist(rand_eng)](std::move(rhs));
    }

    std::unique_ptr<binary_operation> random_binary_operation(std::unique_ptr<expression> lhs, std::unique_ptr<expression> rhs,
        std::default_random_engine& rand_eng)
    {
        assert(binary_operations.size() > 0);
        std::uniform_int_distribution<std::size_t> const dist(0, binary_operations.size() - 1);

        return binary_operations[dist(rand_eng)](std::move(lhs), std::move(rhs));
    }


    std::unique_ptr<expression> random_expression(unsigned depth, unsigned max_depth,
        std::vector<std::reference_wrapper<variable const>> const& variables, std::default_random_engine& rand_eng)
    {
        std::uniform_real_distribution<double> const dist1;
        double const simple_cutoff = static_cast<double>(depth) / max_depth;
        double const r = dist1(rand_eng);

        if (r <= simple_cutoff) {
            if (variables.size() == 0 || dist1(rand_eng) <= 0.5) {
                return random_literal(rand_eng);
            }
            else {
                std::uniform_int_distribution<std::size_t> const dist2(0, variables.size() - 1);
                return std::make_unique<variable>(variables[dist2(rand_eng)]);
            }
        }
        else if (r <= simple_cutoff + ((1.0 - simple_cutoff) / 3.0)) {
            auto rhs = random_expression(depth + 1, max_depth, variables, rand_eng);
            return random_unary_operation(std::move(rhs), rand_eng);
        }
        else {
            auto lhs = random_expression(depth + 1, max_depth, variables, rand_eng);
            auto rhs = random_expression(depth + 1, max_depth, variables, rand_eng);
            return random_binary_operation(std::move(lhs), std::move(rhs), rand_eng);
        }
    }

}
