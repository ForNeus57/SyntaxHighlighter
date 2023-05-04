//
// Created by Dominik on 09.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_NOT_SUPPORTED_TOKEN_VALUE_FOR_TOKEN_CONSTRUCTOR_H
#define COMPILATION_THEORY_AND_COMPILERS_NOT_SUPPORTED_TOKEN_VALUE_FOR_TOKEN_CONSTRUCTOR_H

#include <exception>
#include <string>

class UnknownSymbol: public std::exception {
	public:
		explicit UnknownSymbol(const std::string& input_that_lead_to_error): message(
			"Provided character is not supported by this model! Unknown symbol (symbol not from accepted alphabet) occurred while trying to scan token: " + input_that_lead_to_error + '\n'
		) {}
	public:
		const char* what () const noexcept override {
			return message.c_str();
		}
		std::string getErrorInput() const {
			return this->error_input;
		}
	private:
		std::string message;
		std::string error_input;
};


#endif	//	COMPILATION_THEORY_AND_COMPILERS_NOT_SUPPORTED_TOKEN_VALUE_FOR_TOKEN_CONSTRUCTOR_H
