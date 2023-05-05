//
// Created by Dominik on 11.04.2023.
//

#ifndef BASIC_COMPILER_BASE_TOKEN_H
#define BASIC_COMPILER_BASE_TOKEN_H


#include <utility>
#include <stdexcept>
#include <vector>


/**
 * @brief
 *
 * @todo	Complete documentation...
 * @todo	Consider making colour assigment more generic. So the Token<T> class takes full responsibility of creating Tokens.
 */
class BaseToken {
	public:
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
			OPERATORS			= 3
		};
		/**
		 * @brief	Simple enum that is used to store code for the token.
		 *
		 * @note	Parameters are more or less organised in the increasing ascii code value.
		 *
		 * @todo	Make this documentation complete and up to date
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
			LITERAL_INT				= 3,
			LITERAL_DOUBLE			= 4,
			SPECIAL_CHARACTERS		= 5,
			STRINGS					= 6,
			OPERATOR				= 7,
			WHITE_SYMBOL			= 8,
			UNKNOWN					= 9,		//	Error value
			END						= 10		//	Not a real code of a Token, simple helper to iterate over the codes
		};
	public:
		/**
		 * @brief
		 *
		 * @throws	std::invalid_argument	-	When ...
		 */
		explicit BaseToken(Codes, std::size_t, std::size_t);
		virtual ~BaseToken() = default;
		BaseToken(const BaseToken&) = default;
		BaseToken(BaseToken&&) = default;
	public:
		BaseToken& operator=(const BaseToken&) = default;
		BaseToken& operator=(BaseToken&&) = default;
	public:
		/**
		 * @brief	Simple getter for code attribute.
		 * @return 	One of Codes enum elements.
		 */
		Codes getCode() const;
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
	public:
		static std::string convertCodesToString(Codes);
		static bool isValidCode(Codes);
	public:
		virtual std::string print() const = 0;
		virtual std::string printHTML() const = 0;
	private:
		static std::vector<Codes> generateIterator();
		static std::size_t getNumberOfCodes();
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
		/**
		 * @brief	...
		 */
		const static std::vector<std::string> POSSIBLE_COLOURS;
	private:
		/**
		 * @brief	Code attribute of token, basically informs us of the created token type. Is it a Plus symbol, minus...
		 * @note	It also contains the information about how to understand coming in constructor string and making it proper value.
		 * @see		Codes enum.
		 */
		Codes code;
		/**
		 * @brief	Simple tuple, that contains all the attributes that we want to assign to Token.
		 * @note	The values are from 1 to n.
		 */
		std::size_t line_coordinate;
		/**
		 * @brief	Column where the generated token has been found.
		 * @note	The values are from 1 to n.
		 */
		std::size_t column_coordinate;
		/**
		 * @brief
		 * @return
		 */
		std::string colour;
};


#endif	//	BASIC_COMPILER_BASE_TOKEN_H
