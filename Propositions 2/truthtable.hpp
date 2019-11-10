#pragma once

#include "boolean.hpp"

#include <cstddef>
#include <string>
#include <utility>
#include <vector>


namespace truthtable {

	class input {
	public:
		input(std::string label, boolean::value_set values = boolean::all_values, bool is_unique = true);

		std::string const& label() const;
		boolean::value_set const& values() const;
		bool is_unique() const;

	private:
		bool _is_unique;
		std::string _label;
		boolean::value_set _values;
	};

	bool operator==(input const& lhs, input const& rhs);


	class truth_table {
	public:
		using table_type = std::vector<std::pair<std::vector<boolean::boolean_value>, boolean::boolean_value>>;

		truth_table(std::size_t num_inputs, table_type table);
		truth_table(std::vector<input> inputs, table_type table);

		std::vector<input> const& inputs() const;

		boolean::boolean_value const& operator[](std::vector<boolean::boolean_value> const& inputs) const;

	private:
		std::vector<input> _inputs;
		table_type _table;
	};

}
