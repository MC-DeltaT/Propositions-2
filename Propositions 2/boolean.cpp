#include "boolean.hpp"

#include <algorithm>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <string>


namespace boolean {

	constexpr boolean_value::boolean_value(bool value) :
		_value(value)
	{}

	constexpr bool boolean_value::value() const
	{
		return _value;
	}

	std::string boolean_value::to_string() const
	{
		if (value()) {
			return "T";
		}
		else {
			return "F";
		}
	}

	constexpr boolean_value::operator bool() const
	{
		return value();
	}

	bool boolean_value::operator==(boolean_value const& other) const
	{
		return value() == other.value();
	}


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
		else if (value == T) {
			return _has_t;
		}
	}

	bool value_set::operator==(value_set const& other) const
	{
		return _has_f == other._has_f && _has_t == other._has_t;
	}

}


std::size_t std::hash<boolean::boolean_value>::operator()(boolean::boolean_value const& b) const noexcept
{
	return std::hash<bool>{}(b.value());
}
