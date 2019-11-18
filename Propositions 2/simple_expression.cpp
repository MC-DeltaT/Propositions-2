#include "simple_expression.hpp"

#include "boolean.hpp"
#include "truthtable.hpp"

#include <string>


namespace propositions {

    literal::literal(boolean_value value) :
        _truth({
                {value.to_string(), {value}}
            }, {
                {{value}, value}
            }),
        _value(value)
    {}

    std::string literal::to_string() const
    {
        return _value.to_string();
    }

    truth_table const& literal::truth() const
    {
        return _truth;
    }

    boolean_value literal::value() const
    {
        return _value;
    }

    bool operator==(literal const& lhs, literal const& rhs)
    {
        return lhs.value() == rhs.value();
    }

    literal const literal_f{F};
    literal const literal_t{T};


    variable::variable(std::string name) :
        _name(name),
        _truth({
                {name}
            }, {
                {{F}, F},
                {{T}, T}
            })
    {}

    std::string const& variable::name() const
    {
        return _name;
    }

    std::string variable::to_string() const
    {
        return _name;
    }

    truth_table const& variable::truth() const
    {
        return _truth;
    }

    bool operator==(variable const& lhs, variable const& rhs)
    {
        return lhs.name() == rhs.name();
    }

}
