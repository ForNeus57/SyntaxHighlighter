//
// Created by Dominik on 08.03.2023.
//

#include <valarray>

#include "Token.h"

const std::string Token::INPUT_ALPHABET = {
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
		' ', '\n',
		'(', ')', '*', '+', '-', '/'
};

const std::vector<Codes> Token::CODES_TYPES = {Codes::LEFT_BRACKET,Codes::RIGHT_BRACKET,Codes::TIMES,Codes::PLUS,Codes::MINUS,Codes::DIVIDED,Codes::UNSIGNED_INTEGER_NUMBER,Codes::IDENTIFIER,Codes::UNKNOWN};

Token::Token(Codes c, std::variant<unsigned int, char, std::string> v, Attributes a): code(c), value(std::move(v)), attribute(std::move(a)) {}

Token::operator std::string() const {
	std::string str;
	switch (this->code) {
		case Codes::LEFT_BRACKET: case Codes::RIGHT_BRACKET: case Codes::TIMES: case Codes::PLUS: case Codes::MINUS: case Codes::DIVIDED:
			str = "\'" + std::string(1, std::get<char>(this->value)) + "\'";
			break;
		case Codes::UNSIGNED_INTEGER_NUMBER:
			str = std::to_string(std::get<unsigned int>(this->value));
			break;
		case Codes::IDENTIFIER:
			str = "\"" + std::get<std::string>(this->value) + "\"";
			break;
		case Codes::UNKNOWN:
			throw WrongInputAlphabet();
	}
	const auto [line, col] = this->attribute;
	return "(code:" + this->printCodes() + ", value:" + str + ", line:" + std::to_string(line) + ", col:" + std::to_string(col) + ")";
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

std::string Token::printCodes() const {
	std::string s;
	switch (this->code) {
		case Codes::LEFT_BRACKET: {
			s = "LEFT_BRACKET";
			break;
		}
		case Codes::RIGHT_BRACKET: {
			s = "RIGHT_BRACKET";
			break;
		}
		case Codes::TIMES: {
			s = "TIMES";
			break;
		}
		case Codes::PLUS: {
			s = "PLUS";
			break;
		}
		case Codes::MINUS: {
			s = "MINUS";
			break;
		}
		case Codes::DIVIDED: {
			s = "DIVIDED";
			break;
		}
		case Codes::UNSIGNED_INTEGER_NUMBER: {
			s = "UNSIGNED_INTEGER_NUMBER";
			break;
		}
		case Codes::IDENTIFIER: {
			s = "IDENTIFIER";
			break;
		}
		case Codes::UNKNOWN: {
			throw WrongInputAlphabet();
		}
	}
	return s;
}

std::variant<unsigned int, char, std::string> pars_unsigned_integer(std::string in) {
	return std::stoul(in);
}
std::variant<unsigned int, char, std::string> pars_identifier(std::string in) {
	in.pop_back();
	return in;
}
std::variant<unsigned int, char, std::string> pars_single_value_tokens(std::string in) {
	return in[0];
}
