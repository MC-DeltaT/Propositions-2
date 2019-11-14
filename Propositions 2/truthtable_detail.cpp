#include "truthtable_detail.hpp"

#include "boolean.hpp"

#include <cstddef>
#include <stdexcept>
#include <vector>


namespace truthtable::detail {

    std::size_t value_combination_generator::size() const
    {
        std::size_t res = 1;
        for (auto const& set : _sets) {
            res *= set.size();
        }
        return res;
    }

    bool value_combination_generator::done() const
    {
        return _done;
    }

    std::vector<boolean::boolean_value> const& value_combination_generator::next()
    {
        if (_done) {
            throw std::logic_error("Generator is exhausted.");
        }

        for (std::size_t i = 0; i < _values.size(); ++i) {
            _values[i] = *_iterators[i];
        }

        bool carry = true;
        for (std::size_t i = 0; i < _iterators.size(); ++i) {
            if (carry) {
                auto& it = _iterators[i];
                auto const& set = _sets[i];
                ++it;
                if (it == set.end()) {
                    it = set.begin();
                }
                else {
                    carry = false;
                    break;
                }
            }
        }
        _done = carry;

        return _values;
    }


    boolean::boolean_value const& join_input_generator::operator()(std::size_t index) const
    {
        return (*new_input_values)[index];
    }

}
