#pragma once

#include <cstddef>
#include <functional>
#include <initializer_list>
#include <string>


namespace boolean {

	class boolean_value {
	public:
		explicit constexpr boolean_value(bool value);

		constexpr bool value() const;

		std::string to_string() const;

		constexpr operator bool() const;

		bool operator==(boolean_value const& other) const;

	private:
		bool _value;
	};


	static inline constexpr boolean_value F{false};
	static inline constexpr boolean_value T{true};


	class value_set {
	public:
		value_set(bool has_f, bool has_t);

		value_set(std::initializer_list<boolean_value> values);

		bool contains(boolean_value const& value) const;

		bool operator==(value_set const& other) const;

	private:
		bool _has_f;
		bool _has_t;
	};

}


template<>
struct std::hash<boolean::boolean_value> {
	std::size_t operator()(boolean::boolean_value const& b) const noexcept;
};
