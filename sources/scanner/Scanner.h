//
// Created by Dominik on 08.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_SCANNER_H
#define COMPILATION_THEORY_AND_COMPILERS_SCANNER_H

#include "Token.h"
#include "Automata.h"

class Scanner {
public:
	Scanner() = default;
	explicit Scanner(std::string i): input(std::move(i)) {}
	Token getToken();
	bool isEmpty();
private:
	std::string input;
	Automata A = Automata();
};


#endif //COMPILATION_THEORY_AND_COMPILERS_SCANNER_H
