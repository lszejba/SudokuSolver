#ifndef __FIELD_HPP__
#define __FIELD_HPP__

#include <string>

class Field {
	public:
		void addPossibleValue(int value);
		void removePossibleValue(int value);
		std::string print();
		int getValue();
	private:
		bool isInitSet;
		int value;
		bool possibleValues[9];
};

#endif
