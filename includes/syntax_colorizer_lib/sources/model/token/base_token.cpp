//
// Created by Dominik on 11.04.2023.
//


#include "../../../headers/model/token/base_token.h"


//	Static values initialization
const std::vector<std::vector<char>> BaseToken::INPUT_ALPHABET = {
		//	INPUT_ALPHABET[BaseToken::Alphabet::LETTERS][n] 			- All the letters accepted
		{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'},
		//	INPUT_ALPHABET[BaseToken::Alphabet::NUMBERS][n] 			- All the numbers
		{'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
		//	INPUT_ALPHABET[BaseToken::Alphabet::WHITE_CHARACTERS][n] 	- All the white symbols
		{' ', '\n', '\t', '\v', '\f', '\r'},
		//	INPUT_ALPHABET[BaseToken::Alphabet::OPERATORS][n] 			- All the other symbols
		{'(', ')', '*', '+', '-', '/'}
};
const std::vector<std::string> BaseToken::POSSIBLE_COLOURS = {
		"Aqua",						//	Corresponds to ...
		"SkyBlue",					//	...
		"Wheat",					//	...
		"StaleGray",				//	...
		"RosyBrown",				//	...
		"Olive"						//	...
};
const std::vector<BaseToken::Codes> BaseToken::CODES_TYPES = BaseToken::generateIterator();

//	Constructors definitions
BaseToken::BaseToken(Codes type, std::size_t line, std::size_t col): code(type), line_coordinate(line), column_coordinate(col) {
	if(!BaseToken::isValidCode(type)) throw std::invalid_argument("Unable to create an object from BaseToken::Codes::START || BaseToken::Codes::UNKNOWN || BaseToken::Codes::END!\nUse BaseToken::isValidCode() method to check if the type argument is suitable for an argument!");
	
	this->code = type;
	this->colour = BaseToken::POSSIBLE_COLOURS[type - 1];
}

// Getters and setters method definitions.
BaseToken::Codes BaseToken::getCode() const {
	return this->code;
}
std::size_t BaseToken::getLine() const {
	return this->line_coordinate;
}
std::size_t BaseToken::getColumn() const {
	return this->column_coordinate;
}
std::string BaseToken::getColour() const {
	return this->colour;
}

//	Static methods definitions
bool BaseToken::isValidCode(Codes type) {
	return !(type == Codes::START || type == Codes::UNKNOWN || type == Codes::END);
}
std::size_t BaseToken::getNumberOfCodes() {
	return Codes::END - Codes::START + 1;	//	We add 1, because Codes values a labeled from 0 to n, so n + 1 values in total.
}
std::vector<BaseToken::Codes> BaseToken::generateIterator() {
	std::vector<Codes> result;
	result.reserve(BaseToken::getNumberOfCodes());
	for(size_t i = Codes::START; i < Codes::END + 1; ++i)
		result.push_back(Codes(i));
	
	return result;
}