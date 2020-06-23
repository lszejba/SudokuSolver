#ifndef __FIELD_HPP__
#define __FIELD_HPP__

#include <string>
#include <vector>
#include "object.hpp"

class Field : public Object {
	public:
        Field(int x, int y);
		void removePossibleValue(int value);
		bool isValuePossible(int value);
		std::string print();
		std::string debugPrint();
		std::string debugPrintCoordinates();
		std::string printObject();
		int getValue();
		void setValue(int value);
		void trySettingValue(int value = -1);

	private:
		void clearPossibleValues();
		
		int m_value;
		const int m_x;
		const int m_y;
		bool m_possibleValues[9];
};

#endif
