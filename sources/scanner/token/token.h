/**
 * @file 	token.h
 * @version 0.027
 * @author 	Dominik Breksa
 * @date 	08.03.2023
 * @brief	Header file relating to Token class.
 * @see		token.cpp
**/

#ifndef COMPILATION_THEORY_AND_COMPILERS_TOKEN_H
#define COMPILATION_THEORY_AND_COMPILERS_TOKEN_H

#include <iostream>
#include <variant>
#include <string>
#include <vector>

#include "wrong_input_alphabet.h"

/**
 * @brief	Simple enum that is used to store code for the token.
 *
 * @todo	FIX THIS BLOCK COMMENT
 * @todo	ADD ITERATOR TO THIS ENUM, SUCH THAT ++ returns next element.
 *
 *
 * @param	PLUS					- Equivalent to '+' character, code: 0
 * @param	MINUS					- Equivalent to '-' character, code: 1
 * @param	TIMES					- Equivalent to '*' character, code: 2
 * @param	DIVIDED					- Equivalent to '/' character, code: 3
 * @param	LEFT_BRACKET			- Equivalent to '(' character, code: 4
 * @param	RIGHT_BRACKET			- Equivalent to ')' character, code: 5
 * @param	UNSIGNED_INTEGER_NUMBER	- Equivalent to any integer number
 * @param	IDENTIFIER				-
 * @param	UNKNOWN					- This code value suggests, that
 */
enum class Codes {
	LEFT_BRACKET,
	RIGHT_BRACKET,
	TIMES,
	PLUS,
	MINUS,
	DIVIDED,
	UNSIGNED_INTEGER_NUMBER,
	IDENTIFIER,
	UNKNOWN
};

using Attributes = std::pair<std::size_t, std::size_t>;

/**
 * @brief	Implementation of Token class,
 * @param	code
 * @param 	value
 * @param	attribute
 */
class Token {
public:
	/**
	 * @brief	Constructor for this class...
	 *
	 * @todo	Make this peace of documentation more descriptive.
	 * @todo	Make such if we try to create a token with wrong code (Codes::UNKNOWN), the error is thrown.
	 *
	 * @param	s	- From this parameter the Token code is deducted.
	 * @param	a	- All other necessary data i.e. for error handling.
	 */
	Token(Codes c, std::string s, Attributes a);
public:
	/**
	 * @brief
	 * @return
	 */
	explicit operator std::string() const;
	/**
	 * @brief
	 * @param	os
	 * @param	other
	 * @return
	 */
	friend std::ostream& operator<<(std::ostream& os, const Token& other) {
		return os << std::string(other);
	}
public:
	Codes getCode() const;
	std::variant<unsigned int, char, std::string> getValue() const;
	Attributes getAttribute() const;
public:
	const static std::string INPUT_ALPHABET;
	const static std::vector<Codes> CODES_TYPES;
private:
	Codes code;
	std::variant<unsigned int, char, std::string> value;
	/**
	 * @brief	Simple struct, that contains all the attributes that we want to assign to Token;
	 *
	 * @param 	line	- First parameter. Line number counting from 1 to m. Aka which line number counting from top this object is referring.
	 * @param 	col		- Second parameter. Column number counting from 1 to n. Aka which character counting form left this object is referring.
	 */
	Attributes attribute;
};


#endif	//	COMPILATION_THEORY_AND_COMPILERS_TOKEN_H
