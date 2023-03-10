//
// Created by Dominik on 09.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_INPUT_ALPHABET_H
#define COMPILATION_THEORY_AND_COMPILERS_INPUT_ALPHABET_H

#include <iostream>

#include "WrongInputAlphabet.h"

/**
 * @brief
 *
 * @todo	FIX THIS BLOCK COMMENT
 *
 * @param	PLUS			- Equivalent to '+' character, code: 0
 * @param	MINUS			- Equivalent to '-' character, code: 1
 * @param	TIMES			- Equivalent to '*' character, code: 2
 * @param	DIVIDED			- Equivalent to '/' character, code: 3
 * @param	LEFT_BRACKET	- Equivalent to '(' character, code: 4
 * @param	RIGHT_BRACKET	- Equivalent to ')' character, code: 5
 * @param	INTEGER_NUMBER	- Equivalent to any integer number
 * @param	IDENTIFIER		-
 */
enum class Codes {
	LEFT_BRACKET,
	RIGHT_BRACKET,
	TIMES,
	PLUS,
	MINUS,
	DIVIDED,
	INTEGER_NUMBER,
	IDENTIFIER
};

/**
 * @brief	Since the functionalities of enum of C++ are very limited here is a class, that wraps it and supplements this needs.
 *
 * @see		Codes
 */
class CodeType {
public:
	/**
	 *
	 * @param c
	 */
	explicit CodeType(Codes c);
	/**
	 *
	 * @param c
	 */
	explicit CodeType(char c);
public:
	/**
	 * @brief
	 * @return
	 */
	explicit operator std::string() const;
public:
	/**
	 * @brief
	 *
	 * @throws	WrongInputAlphabet
	 *
	 * @return
	 */
	static Codes translateInput(char);
public:
	/**
	 *
	 * @return
	 */
	Codes getCode();
public:
	const static std::size_t INPUT_ALPHABET_LENGTH = 8;
private:
	/**
	 *
	 */
	Codes code;
};


#endif //COMPILATION_THEORY_AND_COMPILERS_INPUT_ALPHABET_H
