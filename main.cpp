#include <iostream>
#include <fstream>

#include "scanner.h"
#include "token.h"

int main(int argc, char *argv[]) {
	if(argc < 2) {
		std::cout << "Not enough arguments given! Please provide a path to a file that you want to scan.";
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i < argc; ++i) {
		std::cout << "FILE: " << argv[i] << i << '\n' << '\n';
		std::string line;
		std::ifstream input_file(argv[i]);
		Scanner s = Scanner();
		while(std::getline(input_file, line)) {
			s.addNextLine(line);
			while(!s.isEmpty()) {
				Token t = s.getToken();
				std::cout << t << '\n';				//	std::cout << s.getToken() << '\n';
			}
		}
		input_file.close();
	}
	return EXIT_SUCCESS;
}