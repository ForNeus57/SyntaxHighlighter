//
// Created by Dominik on 11.04.2023.
//

#ifndef BASIC_COMPILER_BASE_TOKEN_H
#define BASIC_COMPILER_BASE_TOKEN_H

#include <utility>
#include <stdexcept>
#include <vector>

#include "primitive_token.h"


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
enum Codes {
	//	Single value tokens
	START					= 0,		//	Not a real code of a Token, simple helper to iterate over the codes
	KEYWORD					= 1,		//
	IDENTIFIER				= 2,
	CONSTANTS				= 3,
	SPECIAL_CHARACTERS		= 4,
	STRINGS					= 5,
	OPERATOR				= 6,
	UNKNOWN					= 7,		//	Error value
	END						= 8			//	Not a real code of a Token, simple helper to iterate over the codes
};

template<typename T>
class BaseToken: PrimitiveToken {
	public:
		BaseToken(Codes, T, std::size_t, std::size_t, std::string);
		~BaseToken() = default;
	public:
		Codes getCode() const;
		T getValue() const;
		size_t getLine() const;
		size_t getColumn() const;
		std::string getColour() const;
	public:
		/**
		 * @brief	Static variable containing all the symbols in ascii table, that we consider in input alphabet of this model.
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
		Codes code;
		T value;
		std::size_t line_coordinate;
		std::size_t column_coordinate;
		std::string colour;
};


#endif	//	BASIC_COMPILER_BASE_TOKEN_H
