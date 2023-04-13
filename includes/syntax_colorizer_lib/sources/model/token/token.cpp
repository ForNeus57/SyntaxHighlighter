/**
 * @file 	token.cpp
 * @version 0.027
 * @author 	Dominik Breksa, dominikbreksa@gmail.com
 * @date 	08.03.2023
 * @brief	Source file relating to Token class.
 * @see		token.h
**/


#include "../../../headers/model/token/token.h"

const std::vector<std::string> Token::POSSIBLE_COLOURS = {
	"Aqua",
	"SkyBlue",
	"Wheat",
	"StaleGray",
	"RosyBrown",
	"Olive",
	"Teal",
	"Khaki",
	"OrangeRed"
};
const std::vector<Codes> Token::CODES_TYPES = {Codes::LEFT_BRACKET,Codes::RIGHT_BRACKET,Codes::TIMES,Codes::PLUS,Codes::MINUS,Codes::DIVIDED,Codes::UNSIGNED_INTEGER_NUMBER,Codes::IDENTIFIER,Codes::UNKNOWN};

Token::Token(Codes c, std::string in, std::size_t line, std::size_t column): code(c), value(), line_number(), column_number() {
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
	this->colour = Token::POSSIBLE_COLOURS[this->code];
	this->line_number = line;
	this->column_number = column;
}
Token::operator std::string() const {
	std::string val;
	std::string cod;
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
	return "(code:" + cod + ", value:" + val + ", line:" + std::to_string(this->line_number) + ", col:" + std::to_string(this->column_number) + ")";
}
Codes Token::getCode() const {
	return this->code;
}
std::variant<unsigned int, char, std::string> Token::getValue() const {
	return this->value;
}
std::size_t Token::getLine() const {
	return this->line_number;
}
std::size_t Token::getColumn() const {
	return this->column_number;
}
std::string Token::getColour() const {
	return this->colour;
}
std::string Token::print() const {
	return std::string(*this);
}
std::string Token::convertToHTML() const {
	if(std::holds_alternative<unsigned int>(this->value))
		return "<pra style=\"color: " + this->colour +"\">" + std::to_string(std::get<unsigned int>(this->value)) + "</pra>";
	else if(std::holds_alternative<char>(this->value))
		return "<pra style=\"color: " + this->colour +"\">" + std::string(1, std::get<char>(this->value)) + "</pra>";
	return "<pra style=\"color: " + this->colour +"\">" + std::get<std::string>(this->value) + "</pra>";
}