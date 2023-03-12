//
// Created by Dominik on 08.03.2023.
//
#include <iostream>
#include <fstream>
#include <thread>

#include "Scanner.h"
#include "Token.h"

int main(int argc, char *argv[]) {
	if(argc < 2) {
		std::cout << "Not enough arguments given! Please provide a path to a file that you want to scan.";
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i < argc; ++i) {
		std::cout << "FILE: " << argv[i] << i << '\n' << '\n';
		std::size_t line_number = 1;
		std::string line;
		std::ifstream input_file(argv[i]);
		while(std::getline(input_file, line)) {
			Scanner s = Scanner(line_number, line);
			while(!s.isEmpty()) {
				Token t = s.getToken();
				std::cout << t << '\n';				//	std::cout << s.getToken() << '\n';
			}
			line_number++;
		}
		input_file.close();
	}
	return EXIT_SUCCESS;
}