#ifndef __BOARD_HPP__
#define __BOARD_HPP__

class Field {
	public:
		void addPossibleValue(int value);
		void removePossibleValue(int value);
		std::string print();
		int getValue();
	private:
		bool isInitSet;
		int value;
		bool possibleValues[9];
};

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

