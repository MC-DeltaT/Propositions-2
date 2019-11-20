#pragma once

#include "boolean.hpp"
#include "truthtable.hpp"

#include <ostream>
#include <string>


namespace propositions {

    class expression {
    public:
        virtual ~expression() = default;

        virtual bool could_be(boolean_value value) const;
        virtual boolean_value exact_value() const;
        virtual bool is_contradiction() const;
        virtual bool is_exact() const;
        virtual bool is_tautology() const;
        virtual std::ostream& to_stream(std::ostream& stream) const = 0;
        virtual std::string to_string() const = 0;
        virtual truth_table const& truth() const = 0;
        virtual boolean_value_set values() const;
    };


    class simple_expression : public expression {};


    class compound_expression : public expression {};

}
