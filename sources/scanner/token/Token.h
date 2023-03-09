//
// Created by Dominik on 08.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_TOKEN_H
#define COMPILATION_THEORY_AND_COMPILERS_TOKEN_H

#include <iostream>
#include <variant>

#include "InputAlphabet.h"

/**
 * @brief
 *
 * @param 	x
 * @param 	y
 */
struct Attributes {
	std::size_t cols = 0, rows = 0;
};

class Token {
public:
	/**
	 * @brief
	 * @param	v
	 * @param	attributes
	 */
	Token(std::variant<int, char, std::string> v, Attributes attribute);
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
