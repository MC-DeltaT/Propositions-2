#include "truthtable.hpp"

#include "boolean.hpp"

#include <algorithm>
#include <stdexcept>
#include <utility>


namespace propositions {

    template<typename InputIterator>
    boolean_value const& truth_table::operator[](std::pair<InputIterator, InputIterator> inputs) const
    {
        for (auto const& row : _table) {
            if (std::equal(row.first.cbegin(), row.first.cend(), inputs.first, inputs.second)) {
                return row.second;
            }
        }

        throw std::out_of_range("Input sequence is not mapped to any output.");
    }

}
