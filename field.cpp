#include <iostream>
#include "field.hpp"


void Field::addPossibleValue(int value) {
	if (isInitSet || value > 0) {
		return;
	}
	if (value < 1 || value > 9) {
		std::cout << "[LOG] (addPossibleValue) - invalid value (" << value << ")" << std::endl;
		return;
	}
	possibleValues[value - 1] = true;
}

void Field::removePossibleValue(int value) {
	if (isInitSet || value > 0) {
		return; // field's value is set from start
	}
	if (value < 1 || value > 9) {
		std::cout << "[LOG] (removePossibleValue) - invalid value (" << value << ")" << std::endl;
		return;
	}
	possibleValues[value - 1] = false;
}

std::string Field::print() {
	if (value <= 0) {
		return std::string(" ");
	}

	return std::to_string(value);
}

int Field::getValue() {
	if (value <= 0) {
		return 0;
	}

	return value;
}