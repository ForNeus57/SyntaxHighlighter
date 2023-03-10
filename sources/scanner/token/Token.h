//
// Created by Dominik on 08.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_TOKEN_H
#define COMPILATION_THEORY_AND_COMPILERS_TOKEN_H

#include <iostream>
#include <variant>
#include <string>

#include "CodeType.h"

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
	Token(std::variant<int, char, std::string> v, Attributes aa);
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
	Attributes getAttribute() const;
private:
	CodeType code;
	std::variant<int, char, std::string> value;
	Attributes attribute;
};

#endif	//	COMPILATION_THEORY_AND_COMPILERS_TOKEN_H
