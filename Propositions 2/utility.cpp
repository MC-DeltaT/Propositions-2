#include "utility.hpp"

#include "utility_detail.hpp"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <functional>
#include <iterator>
#include <random>
#include <vector>


namespace propositions {

    std::unique_ptr<expression> random_expression(unsigned max_vars, unsigned max_depth)
    {
        using utility_detail::alphabetic_variables;

        static std::default_random_engine rand_eng(std::chrono::high_resolution_clock::now().time_since_epoch().count());
        static std::vector<std::reference_wrapper<variable const>> variables;

        assert(max_vars <= alphabetic_variables.size());
        assert(max_depth > 0);

        variables.clear();
        variables.reserve(max_vars);
        std::sample(alphabetic_variables.cbegin(), alphabetic_variables.cend(), std::back_inserter(variables), max_vars, rand_eng);

        return utility_detail::random_expression(0, max_depth, variables, rand_eng);
    }

}
