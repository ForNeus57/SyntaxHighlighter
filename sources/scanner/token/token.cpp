/**
 * @file 	token.cpp
 * @version 0.027
 * @author 	Dominik Breksa, dominikbreksa@gmail.com
 * @date 	08.03.2023
 * @brief	Source file relating to Token class.
 * @see		token.h
**/

#include <valarray>

#include "token.h"

//	Static values initialization
const std::vector<std::vector<char>> Token::INPUT_ALPHABET = {
		//	INPUT_ALPHABET[Alphabet::LETTERS][n] - All the letters accepted
		{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'},
		//	INPUT_ALPHABET[Alphabet::NUMBERS][n] - All the numbers
		{'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
		//	INPUT_ALPHABET[Alphabet::WHITE_CHARACTERS][n] - All the white symbols
		{' ', '\n', '\0', '\t'},
		//	INPUT_ALPHABET[Alphabet::SYMBOLS][n] - All the other symbols
		{'(', ')', '*', '+', '-', '/'}
};
const std::vector<Codes> Token::CODES_TYPES = {Codes::LEFT_BRACKET,Codes::RIGHT_BRACKET,Codes::TIMES,Codes::PLUS,Codes::MINUS,Codes::DIVIDED,Codes::UNSIGNED_INTEGER_NUMBER,Codes::IDENTIFIER,Codes::UNKNOWN};

Token::Token(Codes c, std::string in, Attributes a): code(c), value(), attribute(std::move(a)) {
	//	This is where the code deducts how to interpret a coming string.
	switch (this->code) {
		case Codes::LEFT_BRACKET: case Codes::RIGHT_BRACKET: case Codes::TIMES: case Codes::PLUS: case Codes::MINUS: case Codes::DIVIDED: {
			//	Go through all the white space symbols and delete them;
			for(char i : INPUT_ALPHABET[Alphabet::WHITE_CHARACTERS]) {
				std::string::iterator end_pos = std::remove(in.begin(), in.end(), i);
				in.erase(end_pos, in.end());
			}
			this->value = in[0];
			break;
		}
		case Codes::UNSIGNED_INTEGER_NUMBER: {
			this->value = std::stoul(in);
			break;
		}
		case Codes::IDENTIFIER: {
			//	Go through all the white space symbols and delete them;
			for(char i : INPUT_ALPHABET[Alphabet::WHITE_CHARACTERS]) {
				std::string::iterator end_pos = std::remove(in.begin(), in.end(), i);
				in.erase(end_pos, in.end());
			}
			//	Go through all the symbols and delete them;
			for(char i : INPUT_ALPHABET[Alphabet::SYMBOLS]) {
				std::string::iterator end_pos = std::remove(in.begin(), in.end(), i);
				in.erase(end_pos, in.end());
			}
			this->value = in;
			break;
		}
		case Codes::UNKNOWN: {
			throw WrongInputAlphabet("");
		}
	}
}

Token::operator std::string() const {
	std::string val;
	std::string cod;
	const auto [line, col] = this->attribute;
	switch (this->code) {
		case Codes::LEFT_BRACKET:
			cod = "LEFT_BRACKET";
			val = "\'" + std::string(1, std::get<char>(this->value)) + "\'";
			break;
		case Codes::RIGHT_BRACKET:
			cod = "RIGHT_BRACKET";
			val = "\'" + std::string(1, std::get<char>(this->value)) + "\'";
			break;
		case Codes::TIMES:
			cod = "TIMES";
			val = "\'" + std::string(1, std::get<char>(this->value)) + "\'";
			break;
		case Codes::PLUS:
			cod = "PLUS";
			val = "\'" + std::string(1, std::get<char>(this->value)) + "\'";
			break;
		case Codes::MINUS:
			cod = "MINUS";
			val = "\'" + std::string(1, std::get<char>(this->value)) + "\'";
			break;
		case Codes::DIVIDED:
			cod = "DIVIDED";
			val = "\'" + std::string(1, std::get<char>(this->value)) + "\'";
			break;
		case Codes::UNSIGNED_INTEGER_NUMBER:
			cod = "UNSIGNED_INTEGER_NUMBER";
			val = std::to_string(std::get<unsigned int>(this->value));
			break;
		case Codes::IDENTIFIER:
			cod = "IDENTIFIER";
			val = "\"" + std::get<std::string>(this->value) + "\"";
			break;
		case Codes::UNKNOWN:
			throw WrongInputAlphabet("");
	}
	return "(code:" + cod + ", value:" + val + ", line:" + std::to_string(line) + ", col:" + std::to_string(col) + ")";
}

Codes Token::getCode() const {
	return this->code;
}

std::variant<unsigned int, char, std::string> Token::getValue() const {
	return this->value;
}

Attributes Token::getAttribute() const {
	return this->attribute;
}