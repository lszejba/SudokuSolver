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
		Board(const char *file);

	private:
		Field fields[81];

};

#endif

