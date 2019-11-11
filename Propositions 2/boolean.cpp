#include "boolean.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <string>


namespace boolean {

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


	value_set::value_set() :
		_has_f(false),
		_has_t(false)
	{}

	value_set::value_set(bool has_f, bool has_t) :
		_has_f(has_f),
		_has_t(has_t)
	{}

	value_set::value_set(std::initializer_list<boolean_value> values)
	{
		_has_f = std::find(values.begin(), values.end(), F) != values.end();
		_has_t = std::find(values.begin(), values.end(), T) != values.end();
	}

	bool value_set::contains(boolean_value const& value) const
	{
		if (value == F) {
			return _has_f;
		}
		else {
			return _has_t;
		}
	}

	value_set::size_type value_set::size() const
	{
		return static_cast<std::size_t>(_has_f) + static_cast<std::size_t>(_has_t);
	}

	value_set::const_iterator value_set::begin() const
	{
		return _all_booleans.cbegin() + !_has_f;
	}

	value_set::const_iterator value_set::end() const
	{
		return _all_booleans.cend() - !_has_t;
	}

	value_set::_set_type const value_set::_all_booleans{F, T};

	bool operator==(value_set const& lhs, value_set const& rhs)
	{
		return lhs._has_f == rhs._has_f && lhs._has_t == rhs._has_t;
	}


	value_set const all_values(true, true);
}


std::size_t std::hash<boolean::boolean_value>::operator()(boolean::boolean_value const& b) const noexcept
{
	return std::hash<bool>{}(b.value());
}
