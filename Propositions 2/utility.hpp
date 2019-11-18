#pragma once

#include "expression.hpp"

#include <memory>


namespace propositions {

    std::unique_ptr<expression> random_expression(unsigned max_vars, unsigned max_depth);

}
