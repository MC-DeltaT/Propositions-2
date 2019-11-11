#include "truthtable.hpp"

#include "boolean.hpp"

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>


namespace truthtable {

	namespace detail {

		class value_combination_generator {
		public:
			template<class Container,
				std::enable_if_t<std::is_same_v<typename Container::value_type, boolean::value_set>, int> = 0>
				explicit value_combination_generator(Container const& value_sets) :
				_sets(std::cbegin(value_sets), std::cend(value_sets)),
				_values(std::size(value_sets))
			{
				_iterators.reserve(std::size(value_sets));
				for (auto const& set : _sets) {
					_iterators.push_back(set.begin());
				}

				_done = size() == 0;
			}

			template<class Container,
				std::enable_if_t<std::is_same_v<typename Container::value_type, input>, int> = 0>
				explicit value_combination_generator(Container const& inputs) :
				_values(std::size(inputs))
			{
				_sets.reserve(std::size(inputs));
				for (auto const& i : inputs) {
					_sets.push_back(i.values());
				}

				_iterators.reserve(std::size(inputs));
				for (auto const& set : _sets) {
					_iterators.push_back(set.begin());
				}

				_done = size() == 0;
			}

			std::size_t size() const
			{
				std::size_t res = 1;
				for (auto const& set : _sets) {
					res *= set.size();
				}
				return res;
			}

			bool done() const
			{
				return _done;
			}

			std::vector<boolean::boolean_value> const& next()
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

		private:
			bool _done;
			std::vector<boolean::value_set::iterator> _iterators;
			std::vector<boolean::value_set> _sets;
			std::vector<boolean::boolean_value> _values;
		};

	}


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
			_inputs.push_back(std::move(label));
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
