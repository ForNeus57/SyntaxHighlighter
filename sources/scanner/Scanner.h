//
// Created by Dominik on 08.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_SCANNER_H
#define COMPILATION_THEORY_AND_COMPILERS_SCANNER_H

#include "Token.h"
#include "Automata.h"

/**
 * @brief
 *
 * @param	index
 * @param	input
 * @param	A
 */
class Scanner {
public:
	explicit Scanner(size_t, std::string);
	Token getToken();
	bool isEmpty();
public:

private:
	std::string input;
	std::size_t index;
	std::size_t line;
	Automata A;
};


#endif //COMPILATION_THEORY_AND_COMPILERS_SCANNER_H
