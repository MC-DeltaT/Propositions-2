#pragma once

#include <array>
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

	private:
		bool _value;
	};

	constexpr bool operator==(boolean_value const& lhs, boolean_value const& rhs);

	static inline constexpr boolean_value F{false};
	static inline constexpr boolean_value T{true};


	class value_set {
	public:
		constexpr value_set(bool has_f, bool has_t);
		value_set(std::initializer_list<boolean_value> values);

		constexpr bool contains(boolean_value const& value) const;
		constexpr std::size_t size() const;
		constexpr auto begin() const;
		constexpr auto end() const;

		friend constexpr bool operator==(value_set const& lhs, value_set const& rhs);

	private:
		bool _has_f;
		bool _has_t;

		static inline constexpr std::array<boolean_value, 2> _all_booleans{F, T};
	};

	static inline constexpr value_set all_values(true, true);

}


template<>
struct std::hash<boolean::boolean_value> {
	std::size_t operator()(boolean::boolean_value const& b) const noexcept;
};
