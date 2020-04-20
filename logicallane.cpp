#include <iostream>
#include "logicallane.hpp"

void LogicalLane::addGroup(Group *group) {
    if (group == NULL) {
        return;
    }
    if (m_groups.size() == 3) {
        return;
    }
    m_groups.push_back(group);
}

void LogicalLane::removePossibleFromOtherSquares(int number, int groupIdx, int ownerIdx) {
    std::cout << "removePossibleFromOtherSquares(" + std::to_string(number) + ", " + std::to_string(groupIdx) + ", " + std::to_string(ownerIdx) + ")\n";
    for (int i = 0; i < 3; i++) {
        if (i == ownerIdx) {
            continue;
        }
        for (int j = 0; j < 3; j++) {
            m_groups[groupIdx]->getField(i * 3 + j)->removePossibleValue(number);
        }
    }
}

void LogicalLane::checkSquare(int idx, int number) {
    int index = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (m_groups[i]->getField(idx * 3 + j)->getValue() == number) {
                return;
            }
            if (m_groups[i]->getField(idx * 3 + j)->isValuePossible(number)) {
                if (index == -1) {
                    index = i;
                } else if (index != i) {
                    return;
                }
            }
        }
    }

    if (index != -1) {
        removePossibleFromOtherSquares(number, index, idx);
    }
}

bool LogicalLane::processLane() {
    std::cout << "processLane for " + dbgName() + "(" + dbgIndex() + ")\n";
    for (int num = 1; num <= 9; num++) {
        std::cout << "... num: " << std::to_string(num) << std::endl;
        for (int group = 0; group < 3; group++) {
            std::cout << "... ... " + std::to_string(group) << std::endl;
            checkSquare(group, num);
        }
    }

    return true;
}