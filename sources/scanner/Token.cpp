//
// Created by Dominik on 08.03.2023.
//

#include "Token.h"
#include <string>

Token::operator std::string() const {
	if(std::holds_alternative<int>(this->value)) {
		return "(" + std::string(reinterpret_cast<const char *>(this->code)) + ", " + std::to_string(get<int>(this->value)) + ")";
	}
	return "(" + std::string(reinterpret_cast<const char *>(this->code)) + ", " + get<std::string>(this->value) + ")";
}
