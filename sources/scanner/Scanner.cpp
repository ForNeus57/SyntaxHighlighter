//
// Created by Dominik on 08.03.2023.
//

#include "Scanner.h"

Scanner::Scanner(std::size_t l, std::string in): input(std::move(in)), index(0), line(l),  A(Automata()) {}

Token Scanner::getToken() {
	for(; !A.isInAcceptingState(); index++)
		A.changeState(input[index]);

	//	index + 1, because it is counted from 0, but line is initialized with 1, so we don't have too.
	Token t = A.generateTokenOutOfCurrentState({line, index + 1});
	if(A.synchroniseIndex()) index--;
	A.reset();
	return t;
}
bool Scanner::isEmpty() {
	return this->index >= this->input.size();
}
