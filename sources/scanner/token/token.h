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

#include "wrong_input_alphabet.h"

/**
 * @brief	Simple enum that is used to store code for the token.
 *
 * @note	Parameters are more or less organised in the increasing ascii code value.
 *
 * @todo	Remove Codes::UNKNOWN value...
 *
 * @param	LEFT_BRACKET			- Equivalent to '(' character, code: 0, REGEX: (
 * @param	RIGHT_BRACKET			- Equivalent to ')' character, code: 1, REGEX: )
 * @param	TIMES					- Equivalent to '*' character, code: 2, REGEX: *
 * @param	PLUS					- Equivalent to '+' character, code: 3, REGEX: +
 * @param	MINUS					- Equivalent to '-' character, code: 4, REGEX: -
 * @param	DIVIDED					- Equivalent to '/' character, code: 5, REGEX: /
 *
 * @param	UNSIGNED_INTEGER_NUMBER	- Equivalent to any unsigned integer number, code: 6, REGEX: [0-9]+
 * @param	IDENTIFIER				- Equivalent to any variable name you could create, code: 7, REGEX: [a-zA-Z][a-zA-Z0-9]*
 *
 * @param	UNKNOWN					- Error code, signaling the token was tried to be created not from finishing state in Automata, code: 8
 *
 * @see		Token class.
 * @see		automata.h file.
 */
enum class Codes {
	//	Single value tokens
		LEFT_BRACKET			= 0,
		RIGHT_BRACKET			= 1,
		TIMES					= 2,
		PLUS					= 3,
		MINUS					= 4,
		DIVIDED					= 5,
	//	Multi value tokens
		UNSIGNED_INTEGER_NUMBER	= 6,
		IDENTIFIER				= 7,
	//	Error value
		UNKNOWN					= 8
};

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
 * @brief	Simple 2 element tuple, that contains the location in scanned file of created token.
 *
 * @note	The first value is the line number, and the second is the column number in a file.
 * @see		Token.attribute class attribute.
 */
using Attributes = std::pair<std::size_t, std::size_t>;

/**
 * @brief	Token class is meant to represent scanner token used for parsing code.
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
	Token(Codes c, std::string s, Attributes a);
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
	 * @brief	Simple getter for value attribute.
	 * @return 	One of the following: uint, char or std::string elements.
	 */
	std::variant<unsigned int, char, std::string> getValue() const;
	/**
	 * @brief	Simple getter for attribute attribute.
	 * @note	Not the greatest naming of the variable :)
	 * @return 	One of the following: uint, char or std::string elements.
	 */
	Attributes getAttribute() const;
public:
	/**
	 * @brief	Static variable containing all the symbols in ascii table, that we consider in input alphabet of this scanner.
	 * @note	This variable makes it very easy to add new characters to alphabet. Simply extend the vector.
	 *
	 * @see		Alphabet enum.
	 */
	const static std::vector<std::vector<char>> INPUT_ALPHABET;
	/**
	 * @brief	Array that contains all the possible values of Codes enum. It has set like properties, but I will change it later.
	 * @note	It is an array, that makes it easier to iterate for all the tokens codes.
	 * @note	Makes it easy to see the codes length: Token::CODES_TYPES.size().
	 *
	 * @todo	Make this variable an ordered set, to iterate easier and make sure, that their values are unique.
	 * @todo	ADD ITERATOR TO THIS ENUM, SUCH THAT ++ returns next element. TEMPORARY FIX: vector<Codes> Token::CODES_TYPES not memory efficient
	 *
	 * @see		Codes enum.
	 */
	const static std::vector<Codes> CODES_TYPES;
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
	 */
	std::variant<unsigned int, char, std::string> value;
	/**
	 * @brief	Simple tuple, that contains all the attributes that we want to assign to Token.
	 *
	 * @todo	Change the name of this variable to something different i.e. position idk.
	 * @todo	Consider making it separate variables. Instead of packing them into a tuple. Save memory. :D
	 */
	Attributes attribute;
};


#endif	//	COMPILATION_THEORY_AND_COMPILERS_TOKEN_H
