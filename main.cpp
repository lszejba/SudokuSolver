#include <iostream>
#include <fstream>

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
			cout << output << endl;
		}
	}
	file.close();
	cout << "Output |" << output << "|" << endl;

	return 0;
}
