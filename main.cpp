/**
 * @file 	main.cpp
 * @version 0.027
 * @author 	Dominik Breksa
 * @date 	08.03.2023
 * @brief	Main source file.
**/

#include <iostream>
#include <fstream>

#include "includes/internal/headers/model/scanner.h"
//	#include "includes/internal/headers/common/run.h"

/**
 * @brief	Main function, that starts the program; expects the input to be in files to which location was provided in program arguments.
 *
 * @todo	Make the ability to save the output to a file
 *
 * @param	argc	How many argument ware given (starting from 1, because 0 is the .exe file name).
 * @param	argv	Vector of strings containing commandline arguments.
 * @return	0 - all went fine; 1 - not enough arguments were provided.
 */
int main(int argc, char* argv[]) {
	//Run::getInstance(argc, argv)(&std::cin, &std::cout);
	if (argc < 3) {
		std::cerr << "Not enough arguments provided!\n";
		exit(EXIT_FAILURE);
	}
	std::ifstream input_file(argv[1], std::ios::in);
	if (!input_file.is_open()) {
		std::cerr << "Error: could not open file\n";
		exit(EXIT_FAILURE);
	}
	std::ofstream output_file(argv[2], std::ios::out);
	if (!output_file.is_open()) {
		std::cerr << "Error: could not open file\n";
		exit(EXIT_FAILURE);
	}
	std::string line;
	output_file << "<!DOCTYPE html>\n<html lang=\"en\">\n\t<head>\n\t\t<meta charset=\"UTF-8\">\n\t\t<title>Output file of colouring process</title>\n\t</head>\n\t<body>"  << std::endl;
	Scanner s{};
	while(std::getline(input_file, line)) {
		line.push_back('\n');	//	std::getline(...) steals '\n' character
		s.addNextLine(line);
		output_file << s.processLine() << "<br>" <<std::endl;
	}
	output_file << "\t</body>\n</html>" << std::endl;
	input_file.close();
	output_file.close();
	return EXIT_SUCCESS;
}