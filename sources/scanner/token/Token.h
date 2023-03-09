//
// Created by Dominik on 08.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_TOKEN_H
#define COMPILATION_THEORY_AND_COMPILERS_TOKEN_H

#include <iostream>
#include <variant>

#define CODE_TYPE_SIZE 8

/**
 * @brief
 *
 * @todo	Fix the assigned
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

/**
 * @brief
 *
 * @param 	x
 * @param 	y
 */
struct Position {
	std::size_t x = 0, y = 0;
};

class Token {
public:
	/**
	 * @brief
	 * @param	v
	 * @param	coordinates
	 */
	Token(std::variant<int, char, std::string> v, Position coordinates);
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
	CodeType getCode() const;
	std::variant<int, char, std::string> getValue() const;
	Position getAttribute() const;
private:
	CodeType code;
	std::variant<int, char, std::string> value;
	Position attribute;
};

#endif	//	COMPILATION_THEORY_AND_COMPILERS_TOKEN_H
