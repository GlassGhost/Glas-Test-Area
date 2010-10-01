#include <iostream>
#include <fstream>

int main (int argc, char * const argv[]) {
	std::ofstream txtout("./txtout.txt", std::ios::app);
	txtout << "ALL YOUR BASE ARE BELONG TO US!\n";
	txtout.close();
	return 0;
}