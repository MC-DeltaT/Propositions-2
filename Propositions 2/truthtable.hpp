#pragma once


#include "boolean.hpp"

#include <string>


namespace truthtable {

	class unique_input {
	};

	class input {
	public:
		class unique_tag {
		public:
			unique_tag(std::string label) :
				_label(label)
			{}

			bool operator==(unique_tag const&) const
			{
				return false;
			}

		private:
			std::string _label;
		};


		input(boolean::value_set values = {boolean::T, boolean::F}) :
			_values(values)
		{}

	private:
		boolean::value_set _values;
	};

}
