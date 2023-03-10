//
// Created by Dominik on 08.03.2023.
//

#include "Scanner.h"

Scanner::Scanner(std::string in): index(0), input(std::move(in)), A(Automata()) {}

Token Scanner::getToken() {
	for(; !A.isInAcceptingState(); index++)
		A.changeState(input[index]);

	return A.generateTokenOutOfCurrentState();
}
bool Scanner::isEmpty() {
	return this->index == this->input.size() - 1;
}
