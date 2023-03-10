//
// Created by Dominik on 09.03.2023.
//

#include "CodeType.h"

CodeType::CodeType(Codes c): code(c) {}

CodeType::CodeType(char c) {
	this->code = CodeType::translateInput(c);
}

CodeType::operator std::string() const {
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
		case Codes::INTEGER_NUMBER: {
			s = "INTEGER_NUMBER";
			break;
		}
		case Codes::IDENTIFIER: {
			s = "IDENTIFIER";
			break;
		}
	}
	return s;
}

Codes CodeType::translateInput(char in) {
	Codes c;
	switch(in) {
		case '(': {
			c = Codes::LEFT_BRACKET;
			break;
		}
		case ')': {
			c = Codes::RIGHT_BRACKET;
			break;
		}
		case '*': {
			c = Codes::TIMES;
			break;
		}
		case '+': {
			c = Codes::PLUS;
			break;
		}
		case '-': {
			c = Codes::MINUS;
			break;
		}
		case '/': {
			c = Codes::DIVIDED;
			break;
		}
		case '0': {
			c = Codes::INTEGER_NUMBER;
			break;
		}
		case 'i': {
			c = Codes::IDENTIFIER;
			break;
		}
		default: {
			throw WrongInputAlphabet();
		}
	}
	return c;
}

Codes CodeType::getCode() {
	return this->code;
}
