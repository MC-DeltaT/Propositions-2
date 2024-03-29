#include "truthtable_detail.hpp"

#include "boolean.hpp"

#include <cstddef>
#include <stdexcept>
#include <vector>


namespace propositions::truthtable_detail {

    std::size_t input_combination_generator::size() const
    {
        std::size_t res = 1;
        for (auto const& set : _sets) {
            res *= set.size();
        }
        return res;
    }

    bool input_combination_generator::done() const
    {
        return _done;
    }

    std::vector<boolean_value> const& input_combination_generator::next()
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


    join_input_generator::join_input_generator(std::vector<boolean_value> const* new_input_values) :
        _single_input_gen{new_input_values}
    {}


    boolean_value join_input_generator::single_input_generator::operator()(std::size_t index) const
    {
        return (*new_input_values)[index];
    }

}
