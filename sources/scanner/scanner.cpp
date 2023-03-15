/**
 * @file 	Scanner.cpp
 * @version 0.027
 * @author 	Dominik Breksa
 * @date 	08.03.2023
 * @brief	Source file relating to Scanner class.
 * @see		Scanner.cpp
**/

#include "scanner.h"

Scanner::Scanner(): col_index(Scanner::RESET_INDEX), line_index(Scanner::RESET_INDEX),  A(Automata(Token::INPUT_ALPHABET)) {}
Scanner::Scanner(std::string in): input(std::move(in)), col_index(Scanner::RESET_INDEX), line_index(Scanner::RESET_INDEX + 1),  A(Automata(Token::INPUT_ALPHABET)) {}

void Scanner::addNextLine(const std::string& in) {
	this->input = in;
	this->col_index = Scanner::RESET_INDEX;
	this->line_index++;
}

Token Scanner::getToken() {
	//	Make sure we are at the accepting state
	for(; !A.isInAcceptingState(); col_index++)
		A.changeState(input[col_index]);

	//	See what state we are in add create token with states instructions.
	Token t = A.generateTokenOutOfCurrentState({line_index, col_index + 1});
	if(A.synchroniseIndex()) col_index--;
	//	Reset DFA current input, to be ready for next token.
	A.reset();
	return t;
}
bool Scanner::isEmpty() {
	return this->col_index >= this->input.size();
}