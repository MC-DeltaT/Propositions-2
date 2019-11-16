#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <string>


namespace propositions {

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


    class boolean_value_set {
    private:
        using _set_type = std::array<boolean_value, 2>;

    public:
        using value_type = boolean_value;
        using reference = boolean_value const&;
        using const_reference = boolean_value const&;
        using size_type = _set_type::size_type;
        using iterator = _set_type::const_iterator;
        using const_iterator = _set_type::const_iterator;

        boolean_value_set();
        boolean_value_set(bool has_f, bool has_t);
        explicit boolean_value_set(std::initializer_list<boolean_value> values);

        bool contains(boolean_value value) const;
        size_type size() const;
        const_iterator begin() const;
        const_iterator end() const;

        friend bool operator==(boolean_value_set const& lhs, boolean_value_set const& rhs);

    private:
        bool _has_f;
        bool _has_t;

        static _set_type const _all_booleans;
    };

    extern boolean_value_set const all_booleans;

}


template<>
struct std::hash<propositions::boolean_value> {
    std::size_t operator()(propositions::boolean_value b) const noexcept;
};
