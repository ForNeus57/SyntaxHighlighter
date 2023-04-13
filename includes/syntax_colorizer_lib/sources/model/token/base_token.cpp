//
// Created by Dominik on 11.04.2023.
//

#include "../../../headers/model/token/base_token.h"

#include <utility>

//	Static values initialization
template<typename T>
const std::vector<std::vector<char>> BaseToken<T>::INPUT_ALPHABET = {
		//	INPUT_ALPHABET[Alphabet::LETTERS][n] - All the letters accepted
		{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'},
		//	INPUT_ALPHABET[Alphabet::NUMBERS][n] - All the numbers
		{'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
		//	INPUT_ALPHABET[Alphabet::WHITE_CHARACTERS][n] - All the white symbols
		{' ', '\n', '\0', '\t'},
		//	INPUT_ALPHABET[Alphabet::SYMBOLS][n] - All the other symbols
		{'(', ')', '*', '+', '-', '/'}
};


template class BaseToken<std::string>;
template class BaseToken<char>;
template class BaseToken<int>;
template class BaseToken<double>;

template<typename T>
BaseToken<T>::BaseToken(Codes type, T val, std::size_t line, std::size_t col, std::string output_colour): code(type), value(std::move(val)), line_coordinate(line), column_coordinate(col), colour(std::move(output_colour)) {}

template<typename T>
Codes BaseToken<T>::getCode() const {
	return this->code;
}
template<typename T>
T BaseToken<T>::getValue() const {
	return this->value;
}
template<typename T>
std::size_t BaseToken<T>::getLine() const {
	return this->line_coordinate;
}
template<typename T>
std::size_t BaseToken<T>::getColumn() const {
	return this->column_coordinate;
}
template<typename T>
std::string BaseToken<T>::getColour() const {
	return this->colour;
}