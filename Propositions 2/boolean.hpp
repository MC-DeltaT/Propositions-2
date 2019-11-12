#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <string>


namespace boolean {

    class boolean_value {
    public:
        boolean_value();
        explicit boolean_value(bool value);

        bool value() const;
        std::string to_string() const;

        operator bool() const;

    private:
        bool _value;
    };

    bool operator==(boolean_value const& lhs, boolean_value const& rhs);

    extern boolean_value const F;
    extern boolean_value const T;


    class value_set {
    private:
        using _set_type = std::array<boolean_value, 2>;

    public:
        using value_type = boolean_value;
        using reference = boolean_value const&;
        using const_reference = boolean_value const&;
        using size_type = _set_type::size_type;
        using iterator = _set_type::const_iterator;
        using const_iterator = _set_type::const_iterator;

        value_set();
        value_set(bool has_f, bool has_t);
        explicit value_set(std::initializer_list<boolean_value> values);

        bool contains(boolean_value const& value) const;
        size_type size() const;
        const_iterator begin() const;
        const_iterator end() const;

        friend bool operator==(value_set const& lhs, value_set const& rhs);

    private:
        bool _has_f;
        bool _has_t;

        static _set_type const _all_booleans;
    };

    extern value_set const all_values;

}


template<>
struct std::hash<boolean::boolean_value> {
    std::size_t operator()(boolean::boolean_value const& b) const noexcept;
};
