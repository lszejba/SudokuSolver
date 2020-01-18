#include <iostream>
#include "board.hpp"
#include "field.hpp"

Board::Board(const char *buffer) {
    setFields(buffer);
}

std::string Board::print() {
    std::string res = "";
	for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            res += fields[j + i * 9]->print();
        }
        res += '\n';
    }

    return res;
}

void Board::setFields(const char *buffer) {
    int i = 0, count = 0;;
    while(buffer[i] != '\0') {
        if (buffer[i] != ';') {
            int val = (int)((char)buffer[i] - '0');
            fields[count] = new Field(val);
            count++;
        }
        i++;
    }
}