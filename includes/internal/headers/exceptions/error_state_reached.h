//
// Created by Dominik on 14.03.2023.
//

#ifndef SYNTAX_HIGHLIGHTER_ERROR_STATE_REACHED_H
#define SYNTAX_HIGHLIGHTER_ERROR_STATE_REACHED_H

#include <exception>
#include <string>
#include <utility>

class ErrorStateReached: public std::exception {
	public:
		explicit ErrorStateReached(const std::string& input_that_lead_to_error, std::size_t line_number, std::size_t column_number): message(
			"Error state has been reached! Input that caused such turn of event:" + input_that_lead_to_error + ", at line:" + std::to_string(line_number) + ", at column:" + std::to_string(column_number)
		), error_input(input_that_lead_to_error), line(line_number), column(column_number) {}
	public:
		const char* what() const noexcept override {
			return message.c_str();
		}
		std::string getErrorInput() const {
			return this->error_input;
		}
		std::size_t getLineNumber() const {
			return this->line;
		}
		std::size_t getColumnNumber() const {
			return this->column;
		}
	private:
		std::string message;
		std::string error_input;
		std::size_t line;
		std::size_t column;
};

#endif	//	SYNTAX_HIGHLIGHTER_ERROR_STATE_REACHED_H
