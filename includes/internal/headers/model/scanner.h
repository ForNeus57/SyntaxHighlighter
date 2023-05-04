/**
 * @file 	model.h
 * @version 0.027
 * @author 	Dominik Breksa, dominikbreksa@gmail.com
 * @date 	08.03.2023
 * @brief	Header file relating to Scanner class.
 * @see		model.cpp
**/

#ifndef COMPILATION_THEORY_AND_COMPILERS_SCANNER_H
#define COMPILATION_THEORY_AND_COMPILERS_SCANNER_H

#include <optional>
#include <fstream>
#include <sstream>
#include <utility>

#include "token/token.h"
#include "automata/automata.h"
#include "scanner.h"
#include "../common/statistics.h"


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
	std::stringstream operator()(std::istream*, std::ostream*, std::string (Token::*)() const);
	/**
	 * @brief	1x0 output string_stream convert to std::cout set sum nx0 for base example and concatenate string_stream set sum nx1 just concatenate to a file instead of a std::cout
	 * @return
	 */
	std::stringstream operator()(std::ifstream&, std::string (Token::*)() const);
	/**
	 * @brief	nxn with n > 0 in a for loop n times
	 * @return
	 */
	void operator()(std::ifstream&, std::ofstream&, std::string (Token::*)() const);
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
	std::string processLine(std::string (Token::*format)() const);
	/**
	 * @brief	Generates token from provided string.
	 * @todo	Make such that we cannot try to generate token out of empty string(because in that case created token can be unpredictable - Token::UNKNOWN).
	 *
	 * @todo 	fdsnaddajusdsajdasdsadas Make such all the white space is translated imidietly, becouse non of the tokens is using white space -> imidiet stop ......
	 *
	 * @return	Constructed token, ready to be parsed by another module.
	 */
	std::optional<Token> getToken();
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
		 */
		Automata A;
};


#endif	//	COMPILATION_THEORY_AND_COMPILERS_SCANNER_H
