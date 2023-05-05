/**
 * @file 	Scanner.cpp
 * @version 0.027
 * @author 	Dominik Breksa
 * @date 	08.03.2023
 * @brief	Source file relating to Scanner class.
 * @see		Scanner.h
**/

#include "../../headers/model/scanner.h"

Scanner::Scanner(): col_index(Scanner::RESET_INDEX), line_index(Scanner::RESET_INDEX),  A(BaseToken::INPUT_ALPHABET) {}

std::stringstream Scanner::operator()(std::istream* in, std::ostream* out, std::string (BaseToken::*format)() const) {
	std::stringstream s;
	std::string line;
	
	while(std::getline(*in, line)) {
		if (in->fail() || in->eof()) {
			*out << "Exiting...\n";
			break;
		}
		this->addNextLine(line);
		s << this->processLine(format);
	}
	
	return s;
}
std::stringstream Scanner::operator()(std::ifstream& in_file, std::string (BaseToken::*format)() const) {
	std::stringstream s;
	std::string line;
	
	while(std::getline(in_file, line)) {
		this->addNextLine(line);
		s << this->processLine(format);
	}
	
	return s;
}
void Scanner::operator()(std::ifstream& in_file, std::ofstream& out_file, std::string (BaseToken::*format)() const) {
	std::string line;
	
	while(std::getline(in_file, line)) {
		this->addNextLine(line);
		out_file << this->processLine(format);
	}
}
void Scanner::addNextLine(const std::string& in) {
	this->input = in;
	this->col_index = Scanner::RESET_INDEX;
	this->line_index++;
}
std::string Scanner::processLine(std::string (BaseToken::* format)() const) {
	std::string output(this->input);
	while(!this->isEmpty()) {							//	Generate all the tokens in this line.
		std::optional<Token> generated_token;
		try {
			generated_token = this->getToken();			//	I use a method call instead of a function, but I think, that it isn't much of a problem.
		} catch(const WrongInputAlphabet& err){
			std::cout << err.what();
			break;
		}
		if(generated_token) {
			std::size_t column = generated_token->getColumn();
			std::size_t size;
			
			if(std::holds_alternative<unsigned int>(generated_token.value().getValue()))
				size = std::to_string(std::get<unsigned int>(generated_token.value().getValue())).size();
			else if(std::holds_alternative<char>(generated_token.value().getValue()))
				size = 1;
			else
				size = std::get<std::string>(generated_token.value().getValue()).size();
			output.replace(column - 1, size, (generated_token.value().*format)());
		} else {
			//	add '\n' because std::getline(...) doesn't put it when reading a line.
			output.push_back('\n');
			break;
		}
	}
	return output;
}
std::optional<std::unique_ptr<BaseToken>> Scanner::getToken() {
	//	Make sure we are at the accepting state
	for(; !A.isInAcceptingState() and col_index < input.size(); col_index++)
		A.changeState(input[col_index]);
	if(A.isInAcceptingState()) {
		//	See what state we are in add create token with states instructions.
		Token t = A.generateTokenOutOfCurrentState(line_index, col_index + 1);
		if(A.synchroniseIndex()) col_index--;
		//	Reset DFA current input, to be ready for next token.
		A.reset();
		return t;
	}
	A.reset();
	return {};
}
bool Scanner::isEmpty() {
	return this->col_index >= this->input.size();
}