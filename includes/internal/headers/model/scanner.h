/**
 * @file 	model.h
 * @version 0.027
 * @author 	Dominik Breksa
 * @date 	08.03.2023
 * @brief	Header file relating to Scanner class.
 * @see		scanner.cpp
**/

#ifndef COMPILATION_THEORY_AND_COMPILERS_SCANNER_H
#define COMPILATION_THEORY_AND_COMPILERS_SCANNER_H

#include <optional>
#include <fstream>
#include <sstream>
#include <utility>

#include "token/token.h"
#include "automata/automata.h"
#include "../exceptions/unknown_symbol.h"
#include "../exceptions/error_state_reached.h"


/**
 * @brief	Scanner class is able to manage addition of new lines to DFA and changing its states in Automata object.
 *
 * @todo	Consider merging this class with Automata class as their functionalities are very similar. No need to have some variables twice in the memory.
 */
class Scanner {
public:
	/**
	 * @brief	Default constructor, starting input is empty. There is a need to use .addNextLine(...) method to be able to generate tokens.
	 */
	Scanner();
public:
	/**
	 * @brief	0x0 set sum with 0x1 converted to file stream from string_stream
	 * @return
	 */
	std::stringstream operator()(std::istream*, std::ostream*, std::string (BaseToken::*)() const);
	/**
	 * @brief	1x0 output string_stream convert to std::cout set sum nx0 for base example and concatenate string_stream set sum nx1 just concatenate to a file instead of a std::cout
	 * @return
	 */
	std::stringstream operator()(std::ifstream&, std::string (BaseToken::*)() const);
	/**
	 * @brief	nxn with n > 0 in a for loop n times
	 * @return
	 */
	void operator()(std::ifstream&, std::ofstream&, std::string (BaseToken::*)() const);
public:
	/**
	 * @brief	Changes the input attribute to
	 * @todo	Make that you cannot add new line, if this current one didn't finish being processed.
	 *
	 * @param	in	- The line that will be processed.
	 */
	void addNextLine(const std::string& in);
	/**
	 * @brief
	 * @return
	 */
	std::string processLine();
	/**
	 * @brief	Generates token from provided string.
	 *
	 * @return	Constructed token, ready to be parsed by another module.
	 */
	std::optional<std::unique_ptr<BaseToken>> getToken();
public:
	/**
	 * @brief	Method used to check the status of token generation process. If it has finished processing provided line.
	 * @return	True / false if this abject is ready for adding next line.
	 */
	bool isEmpty();
private:	//	Empty space for private class methods.

	public:
		/**
		 * @brief	Simple static variable to better understand certain assignments (mainly relating to col_index attribute).
		 */
		const static std::size_t RESET_INDEX = 0;
	private:
		/**
		 * @brief
		 */
		std::string input;
		/**
		 * @brief	Second parameter. Column number counting from 1 to n. Aka which character counting form left this object is referring.
		 *
		 * @see		token.h file.
		 */
		std::size_t col_index;
		/**
		 * @brief	First parameter. Line number counting from 1 to m. Aka which line number counting from top this object is referring.
		 *
		 * @see		token.h file.
		 */
		std::size_t line_index;
		/**
		 * @brief
		 *
		 * @see		Automata class.
		 * @see		automata.h file.
		 */
		Automata A;
};


#endif	//	COMPILATION_THEORY_AND_COMPILERS_SCANNER_H
