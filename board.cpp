#include <iostream>
#include "board.hpp"
#include "field.hpp"
#include "group.hpp"
#include "logicallane.hpp"

Board::Board(const char *buffer) {
    std::cout << "[LOG] Board init start" << std::endl;
    std::cout << "[LOG] |" << buffer << "|" << std::endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            m_fields[i * 9 + j] = new Field(i, j);
        }
    }
    setAllGroups();
    setFields(buffer);
    std::cout << "[LOG] Board init done" << std::endl;
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

    // print all fields
    res += "\n";
    for (int i = 0; i < 81; i++) {
        res += m_fields[i]->debugPrint();
    }
    res += "\n";

    return res;
}

void Board::setFields(const char *buffer) {
    int i = 0, count = 0;;
    while(buffer[i] != '\0') {
        if (buffer[i] != ';') {
            int val = (int)((char)buffer[i] - '0');
//            m_fields[count] = new Field(count / 9, count % 9);
            m_fields[count]->setValue(val/*, true*/);
            count++;
        }
        i++;
    }
}

void Board::setAllGroups() {
    //rows
    for (int i = 0; i < 9; i++) {
        Row *row = new Row(i);
        for (int j = 0; j < 9; j++) {
            row->addField(m_fields[i * 9 + j]);
            m_fields[i * 9 + j]->addOwner(row);
        }
        m_rows.push_back(row);
    }

    //logical rows
    for (int i = 0; i < 3; i++) {
        LogicalRow *lRow = new LogicalRow(i);
        for (int j = 0; j < 3; j++) {
            lRow->addGroup(m_rows[i * 3 + j]);
        }
        m_logicalRows.push_back(lRow);
    }

    //columns
    for (int i = 0; i < 9; i++) {
        Column *column = new Column(i);
        for (int j = 0; j < 9; j++) {
            column->addField(m_fields[i + j * 9]);
            m_fields[i + j * 9]->addOwner(column);
        }
        m_columns.push_back(column);
    }

    //logical columns
    for (int i = 0; i < 3; i++) {
        LogicalColumn *lCol = new LogicalColumn(i);
        for (int j = 0; j < 3; j++) {
            lCol->addGroup(m_columns[i * 3 + j]);
        }
    }

    //squares
    for (int i1 = 0; i1 < 3; i1++) {
        for (int j1 = 0; j1 < 3; j1++) {
            Square *square = new Square(i1 * 3 + j1);
            for (int i2 = 0; i2 < 3; i2++) {
                for (int j2 = 0; j2 < 3; j2++) {
                    square->addField(m_fields[i1 * 3 + i2 + 9 * (j1 * 3+ j2)]);
                    m_fields[i1 * 3 + i2 + 9 *(j1 * 3 + j2)]->addOwner(square);
                }
            }
            m_squares.push_back(square);
        }
    }
}

void Board::refreshPossibleFields() {
/*    for (auto it : m_rows) {
        res |= it->processGroup();
        if (res) {
            return true;
        }
    }

    for (auto it : m_columns) {
        res |= it->processGroup();
        if (res) {
            return true;
        }
    }

    for (auto it : m_squares) {
        res |= it->processGroup();
        if (res) {
            return true;
        }
    } */

    for (auto it : m_logicalRows) {
        it->processLane();
    }

    for (auto it : m_logicalColumns) {
        it->processLane();
    }
}

std::string Board::dbgPrint() {
    std::string res = "";
    for (int i = 0; i < 81; i++) {
        res += m_fields[i]->debugPrint();
    }

    return res;
}