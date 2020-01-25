#include <iostream>
#include "board.hpp"
#include "field.hpp"

Board::Board(const char *buffer) {
    setFields(buffer);
}

std::string Board::print() {
    std::string res = "";
    res += "+---+---+---+\n";
	for (int i = 0; i < 9; i++) {
        res += "|";
        for (int j = 0; j < 9; j++) {
            res += m_fields[j + i * 9]->print();
            if ((j + 1) % 3 == 0) {
                res += "|";
            }
        }
        res += '\n';
        if ((i + 1) % 3 == 0) {
            res += "+---+---+---+\n";
        }
    }

    res += "\nFields:\n";

    for (int i = 0; i < 81; i++) {
        res += m_fields[i]->debugPrint();
    }

    return res;
}

void Board::setFields(const char *buffer) {
    int i = 0, count = 0;;
    while(buffer[i] != '\0') {
        if (buffer[i] != ';') {
            int val = (int)((char)buffer[i] - '0');
            m_fields[count] = new Field(val, count / 9, count % 9);
            count++;
        }
        i++;
    }
}