//
// Created by Dominik on 08.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_TOKEN_H
#define COMPILATION_THEORY_AND_COMPILERS_TOKEN_H

#include <iostream>
#include <variant>

/**
 *	@param	PLUS			- Equivalent to '+' character, code: 0
 *	@param	MINUS			- Equivalent to '-' character, code: 0
 *	@param	TIMES			- Equivalent to '*' character, code: 0
 *	@param	DIVIDED			- Equivalent to '/' character, code: 0
 *	@param	LEFT_BRACKET	- Equivalent to '(' character, code: 0
 *	@param	RIGHT_BRACKET	- Equivalent to ')' character, code: 0
 *	@param	INTEGER_NUMBER	-
 *	@param	IDENTIFIER		-
 */
enum class CodeType {
	PLUS = 0,
	MINUS = 1,
	TIMES = 2,
	DIVIDED = 3,
	LEFT_BRACKET = 4,
	RIGHT_BRACKET = 5,
	INTEGER_NUMBER = 6,
	IDENTIFIER = 7
};

struct Position {
	unsigned int x, y;
};

class Token {
public:
	/**
	 *
	 *	@param i
	 *	@param p
	 */
	Token(int i, Position p);
	/**
	 *
	 *	@param t
	 *	@param p
	 */
	Token(CodeType t, Position p);
public:
	explicit operator std::string() const;
	friend std::ostream& operator<<(std::ostream& os, const Token& obj) {
		os << std::string(obj);
		return os;
	}
public:
	CodeType getCode();
	std::variant<int, std::string> getValue();
	Position getPosition();
private:

public:
	const std::string description;
	const std::string comments;
private:
	CodeType code;
	std::variant<int, std::string> value;
	Position attribute;
};

#endif	//	COMPILATION_THEORY_AND_COMPILERS_TOKEN_H
