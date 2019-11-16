#pragma once

#include "boolean.hpp"
#include "expression.hpp"
#include "truthtable.hpp"

#include <string>


namespace propositions {

    class literal : public simple_expression {
    public:
        literal(boolean_value value);

        virtual std::string to_string() const override;
        virtual truth_table const& truth() const override;
        boolean_value value() const;

    private:
        truth_table _truth;
        boolean_value _value;
    };

    bool operator==(literal const& lhs, literal const& rhs);

    extern literal const literal_f;
    extern literal const literal_t;


    class variable : public simple_expression {
    public:
        explicit variable(std::string name);

        std::string const& name() const;
        virtual std::string to_string() const override;
        virtual truth_table const& truth() const override;

    private:
        std::string _name;
        truth_table _truth;
    };

    bool operator==(variable const& lhs, variable const& rhs);

}
