//
// Created by Dominik on 09.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_INPUT_ALPHABET_H
#define COMPILATION_THEORY_AND_COMPILERS_INPUT_ALPHABET_H

#include <iostream>

#define CODE_TYPE_SIZE 8

/**
 * @brief
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
enum CodeType {
	LEFT_BRACKET	= '(',
	RIGHT_BRACKET	= ')',
	TIMES			= '*',
	PLUS			= '+',
	MINUS			= '-',
	DIVIDED			= '/',
	INTEGER_NUMBER	= '0',
	IDENTIFIER		= 'i'
};
/**
 * @param 	type
 * @return
 */
std::string printCodeType(CodeType type);


#endif //COMPILATION_THEORY_AND_COMPILERS_INPUT_ALPHABET_H
