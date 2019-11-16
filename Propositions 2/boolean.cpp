#include "boolean.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <string>


namespace propositions {

    boolean_value::boolean_value() :
        _value(false)
    {}

    boolean_value::boolean_value(bool value) :
        _value(value)
    {}

    bool boolean_value::value() const
    {
        return _value;
    }

    std::string boolean_value::to_string() const
    {
        if (_value) {
            return "T";
        }
        else {
            return "F";
        }
    }

    boolean_value::operator bool() const
    {
        return _value;
    }

    bool operator==(boolean_value const& lhs, boolean_value const& rhs)
    {
        return lhs.value() == rhs.value();
    }

    boolean_value const F{false};
    boolean_value const T{true};


    boolean_value_set::boolean_value_set() :
        _has_f(false),
        _has_t(false)
    {}

    boolean_value_set::boolean_value_set(bool has_f, bool has_t) :
        _has_f(has_f),
        _has_t(has_t)
    {}

    boolean_value_set::boolean_value_set(std::initializer_list<boolean_value> values)
    {
        _has_f = std::find(values.begin(), values.end(), F) != values.end();
        _has_t = std::find(values.begin(), values.end(), T) != values.end();
    }

    bool boolean_value_set::contains(boolean_value value) const
    {
        if (value == F) {
            return _has_f;
        }
        else {
            return _has_t;
        }
    }

    boolean_value_set::size_type boolean_value_set::size() const
    {
        return static_cast<std::size_t>(_has_f) + static_cast<std::size_t>(_has_t);
    }

    boolean_value_set::const_iterator boolean_value_set::begin() const
    {
        return _all_booleans.cbegin() + !_has_f;
    }

    boolean_value_set::const_iterator boolean_value_set::end() const
    {
        return _all_booleans.cend() - !_has_t;
    }

    boolean_value_set::_set_type const boolean_value_set::_all_booleans{F, T};

    bool operator==(boolean_value_set const& lhs, boolean_value_set const& rhs)
    {
        return lhs._has_f == rhs._has_f && lhs._has_t == rhs._has_t;
    }


    boolean_value_set const all_booleans(true, true);
}


std::size_t std::hash<propositions::boolean_value>::operator()(propositions::boolean_value b) const noexcept
{
    return std::hash<bool>{}(b.value());
}
