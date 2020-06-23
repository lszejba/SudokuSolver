#include <iostream>
#include "field.hpp"
#include "group.hpp"

Field::Field(int x, int y) : /*m_isInitSet(false),*/ m_value(0), m_x(x), m_y(y) {
	for (int i = 0; i < 9; i++) {
		m_possibleValues[i] = true;//!m_isInitSet;
	}
}

/* Returns true if value has been removed from possibleValues, false otherwise */
void Field::removePossibleValue(int value) {
	if (m_value > 0) {
		return; // field's value is set from start
	}
	if (value < 1 || value > 9) {
//		std::cout << "[LOG] (removePossibleValue) - invalid value (" << value << ")" << std::endl;
		return;
	}
	if (m_possibleValues[value - 1]) {
		m_possibleValues[value - 1] = false;
		std::cout << "--- removePossible(" << std::to_string(value) << ") for " << debugPrintCoordinates() << std::endl;
		signalOwners();
	}
}

bool Field::isValuePossible(int value) {
	if (m_value > 0) {
		return false;
	}
	return m_possibleValues[value - 1];
}

std::string Field::print() {
	if (m_value <= 0) {
		return std::string(" ");
	}

	return std::to_string(m_value);
}

std::string Field::debugPrint() {
	std::string res = "Field " + debugPrintCoordinates() + " value: " + std::to_string(m_value) + ", ";
	res += "\tPossible values: ";
	for (int i = 0; i < 9; i++) {
		if (m_possibleValues[i]) {
			res += std::to_string(i + 1) + " ";
		}
	}
	res += "\n";
	return res;
}

std::string Field::printObject() {
	return this->debugPrintCoordinates();
}

std::string Field::debugPrintCoordinates() {
	std::string res = "(" + std::to_string(m_x) + "," + std::to_string(m_y) + ")";

	return res;
}

int Field::getValue() {
	if (m_value <= 0) {
		return 0;
	}

	return m_value;
}

void Field::setValue(int value) {
	if (m_value > 0) {
		std::cout << "$$$ setValue failed " << debugPrintCoordinates() << " - value already set" << std::endl;
		return;
	}
	if (value < 1 || value > 9) {
		std::cout << "$$$ setValue failed " << debugPrintCoordinates() << " - invalid value[" << std::to_string(value) << "]" << std::endl;
		return;
	}
	if (!m_possibleValues[value-1]) {
		std::cout << "$$$ setValue failed " << debugPrintCoordinates() << " - value not possible to set [" << std::to_string(value) << "]" << std::endl;
		return;
	}
	if (ownersSetToChange()) {
		std::cout << "$$$ setValue failed " << debugPrintCoordinates() << " - owners set to change" << std::endl;
		return;
	}

	m_value = value;
	clearPossibleValues();
	std::cout << "--- setValue(" << std::to_string(value) << ") for " << debugPrintCoordinates() << std::endl;
	signalOwners();
}

void Field::trySettingValue(int value) {
	int count = 0, valueToSet = value;
	if (valueToSet == -1) {
		for (int i = 0; i < 9; i++) {
			if (m_possibleValues[i]) {
				count++;
				valueToSet = i + 1;
			}
		}
	} else {
		count = 1;
	}

	if (count == 1) {
		setValue(valueToSet);
	}
}

//void Field::addOwner(void *owner) {
//	if (owner != NULL) {
//		m_owners.push_back(owner);
//	}
//}

void Field::clearPossibleValues() {
	for (int i = 0; i < 9; i++) {
		m_possibleValues[i] = false;
	}
}