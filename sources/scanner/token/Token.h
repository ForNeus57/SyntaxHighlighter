//
// Created by Dominik on 08.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_TOKEN_H
#define COMPILATION_THEORY_AND_COMPILERS_TOKEN_H

#include <iostream>
#include <variant>
#include <string>

#include "WrongInputAlphabet.h"

/**
 * @brief
 *
 * @todo	FIX THIS BLOCK COMMENT
 *
 * @param	PLUS					- Equivalent to '+' character, code: 0
 * @param	MINUS					- Equivalent to '-' character, code: 1
 * @param	TIMES					- Equivalent to '*' character, code: 2
 * @param	DIVIDED					- Equivalent to '/' character, code: 3
 * @param	LEFT_BRACKET			- Equivalent to '(' character, code: 4
 * @param	RIGHT_BRACKET			- Equivalent to ')' character, code: 5
 * @param	UNSIGNED_INTEGER_NUMBER	- Equivalent to any integer number
 * @param	IDENTIFIER				-
 */
enum class Codes {
	LEFT_BRACKET,
	RIGHT_BRACKET,
	TIMES,
	PLUS,
	MINUS,
	DIVIDED,
	UNSIGNED_INTEGER_NUMBER,
	IDENTIFIER
};


/**
 * @brief	Simple struct, that contains all the attributes that we want to assign to Token;
 *
 * @param 	cols - column number counting from 0 to n. Aka which character counting form left this object is referring.
 * @param 	rows - row number counting from 0 to m. Aka which line number counting from top this object is referring.
 */
struct Attributes {
	std::size_t cols = 0, rows = 0;
};

class Token {
public:
	/**
	 * @brief	Constructor for this class...
	 *
	 * @todo	Make this peace of documentation more descriptive.
	 *
	 * @param	v	- From this parameter the Token code is deducted.
	 * @param	a	- All other necessary data i.e. for error handling.
	 */
	Token(Codes c, std::variant<unsigned int, char, std::string> v, Attributes a);
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

private:
	std::string printCodes() const;
public:
	const static std::string INPUT_ALPHABET;
	const static std::size_t CODE_SIZE = 8;
private:
	Codes code;
	std::variant<unsigned int, char, std::string> value;
	Attributes attribute;
};

/**
 * @brief
 *
 * @todo	Make such if string values aren't 0987654321 the exception is thrown.
 *
 * @param	in
 * @return
 */
std::variant<unsigned int, char, std::string> pars_unsigned_integer(std::string);
/**
 * @brief
 * @return
 */
std::variant<unsigned int, char, std::string> pars_identifier(std::string);
/**
 * @brief
 *
 * @todo Make such that if this string is longer then single character the exception should be thrown.
 *
 * @param 	in
 * @return
 */
std::variant<unsigned int, char, std::string> pars_single_value_tokens(std::string);


#endif	//	COMPILATION_THEORY_AND_COMPILERS_TOKEN_H
