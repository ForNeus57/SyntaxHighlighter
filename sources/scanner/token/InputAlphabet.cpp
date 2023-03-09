//
// Created by Dominik on 09.03.2023.
//

#include "InputAlphabet.h"

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