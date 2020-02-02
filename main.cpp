#include <iostream>
#include <fstream>
#include "board.hpp"

using namespace std;

int main(int argc, char **argv) {
	if (argc <= 1) {
		cout << "No filename provided" << endl;
		return -1;
	}
	// read file
	ifstream file;
	cout << "[LOG] Opening file " << argv[1] << endl;
	file.open(argv[1]);
	char output[256];
	if (file.is_open()) {
		while(!file.eof()) {
			file >> output;
		}
	}
	file.close();
	cout << "[LOG] Output |" << output << "|" << endl;
	Board board(output);
	cout << "[LOG] Board: \n" << board.print() << endl;

	for (int i = 0; i < 5; i++) {
		board.refreshPossibleFields();
	}

	int counter = 1;
	do {
		std::cout << "[LOG] Round " << counter++ << std::endl;
	} while(board.refreshPossibleFields());

	std::cout << "[LOG] Nothing more to do\n";

	return 0;
}
