//
// Created by Dominik on 14.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_CANNOT_CREATE_TOKEN_NOT_FROM_FINISHING_STATE_H
#define COMPILATION_THEORY_AND_COMPILERS_CANNOT_CREATE_TOKEN_NOT_FROM_FINISHING_STATE_H

#include <exception>
#include <string>

class CannotCreateTokenNotFromFinishingState: public std::exception {
	public:
		explicit CannotCreateTokenNotFromFinishingState(const std::string & msg = "Not given.") {
			this->message += msg + '\n';
		}
	public:
		const char* what () const noexcept override {
			return message.c_str();
		}
	private:
		std::string message = "Provided character is not supported by this model!\n"
							  "Additional info: ";
};

#endif	//	COMPILATION_THEORY_AND_COMPILERS_CANNOT_CREATE_TOKEN_NOT_FROM_FINISHING_STATE_H
