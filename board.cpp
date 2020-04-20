#include <iostream>
#include "board.hpp"
#include "field.hpp"
#include "group.hpp"
#include "logicallane.hpp"

Board::Board(const char *buffer) {
    std::cout << "[LOG] Board init start" << std::endl;
    std::cout << "[LOG] |" << buffer << "|" << std::endl;
    setFields(buffer);
    setAllGroups();
    std::cout << "[LOG] Board init done" << std::endl;
}

std::string Board::print() {
    std::string res = "";
    res += "+---+---+---+\n";
    std::cout << res;
	for (int i = 0; i < 9; i++) {
        res += "|";
        for (int j = 0; j < 9; j++) {
            res += m_fields[j + i * 9]->print();
            if ((j + 1) % 3 == 0) {
                res += "|";
            }
        }
        res += '\n';
        std::cout << res;
        if ((i + 1) % 3 == 0) {
            res += "+---+---+---+\n";
        }
        std::cout << res;
    }

//    res += "\nFields:\n";

//    for (int i = 0; i < 81; i++) {
//        res += m_fields[i]->debugPrint();
//    }

    return res;
}

void Board::setFields(const char *buffer) {
    std::cout << "setFields()" << std::endl;
    if (buffer == NULL) {
        std::cout << "Buffer is NULL\n";
    } else {
        std::cout << "buffer: |" << buffer << "|" << std::endl;
    }
    int i = 0, count = 0;;
    while(buffer[i] != '\0') {
        if (buffer[i] != ';') {
            int val = (int)((char)buffer[i] - '0');
            m_fields[count] = new Field(/*val, */count / 9, count % 9);
            m_fields[count]->setValue(val, true);
            std::cout << "field added: " << std::to_string(val) << " (" << std::to_string(count) << ")\n";
            count++;
        }
        i++;
    }
}

void Board::setAllGroups() {
    //rows
    for (int i = 0; i < 9; i++) {
        Row row(i);
        for (int j = 0; j < 9; j++) {
            row.addField(m_fields[i * 9 + j]);
        }
        m_rows.push_back(row);
    }

    //logical rows
    for (int i = 0; i < 3; i++) {
        LogicalRow lRow(i);
        for (int j = 0; j < 3; j++) {
            lRow.addGroup(&(m_rows[i * 3 + j]));
        }
        m_logicalRows.push_back(lRow);
    }

    //columns
    for (int i = 0; i < 9; i++) {
        Column column(i);
        for (int j = 0; j < 9; j++) {
            column.addField(m_fields[i + j * 9]);
        }
        m_columns.push_back(column);
    }

    //logical columns
    for (int i = 0; i < 3; i++) {
        LogicalColumn lCol(i);
        for (int j = 0; j < 3; j++) {
            lCol.addGroup(&(m_columns[i * 3 + j]));
        }
    }

    //squares
    for (int i1 = 0; i1 < 3; i1++) {
        for (int j1 = 0; j1 < 3; j1++) {
            Square square(i1 * 3 + j1);
//            std::cout << "Group start" << std::endl;
            for (int i2 = 0; i2 < 3; i2++) {
                for (int j2 = 0; j2 < 3; j2++) {
 //                   std::cout << "\t" << m_fields[i1 *3 + i2 + 9 * (j1 * 3+ j2)]->debugPrintCoordinates();
                    square.addField(m_fields[i1 * 3 + i2 + 9 * (j1 * 3+ j2)]);
                }
            }
//            std::cout << "Group end" << std::endl;
            m_squares.push_back(square);
        }
    }
}

bool Board::refreshPossibleFields() {
    bool res = false;
    for (auto it : m_rows) {
        res |= it.processGroup();
    }
//    std::cout << "\n---\nAfter processing rows\n---\n";
//    std::cout << print() << std::endl;

    for (auto it : m_columns) {
        res |= it.processGroup();
    }
//    std::cout << "\n---\nAfter processing columns\n---\n";
//    std::cout << print() << std::endl;

    for (auto it : m_squares) {
        res |= it.processGroup();
    }
//    std::cout << "\n---\nAfter processing squares\n---\n";

    for (auto it : m_logicalRows) {
        res |= it.processLane();
    }

    for (auto it : m_logicalColumns) {
        res |= it.processLane();
    }
    std::cout << print() << std::endl;

    return res;
}
