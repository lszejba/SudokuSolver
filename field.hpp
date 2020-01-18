#ifndef __FIELD_HPP__
#define __FIELD_HPP__

#include <string>

class Field {
	public:
        Field(int value);
		void addPossibleValue(int value);
		void removePossibleValue(int value);
		std::string print();
		int getValue();
	private:
		bool m_isInitSet;
		int m_value;
		bool m_possibleValues[9];
};

#endif
