#include <iostream>
#include <fstream>
#include <cstring>
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
	char output1[256];
	memset(output1, 0, sizeof(output1));
	char output[256];
	if (file.is_open()) {
		while(!file.eof()) {
			file >> output;
		}
	}
	memcpy(output1, output, sizeof(output));
	file.close();
	cout << "[LOG] Output |" << output << "|" << endl;
	Board board(output1);
	cout << "[LOG] Board: \n" << board.print() << endl;

	bool continueWork = true;
	int rounds = 0;
	while(continueWork) {
		continueWork = board.refreshPossibleFields();
		rounds++;
	}

	std::cout << board.print() << std::endl;
	std::cout << "\nDone in " + std::to_string(rounds) << " rounds\n";

	return 0;
}
