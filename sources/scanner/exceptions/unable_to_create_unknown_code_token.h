//
// Created by Dominik on 12.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_UNABLE_TO_CREATE_UNKNOWN_CODE_TOKEN_H
#define COMPILATION_THEORY_AND_COMPILERS_UNABLE_TO_CREATE_UNKNOWN_CODE_TOKEN_H

#include <exception>
#include <string>

class UnableToCreateUnknownCodeToken: public std::exception {
public:
	explicit UnableToCreateUnknownCodeToken(std::size_t line, std::size_t col) {
		message += " Exception location - line:" + std::to_string(line) + ", column:" + std::to_string(col) + '\n';
	}
public:
	const char* what () const noexcept override {
		return message.c_str();
	}
private:
	std::string message = "An attempt was made to create Token, with UNKNOWN Code!";
};

#endif //COMPILATION_THEORY_AND_COMPILERS_UNABLE_TO_CREATE_UNKNOWN_CODE_TOKEN_H
