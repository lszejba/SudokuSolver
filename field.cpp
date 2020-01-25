#include <iostream>
#include "field.hpp"

Field::Field(int val, int x, int y) {
    if (val > 0 && val <= 9) {
        m_isInitSet = true;
        m_value = val;
    } else {
		m_isInitSet = false;
		m_value = 0;
	}

	m_x = x;
	m_y = y;

	for (int i = 0; i < 9; i++) {
		m_possibleValues[i] = !m_isInitSet;
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

std::string Field::debugPrint() {
	std::string res = "Field [" + std::to_string(m_x) + "," + std::to_string(m_y) + "] value: " + std::to_string(m_value) + "\n";
	res += "\tPossible values: ";
	for (int i = 0; i < 9; i++) {
		if (m_possibleValues[i]) {
			res += std::to_string(i + 1) + " ";
		}
	}
	res += "\n";
	return res;
}

int Field::getValue() {
	if (m_value <= 0) {
		return 0;
	}

	return m_value;
}