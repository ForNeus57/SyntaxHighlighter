//
// Created by Dominik on 08.03.2023.
//

#include "Token.h"

Token::Token(std::variant<int, char, std::string> v, Attributes a): code(
		std::holds_alternative<int>(v) ? Codes::INTEGER_NUMBER : (
			std::holds_alternative<char>(v) ? CodeType::translateInput(get<char>(v)) : Codes::IDENTIFIER
		)
), value(std::move(v)), attribute(a) {}

Token::operator std::string() const {
	std::string str;
	if(std::holds_alternative<int>(this->value))
		str = std::to_string(get<int>(this->value));
	else if(std::holds_alternative<char>(this->value))
		str = std::to_string(get<char>(this->value));
	else
		str = get<std::string>(this->value);

	return "(" + std::string(this->code) + ", " + str
			+ ", col:" + std::to_string(this->attribute.cols) + ", row:" + std::to_string(this->attribute.rows) + ")";
}

CodeType Token::getCode() const {
	return this->code;
}

std::variant<int, char, std::string> Token::getValue() const {
	return this->value;
}

Attributes Token::getAttribute() const {
	return this->attribute;
}
