#ifndef __FIELD_HPP__
#define __FIELD_HPP__

#include <string>

class Field {
	public:
        Field(int value, int x, int y);
		void addPossibleValue(int value);
		void removePossibleValue(int value);
		std::string print();
		std::string debugPrint();
		int getValue();
	private:
		bool m_isInitSet;
		int m_value;
		int m_x;
		int m_y;
		bool m_possibleValues[9];
};

#endif
