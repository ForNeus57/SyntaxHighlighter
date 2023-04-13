/**
 * @file 	token.h
 * @version 0.027
 * @author 	Dominik Breksa, dominikbreksa@gmail.com
 * @date 	08.03.2023
 * @brief	Header file relating to Token class.
 * @see		token.cpp file.
**/

#ifndef COMPILATION_THEORY_AND_COMPILERS_TOKEN_H
#define COMPILATION_THEORY_AND_COMPILERS_TOKEN_H

#include <iostream>
#include <variant>
#include <string>
#include <vector>

#include "../../exceptions/wrong_input_alphabet.h"
#include "base_token.h"

#define CODES_SIZE 9





/**
 * @brief	Enum, that helps organise access to 2D Token::INPUT_ALPHABET vector.
 * @note	It helps with time complexity, making it O(1) to access any character in Token::INPUT_ALPHABET, instead of O(log(n)) using std::map<std::string, vector<char>>.
 * 			And also providing the same information of what we try to access in alphabet.
 *
 * @param	LETTERS				- Referring to the index in Token::INPUT_ALPHABET containing all the letters.
 * @param	NUMBERS				- Referring to the index in Token::INPUT_ALPHABET containing all the number.
 * @param	WHITE_CHARACTERS	- Referring to the index in Token::INPUT_ALPHABET containing all the white symbols.
 * @param	SYMBOLS				- Referring to the index in Token::INPUT_ALPHABET containing all the symbols.
 *
 * @example	Token::INPUT_ALPHABET[Alphabet::LETTERS][i] will return i -th letter from this alphabet.
 *
 * @see		token.cpp file to better understand how this data is organised.
 * @see		Token class.
 * @see		Token::INPUT_ALPHABET static attribute.
 */
enum Alphabet {
	LETTERS				= 0,
	NUMBERS				= 1,
	WHITE_CHARACTERS	= 2,
	SYMBOLS				= 3
};


/**
 * @brief	Token class is meant to represent model token used for parsing code.
 * @note	It is an extension to a Codes enum, because their modularity is very limiting in C++, however it adds the ability to process token value and locate errors.
 *
 * @todo	Consider merging State class and Token class into one class.
 *
 * @see		Codes enum.
 * @see		Alphabet enum.
 * @see		Automata class.
 */
class Token {
	public:
		/**
		 * @brief	Constructor for this class. That assigns the value of the token based on the provided code.
		 *
		 * @throws	WrongInputAlphabet if this object is tried to be created with codes == Codes::UNKNOWN
		 *
		 * @param	c	- From this parameter the Token value is deducted.
		 * @param	s	- String that lead to creating a Token in Automata.
		 * @param	a	- All other necessary data i.e. location for error handling.
		 *
		 * @see		Automata class.
		 * @see		Codes enum.
		 */
		Token(Codes c,std::string s, std::size_t line, std::size_t column);
	public:
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
		 * @brief	Simple getter for code attribute.
		 * @return 	One of Codes enum elements.
		 */
		Codes getCode() const;
		/**
		 * @brief	Simple getter for value of the Token.
		 * @return 	One of the following: uint, char or std::string elements.
		 */
		std::variant<unsigned int, char, std::string> getValue() const;
		/**
		 * @brief	Simple getter for the line in a file where a token have been constructed.
		 * @return 	y coordinate of a Token.
		 */
		std::size_t getLine() const;
		/**
		 * @brief	Simple getter for the column in a line where a token have been constructed.
		 * @return x coordinate of a Token.
		 */
		std::size_t getColumn() const;
		/**
		 * @brief
		 * @return
		 */
		std::string getColour() const;
		/**
		 * @brief
		 * @return
		 */
		std::string convertToHTML() const;
		/**
		 * @brief
		 * @return
		 */
		std::string print() const;
	public:
		const static std::vector<std::string> POSSIBLE_COLOURS;
	private:
		/**
		 * @brief	Code attribute of token, basically informs us of the created token type. Is it a Plus symbol, minus...
		 * @note	It also contains the information about how to understand coming in constructor string and making it proper value.
		 * @see		Codes enum.
		 */
		Codes code;
		/**
		 * @brief	Value stored of a token.
		 * @note	It is 100% dependent on the previous attribute: Token::code. For example single value tokens are guaranteed to ba a char, UNSIGNED_INTEGER, unsigned integer and so on.
		 * @note	Why use std::variant<...>? Because this attribute can hold single and multi value tokens.
		 *
		 * @todo	Change this to std::any()....
		 */
		std::variant<unsigned int, char, std::string> value;
		/**
		 * @brief	Simple tuple, that contains all the attributes that we want to assign to Token.
		 * @note	The values are from 1 to n.
		 */
		std::size_t line_number;
		/**
		 * @brief	Column where the generated token has been found.
		 * @note	The values are from 1 to n.
		 */
		std::size_t column_number;
		std::string colour;
};


#endif	//	COMPILATION_THEORY_AND_COMPILERS_TOKEN_H
