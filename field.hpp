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
		void setValue(int value);
		void trySettingValue();
	private:
		void clearPossibleValues();

		bool m_isInitSet;
		int m_value;
		const int m_x;
		const int m_y;
		bool m_possibleValues[9];
};

#endif
