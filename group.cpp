#include <iostream>
#include <map>
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

Field * Group::getField(int index) {
    if (index < 0 || index >= 9) {
        return NULL;
    }
    if (m_fields.size() < index + 1) {
        return NULL;
    }
    return m_fields[index];
}

// bool Group::processGroup() {
//     if (m_fields.size() != 9) {
//         return false;
//     }

//     // get all values used in this group
//     std::vector<int> setValues;
//     for (auto it : m_fields) {
//         if (it->getValue() > 0) {
//             setValues.push_back(it->getValue());
//         }
//     }

//     std::cout << "*** Values already set for " << this->dbgName() << "(" << this->dbgIndex() << ")" << "\t\t";
//     for (auto it2 : setValues) {
//         std::cout << std::to_string(it2) << ", ";
//     }
//     std::cout << "\n";

//     // remove used values from possibleValues
//     bool anyChange = false;
//     for (auto it : m_fields) {
// //        if (it->getValue() == 0) {
//         for (auto it2 : setValues) {
//             anyChange |= it->removePossibleValue(it2);
//         }
// //        }
// //        anyChange |= it->trySettingValue();
//     }

//     // check if there is any possible value that exists as single in group and set it
//     std::map<int, int> possibleValues;
//     for (auto it : m_fields) {
//         std::cout << "*** Possible values: " << it->debugPrint() << std::endl;
//         if (it->getValue() > 0) {
//             continue;
//         }
//         for (int i = 1; i <= 9; i++) {
//             if (it->isValuePossible(i)) {
//                 possibleValues[i - 1]++;
//             }
//         }
//     }
//     std::cout << "### Possible values count " << dbgName() << " " << dbgIndex() << std::endl;
//     for (auto it : possibleValues) {
//         std::cout << "### ... " << std::to_string(it.first) << " - " << std::to_string(it.second) << std::endl;
//     }
// //    std::cout << "*** Possible values count\n";
//     int valueToSet = -1;
//     for (auto it : possibleValues) {
//         if (it.second == 1) {
//             valueToSet = it.first + 1;
//             break;
//         }
//     }
//     Field *fieldToSetSinglePossibleValue = NULL;
//     std::cout << "### valueToSet: " << valueToSet << std::endl;
//     if (valueToSet > 0) {
//         for (auto it : m_fields) {
//             if (it->isValuePossible(valueToSet)) {
//                 fieldToSetSinglePossibleValue = it;
//                 break;
//             }
//         }
//     }
//     if (fieldToSetSinglePossibleValue != NULL) {
//         if (fieldToSetSinglePossibleValue->trySettingValue(valueToSet)) {
//             return true;
//         }
//     }

//     // try setting value (return on first success)
//     for (auto it : m_fields) {
//         bool setField = it->trySettingValue();
//         if (setField) {
//             std::cout << "*** " << it->debugPrint();
//             anyChange |= setField;
//             break;
//         }
//     }

//     return anyChange;
// }

void Group::performCleanup() {
    // get all values used in this group
    std::vector<int> setValues;
    for (auto it : m_fields) {
        if (it->getValue() > 0) {
            setValues.push_back(it->getValue());
        }
    }

    std::cout << "*** Values already set for " << this->dbgName() << "(" << this->dbgIndex() << ")" << "\t\t";
    for (auto it2 : setValues) {
        std::cout << std::to_string(it2) << ", ";
    }
    std::cout << "\n";

    // remove used values from possibleValues
    for (auto it : m_fields) {
        for (auto it2 : setValues) {
            it->removePossibleValue(it2);
        }
    }
}

void Group::performSetting() {
    std::map<Field *, int> valuesToSet;
    std::map<int, int> possibleValuesCount;

    for (auto it : m_fields) {
        int possibleCounter = 0, possibleValue = -1;
        for (int i = 0; i < 9; i++) {
            if (it->isValuePossible(i + 1)) {
                possibleValuesCount[i + 1]++;
                possibleValue = i + 1;
                possibleCounter++;
            }
        }
        if (possibleCounter == 1) { // only one possible value to set in this field
            std::cout << "*** single possible value for " << it->debugPrintCoordinates() << " [" << std::to_string(possibleValue) << std::endl;
            valuesToSet[it] = possibleValue;
            possibleValuesCount[possibleValue]++; // increment so this value won't be selected in next step
        }
    }
    std::cout << "*** possibleValuesCount: " << std::endl;
    for (auto it2 : possibleValuesCount) {
        std::cout << "*** ... " << std::to_string(it2.first) << ": " << std::to_string(it2.second) << std::endl;
    }

    // if value is possible only for a single field in group, set it
    for (auto it2 : possibleValuesCount) {
        if (it2.second > 1) {
            continue;
        }
        for (auto it : m_fields) {
            if (it->isValuePossible(it2.first)) {
                valuesToSet[it] = it2.first;
                break;
            }
        }
    }

    // try setting values
    for (auto it3 : valuesToSet) {
        it3.first->trySettingValue(it3.second);
    }

    performCleanup();
}

//void Group::performOwnerFunction() {
//    std::cout << "Group.performOwnerFunction()" << std::endl;
//    processGroup();
//}

std::string Group::printObject() {
    return dbgName() + " " + dbgIndex();
}