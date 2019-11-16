#include "expression.hpp"

#include "boolean.hpp"

#include <stdexcept>


namespace propositions {

    bool expression::could_be(boolean_value value) const
    {
        return values().contains(value);
    }

    boolean_value expression::exact_value() const
    {
        if (!is_exact()) {
            throw std::logic_error("Expression is not exact.");
        }
        return *values().begin();
    }

    bool expression::is_contradiction() const
    {
        return is_exact() && values().contains(F);
    }

    bool expression::is_exact() const
    {
        return values().size() == 1;
    }

    bool expression::is_tautology() const
    {
        return is_exact() && values().contains(T);
    }

    boolean_value_set expression::values() const
    {
        return truth().outputs();
    }

}
