//
// Created by Dominik on 08.03.2023.
//

#include <utility>

#include "Token.h"

Token::Token(std::variant<int, char, std::string> v, Attributes attribute): value(std::move(v)), attribute(attribute) {
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

Attributes Token::getAttribute() const {
	return this->attribute;
}
