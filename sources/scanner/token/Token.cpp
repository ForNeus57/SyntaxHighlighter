//
// Created by Dominik on 08.03.2023.
//

#include "Token.h"

#include <utility>

std::string printCodeType(CodeType type) {
	switch (type) {
		case LEFT_BRACKET:
			return "LEFT_BRACKET";
		case RIGHT_BRACKET:
			return "RIGHT_BRACKET";
		case TIMES:
			return "TIMES";
		case PLUS:
			return "PLUS";
		case MINUS:
			return "MINUS";
		case DIVIDED:
			return "DIVIDED";
		case INTEGER_NUMBER:
			return "INTEGER_NUMBER";
		case IDENTIFIER:
			return "IDENTIFIER";
	}
}

Token::Token(std::variant<int, char, std::string> v, Position coordinates): value(std::move(v)), attribute(coordinates) {
	if(std::holds_alternative<int>(this->value))
		this->code = CodeType::INTEGER_NUMBER;
	else if(std::holds_alternative<char>(this->value))
		this->code = static_cast<CodeType>(get<char>(this->value));
	else
		this->code = CodeType::IDENTIFIER;
}

Token::operator std::string() const {
	std::string str;
	if(std::holds_alternative<int>(this->value))
		str = std::to_string(get<int>(this->value));
	else if(std::holds_alternative<char>(this->value))
		str = std::to_string(get<char>(this->value));
	else
		str = get<std::string>(this->value);

	return "(" + printCodeType(this->code) + ", " + str + ")";
}

CodeType Token::getCode() const {
	return this->code;
}

std::variant<int, char, std::string> Token::getValue() const {
	return this->value;
}

Position Token::getAttribute() const {
	return this->attribute;
}
