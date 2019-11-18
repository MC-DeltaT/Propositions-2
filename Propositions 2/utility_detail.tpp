#include "utility_detail.hpp"

#include "operation.hpp"

#include <memory>
#include <utility>


namespace propositions::utility_detail {

    template<class UnaryOperation>
    std::unique_ptr<unary_operation> create_unary_operation(std::unique_ptr<expression> rhs)
    {
        return std::make_unique<UnaryOperation>(std::move(rhs));
    }

    template<class BinaryOperation>
    std::unique_ptr<binary_operation> create_binary_operation(std::unique_ptr<expression> lhs, std::unique_ptr<expression> rhs)
    {
        return std::make_unique<BinaryOperation>(std::move(lhs), std::move(rhs));
    }

}
