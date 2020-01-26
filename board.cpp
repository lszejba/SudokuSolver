#include <iostream>
#include "board.hpp"
#include "field.hpp"
#include "group.hpp"

Board::Board(const char *buffer) {
    setFields(buffer);
    setAllGroups();
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

void Board::setAllGroups() {
    //rows
    for (int i = 0; i < 9; i++) {
        Group row;
        for (int j = 0; j < 9; j++) {
            row.addField(m_fields[i * 9 + j]);
        }
        m_rows.push_back(row);
    }

    //columns
    for (int i = 0; i < 9; i++) {
        Group column;
        for (int j = 0; j < 9; j++) {
            column.addField(m_fields[i + j * 9]);
        }
        m_columns.push_back(column);
    }

    //squares
    // TODO
}

bool Board::refreshPossibleFields() {
    for (auto it : m_rows) {
        it.processGroup();
    }
    std::cout << "\n---\nAfter processing rows\n---\n";
    std::cout << print() << std::endl;

    for (auto it : m_columns) {
        it.processGroup();
    }
    std::cout << "\n---\nAfter processing columns\n---\n";
    std::cout << print() << std::endl;

    return true;
}
