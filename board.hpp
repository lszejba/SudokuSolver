#ifndef __BOARD_HPP__
#define __BOARD_HPP__

class Field {
	public:
	private:
		bool isInitSet;
		int value;
		bool possibleValues[9];
};

class Board {
	public:
		void print();
		Board(const char *file);

	private:
		
};

#endif

