/**
 * @file 	main.cpp
 * @version 0.027
 * @author 	Dominik Breksa, dominikbreksa@gmail.com
 * @date 	08.03.2023
 * @brief	Main source file.
**/

#include <iostream>

//#include "includes/syntax_colorizer_lib/headers/common/run.h"

/**
 * @brief	Main function, that starts the program; expects the input to be in files to which location was provided in program arguments.
 *
 * @todo	Make the ability to take data for model and others from standard input like console.
 * @todo	Make the ability to save the output to a file
 * @todo	Add statistics how many correct tokens have been found in a provided file or console input.
 * @todo	Implement model class as an different thread separated from for example parsing, so that the parsing isn't stopped for producing next token.
 *
 * @param	argc	How many argument ware given (starting from 1, because 0 is the .exe file name).
 * @param	argv	Vector of strings containing commandline arguments.
 * @return	0 - all went fine; 1 - not enough arguments were provided.
 */
int main() {
	//Run::getInstance(argc, argv)(&std::cin, &std::cout);
	return EXIT_SUCCESS;
}