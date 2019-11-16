#pragma once

#include "boolean.hpp"
#include "truthtable.hpp"


namespace propositions {

    class expression {
    public:
        virtual bool could_be(boolean_value value) const;
        virtual boolean_value exact_value() const;
        virtual bool is_contradiction() const;
        virtual bool is_exact() const;
        virtual bool is_tautology() const;
        virtual truth_table const& truth() const = 0;
        virtual boolean_value_set values() const;
    };

}
