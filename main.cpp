//
// Created by Dominik on 08.03.2023.
//
#include <iostream>
#include <fstream>
#include <thread>

#include "Scanner.h"
#include "Token.h"

int main(int argc, char *argv[]) {
	Token ta =Token("asdasdad", {0,0});
	std::cout << std::string(ta.getCode()) << ", " << get<std::string>(ta.getValue());
	exit(EXIT_FAILURE);

	if(argc < 2) {
		std::cout << "Not enough arguments given! Please provide a path to a file that you want to scan.";
		exit(EXIT_FAILURE);
	}

	std::string line;
	std::ifstream input_file(argv[1]);

	while(std::getline(input_file, line)) {
		Scanner s = Scanner(line);
		while(!s.isEmpty()) {
			Token t = s.getToken();
			std::cout << t;				//	std::cout << s.getToken();
		}
	}

	input_file.close();

	return EXIT_SUCCESS;
}