#pragma once

#include <cstddef>
#include <functional>
#include <initializer_list>
#include <string>


namespace boolean {

	class boolean_value {
	public:
		static constexpr boolean_value from_bool(bool value);

		constexpr bool value() const;

		std::string to_string() const;

		constexpr operator bool() const;

		bool operator==(boolean_value const& other) const;

	private:
		bool _value;

		explicit constexpr boolean_value(bool value);
	};


	static constexpr boolean_value F = boolean_value::from_bool(false);;
	static constexpr boolean_value T = boolean_value::from_bool(true);


	class value_set {
	public:
		value_set(bool has_f, bool has_t);

		value_set(std::initializer_list<boolean_value> values);

	private:
		bool _has_f;
		bool _has_t;
	};

}


template<>
struct std::hash<boolean::boolean_value> {
	std::size_t operator()(boolean::boolean_value const& b) const noexcept;
};
