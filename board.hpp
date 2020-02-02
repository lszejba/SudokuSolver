#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include "field.hpp"
#include "group.hpp"

class VLane {
	public:
	private:

};

class HLane {
	public:
	private:
};

class Board {
	public:
		std::string print();
		Board(const char *buffer);
		bool refreshPossibleFields();

	private:
		void setFields(const char *buffer);
		void setAllGroups();

		Field *m_fields[81];
		std::vector<Row> m_rows;
		std::vector<Column> m_columns;
		std::vector<Square> m_squares;
};

#endif

