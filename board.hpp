#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include "field.hpp"
#include "group.hpp"
#include "logicallane.hpp"

// class VLane {
// 	public:
// 	private:

// };

// class HLane {
// 	public:
// 	private:
// };

class Board {
	public:
		std::string print();
		Board(const char *buffer);
		void refreshPossibleFields();
		std::string dbgPrint();

	private:
		void setFields(const char *buffer);
		void setAllGroups();

		Field *m_fields[81];
		std::vector<Row *> m_rows;
		std::vector<Column *> m_columns;
		std::vector<Square *> m_squares;
		std::vector<LogicalRow *> m_logicalRows;
		std::vector<LogicalColumn *> m_logicalColumns;
};

#endif

