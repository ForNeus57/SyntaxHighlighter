//
// Created by Dominik on 14.03.2023.
//

#ifndef BASIC_COMPILER_CANNOT_CREATE_TOKEN_NOT_FROM_FINISHING_STATE_H
#define BASIC_COMPILER_CANNOT_CREATE_TOKEN_NOT_FROM_FINISHING_STATE_H

#include <exception>
#include <string>


class UnknownReturnCode: public std::exception {
	public:
		explicit UnknownReturnCode(const std::string & msg = "Not given.") {
			this->message += msg + '\n';
		}
	public:
		const char* what () const noexcept override {
			return message.c_str();
		}
	private:
		std::string message = "Cannot receive return code from state. Additional information: ";
};

#endif	//	BASIC_COMPILER_CANNOT_CREATE_TOKEN_NOT_FROM_FINISHING_STATE_H
