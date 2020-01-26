#include <iostream>
#include "group.hpp"

void Group::addField(Field *field) {
    if (field == NULL) {
        return;
    }
    if (m_fields.size() == 9) {
        return;
    }

    m_fields.push_back(field);
}

bool Group::processGroup() {
    if (m_fields.size() != 9) {
        return false;
    }

    // get all values used in this group
    std::vector<int> usedValues;
    for (auto it : m_fields) {
        if (it->getValue() != 0) {
            usedValues.push_back(it->getValue());
            std::cout << "usedValues added " << std::to_string(it->getValue()) << std::endl;
        }
    }

    // remove used values from possibleValues and try setting value
    for (auto it : m_fields) {
        if (it->getValue() == 0) {
            for (auto it2 : usedValues) {
                it->removePossibleValue(it2);
                std::cout << "removingPossibleValue for " << std::to_string(it2) << std::endl;
            }
        }
        it->trySettingValue();
    }

    return true;
}
