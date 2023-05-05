/**
 * @file 	token.h
 * @version 0.027
 * @author 	Dominik Breksa
 * @date 	08.03.2023
 * @brief	Header file relating to Token class.
 * @see		token.cpp file.
**/

#ifndef COMPILATION_THEORY_AND_COMPILERS_TOKEN_H
#define COMPILATION_THEORY_AND_COMPILERS_TOKEN_H


#include <iostream>
#include <string>

#include "base_token.h"


/**
 * @brief	Token class is meant to represent model token used for parsing code.
 * @note	It is an extension to a Codes enum, because their modularity is very limiting in C++, however it adds the ability to process token value and locate errors.
 *
 * @see		Codes enum.
 * @see		Alphabet enum.
 * @see		Automata class.
 */
template<typename T>
class Token final: public BaseToken {
	public:
		using ValueType = T;			//	Makes it easier to read.
	public:
		/**
		 * @brief	Constructor for this class. That assigns the value of the token based on the provided code.
		 *
		 * @param	code	- From this parameter the Token value is deducted.
		 * @param	value	- String that lead to creating a Token in Automata.
		 * @param	line	- All other necessary data i.e. location for error handling.
		 * @param	column	- ........
		 *
		 * @see		Automata class.
		 * @see		Codes enum.
		 */
		Token(BaseToken::Codes code, ValueType value, std::size_t line, std::size_t column);
		Token(const Token&) = default;
		Token(Token&&) noexcept = default;
		~Token() override = default;
	public:
		Token& operator=(const Token&) = default;
		Token& operator=(Token&&) noexcept = default;
		/**
		 * @brief	Operator that makes it easier to display the information of Token contents. It casts this class object to std::string.
		 *
		 * @return	std::string, that contains information about token features:
		 * 				"(code:{Some value from Codes enum}, value:{value of the token}, line:{line number}, col:{column number})"
		 */
		explicit operator std::string() const;
		/**
		 * @brief	Simple stream operator, to make it able to be printed into console.
		 * @param	os		- Output stream
		 * @param	other	- Some token object.
		 * @return	output stream back to the source.
		 */
		friend std::ostream& operator<<(std::ostream& os, const Token& other) { return os << std::string(other); }
	public:
		/**
		 * @brief	Simple getter for value of the Token.
		 * @return 	One of the following: uint, char or std::string elements.
		 */
		ValueType getValue() const;
	public:
		/**
		 * @brief
		 * @return
		 */
		std::string print() const override;
		/**
		 * @brief
		 * @return
		 */
		std::string printHTML() const override;
		/**
		 * @brief	Method ....
		 * @return 	The length of std::string(this->Value).size()
		 */
		std::size_t valueShift() const override;
		/**
		 * @brief
		 * @return 	this->print().size() - this->ValueShift()
		 */
		std::size_t printShift() const override;
		/**
		 * @brief
		 * @return	this->printHTML().size() - this->ValueShift()
		 */
		std::size_t printHTMLShift() const override;
	private:
		/**
		 * @brief	Value stored of a token.
		 * @note	It is 100% dependent on the previous attribute: Token::code. For example single value tokens are guaranteed to ba a char, UNSIGNED_INTEGER, unsigned integer and so on.
		 * @note	Why use std::variant<...>? Because this attribute can hold single and multi value tokens.
		 *
		 * @todo	Change documentation so it is up to date.
		 */
		ValueType value;
};


#endif	//	COMPILATION_THEORY_AND_COMPILERS_TOKEN_H
