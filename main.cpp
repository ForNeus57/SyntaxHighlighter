/**
 * @file 	main.cpp
 * @version 0.027
 * @author 	Dominik Breksa, dominikbreksa@gmail.com
 * @date 	08.03.2023
 * @brief	Main source file.
**/

#include <iostream>
#include <fstream>

#include "scanner.h"
#include "token.h"

/**
 * @brief	Main function, that starts the program; expects the input to be in files to which location was provided in program arguments.
 *
 * @todo	Make the ability to take data for scanner and others from standard input like console.
 * @todo	Make the ability to save the output to a file
 * @todo	Add statistics how many correct tokens have been found in a provided file or console input.
 * @todo	Implement scanner class as an different thread separated from for example parsing, so that the parsing isn't stopped for producing next token.
 *
 * @param	argc	How many argument ware given (starting from 1, because 0 is the .exe file name).
 * @param	argv	Vector of strings containing commandline arguments.
 * @return	0 - all went fine; 1 - not enough arguments were provided.
 */
int main(int argc, char *argv[]) {
	if(argc < 2) {										//	Make sure, that there are arguments passed when executing this program.
		std::cout << "Not enough commandline arguments given! Please provide a path to a file that you want to scan.";
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i < argc; ++i) {						//	Iterate over all the file provided in arguments.
		std::cout << "\nFILE: " << argv[i] << "\nFILE NUMBER: " << i << "\nGENERATED TOKENS:\n" << '\n';
		std::string line;
		std::ifstream input_file(argv[i]);
		Scanner s = Scanner();							//	Create a new scanner to clear memory. It isn't needed, but to be 100% sure nothing wasn't passed from previous files.
		while(std::getline(input_file, line)) {	//	Go through all the lines of a given file.
			s.addNextLine(line);
			while(!s.isEmpty()) {						//	Generate all the tokens in this line.
				Token t = s.getToken();					//	I use a method call instead of a function, but I think, that it isn't much of a problem.
				std::cout << t << '\n';					//	Could be swapped to: std::cout << s.getToken() << '\n';
			}
		}
		input_file.close();								//	Close the file after the use.
	}
	return EXIT_SUCCESS;
}