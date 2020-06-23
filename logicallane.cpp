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
        std::cout << "### Remove from other squares(" + std::to_string(number) + ", " << std::to_string(index) + ", " << std::to_string(idx) << ")" << std::endl;
        removePossibleFromOtherSquares(number, index, idx);
    }
}

void LogicalLane::processLane() {
    for (int num = 1; num <= 9; num++) {
        for (int group = 0; group < 3; group++) {
            checkSquare(group, num);
        }
    }
}