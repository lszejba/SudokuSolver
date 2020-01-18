#include <iostream>
#include <fstream>
#include "board.hpp"

using namespace std;

class SudokuBoard {
	public:
		void print();
		SudokuBoard(const char *file);

	private:
		
};

int main(int argc, char **argv) {
	if (argc <= 1) {
		cout << "No filename provided" << endl;
		return -1;
	}
	// read file
	ifstream file;
	cout << "Opening file " << argv[1] << endl;
	file.open(argv[1]);
	char output[256];
	if (file.is_open()) {
		while(!file.eof()) {
			file >> output;
		}
	}
	file.close();
	cout << "Output |" << output << "|" << endl;
	Board board(output);
	cout << "Board: \n" << board.print() << endl;

	return 0;
}
