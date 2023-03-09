//
// Created by Dominik on 08.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_SCANNER_H
#define COMPILATION_THEORY_AND_COMPILERS_SCANNER_H

#include "Token.h"
#include "Automata.h"

class Scanner {
public:
	Scanner(std::string in);
	Token getToken();
	bool isEmpty();
public:

private:
	std::size_t index;
	std::string input;
	Automata A;
};


#endif //COMPILATION_THEORY_AND_COMPILERS_SCANNER_H
