#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include "field.hpp"

class Group {
	public:
	private:
};

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

	private:
		void setFields(const char *buffer);
		Field *fields[81];

};

#endif

