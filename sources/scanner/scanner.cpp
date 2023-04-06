/**
 * @file 	Scanner.cpp
 * @version 0.027
 * @author 	Dominik Breksa
 * @date 	08.03.2023
 * @brief	Source file relating to Scanner class.
 * @see		Scanner.cpp
**/

#include "scanner.h"

Scanner::Scanner(): col_index(Scanner::RESET_INDEX), line_index(Scanner::RESET_INDEX),  A(Token::INPUT_ALPHABET) {}

std::pair<std::stringstream, Statistics> Scanner::operator()(std::istream* in, std::ostream* out, bool requires_statistics, std::string (Token::*format)() const) {
	std::stringstream s;
	std::string line;
	Statistics statistics;
	
	//	Useless check, because statistics are not implemented as yet.
	if(requires_statistics)	statistics = Statistics();
	else statistics = Statistics();
	
	while(std::getline(*in, line)) {
		if (in->fail() || in->eof()) {
			*out << "Exiting...\n";
			break;
		}
		this->addNextLine(line);
		s << this->processLine(format);
	}
	
	return std::make_pair(std::stringstream(s.str()), statistics);
}
std::pair<std::stringstream, Statistics> Scanner::operator()(std::ifstream& in_file, bool requires_statistics, std::string (Token::*format)() const) {
	std::stringstream s;
	std::string line;
	Statistics statistics;
	
	//	Useless check, because statistics are not implemented as yet.
	if(requires_statistics)	statistics = Statistics();
	else statistics = Statistics();
	
	while(std::getline(in_file, line)) {
		this->addNextLine(line);
		s << this->processLine(format);
	}
	
	return std::make_pair(std::stringstream(s.str()), statistics);
}
Statistics Scanner::operator()(std::ifstream& in_file, std::ofstream& out_file, bool requires_statistics, std::string (Token::*format)() const) {
	std::string line;
	Statistics statistics;
	
	//	Useless check, because statistics are not implemented as yet.
	if(requires_statistics)	statistics = Statistics();
	else statistics = Statistics();
	
	while(std::getline(in_file, line)) {
		this->addNextLine(line);
		out_file << this->processLine(format);
	}
	
	return statistics;
}
void Scanner::addNextLine(const std::string& in) {
	this->input = in;
	this->col_index = Scanner::RESET_INDEX;
	this->line_index++;
}
std::string Scanner::processLine(std::string (Token::* format)() const) {
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
			const auto [line, column] = generated_token->getAttribute();
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
std::optional<Token> Scanner::getToken() {
	//	Make sure we are at the accepting state
	for(; !A.isInAcceptingState() and col_index < input.size(); col_index++)
		A.changeState(input[col_index]);
	if(A.isInAcceptingState()) {
		//	See what state we are in add create token with states instructions.
		Token t = A.generateTokenOutOfCurrentState({line_index, col_index + 1});
		if(A.synchroniseIndex()) col_index--;
		//	Reset DFA current input, to be ready for next token.
		A.reset();
		return t;
	}
	return {};
}
bool Scanner::isEmpty() {
	return this->col_index >= this->input.size();
}