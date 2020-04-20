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

bool LogicalLane::removePossibleFromOtherSquares(int number, int groupIdx, int ownerIdx) {
    bool result = false;
    for (int i = 0; i < 3; i++) {
        if (i == ownerIdx) {
            continue;
        }
        for (int j = 0; j < 3; j++) {
            result |= m_groups[groupIdx]->getField(i * 3 + j)->removePossibleValue(number);
        }
    }

    return result;
}

bool LogicalLane::checkSquare(int idx, int number) {
    int index = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (m_groups[i]->getField(idx * 3 + j)->getValue() == number) {
                return false;
            }
            if (m_groups[i]->getField(idx * 3 + j)->isValuePossible(number)) {
                if (index == -1) {
                    index = i;
                } else if (index != i) {
                    return false;
                }
            }
        }
    }

    bool result = false;
    if (index != -1) {
        result = removePossibleFromOtherSquares(number, index, idx);
    }

    return result;
}

bool LogicalLane::processLane() {
    bool result = false;
    for (int num = 1; num <= 9; num++) {
        for (int group = 0; group < 3; group++) {
            result |= checkSquare(group, num);
        }
    }

    return result;
}