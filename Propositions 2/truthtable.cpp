#include "truthtable.hpp"

#include "boolean.hpp"

#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>


namespace truthtable {

	input::input(std::string label, boolean::value_set values, bool is_unique) :
		_is_unique(is_unique),
		_label(label),
		_values(values)
	{}

	std::string const& input::label() const
	{
		return _label;
	}

	boolean::value_set const& input::values() const
	{
		return _values;
	}

	bool input::is_unique() const
	{
		return _is_unique;
	}

	bool operator==(input const& lhs, input const& rhs)
	{
		if (lhs.is_unique() || rhs.is_unique()) {
			return &lhs == &rhs;
		}
		else {
			return lhs.label() == rhs.label();
		}
	}


	truth_table::truth_table(std::size_t num_inputs, table_type table) :
		_table(table)
	{
		_inputs.reserve(num_inputs);
		for (std::size_t i = 0; i < num_inputs; ++i) {
			std::string label = "<" + std::to_string(i + 1) + ">";
			_inputs.emplace_back(std::move(label));
		}
	}

	truth_table::truth_table(std::vector<input> inputs, table_type table) :
		_inputs(inputs),
		_table(table)
	{}

	std::vector<input> const& truth_table::inputs() const
	{
		return _inputs;
	}

	boolean::boolean_value const& truth_table::operator[](std::vector<boolean::boolean_value> const& input) const
	{
		for (auto const& row : _table) {
			if (row.first == input) {
				return row.second;
			}
		}

		throw std::out_of_range("Input sequence is not mapped to any output.");
	}

}
