#ifndef __FIELD_HPP__
#define __FIELD_HPP__

#include <string>
#include <vector>
#include "object.hpp"

class Field : public Object {
	public:
        Field(int x, int y);
//		void addPossibleValue(int value);
		void removePossibleValue(int value);
		bool isValuePossible(int value);
		std::string print();
		std::string debugPrint();
		std::string debugPrintCoordinates();
		std::string printObject();
		int getValue();
		void setValue(int value/*, bool isInit = false*/);
		void trySettingValue(int value = -1);
//		void addOwner(void * owner);

	private:
		void clearPossibleValues();

//		bool m_isInitSet;
		int m_value;
		const int m_x;
		const int m_y;
		bool m_possibleValues[9];
//		std::vector<void *> m_owners;
};

#endif
