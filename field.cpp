#include <iostream>
#include "field.hpp"

Field::Field(int val) {
    if (val > 0 && val <= 9) {
        m_isInitSet = true;
        m_value = val;
    } else {
		m_isInitSet = false;
		m_value = 0;
	}
}

void Field::addPossibleValue(int value) {
	if (m_isInitSet || value > 0) {
		return;
	}
	if (value < 1 || value > 9) {
		std::cout << "[LOG] (addPossibleValue) - invalid value (" << value << ")" << std::endl;
		return;
	}
	m_possibleValues[value - 1] = true;
}

void Field::removePossibleValue(int value) {
	if (m_isInitSet || value > 0) {
		return; // field's value is set from start
	}
	if (value < 1 || value > 9) {
		std::cout << "[LOG] (removePossibleValue) - invalid value (" << value << ")" << std::endl;
		return;
	}
	m_possibleValues[value - 1] = false;
}

std::string Field::print() {
	if (m_value <= 0) {
		return std::string(" ");
	}

	return std::to_string(m_value);
}

int Field::getValue() {
	if (m_value <= 0) {
		return 0;
	}

	return m_value;
}