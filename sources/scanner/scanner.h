//
// Created by Dominik on 08.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_SCANNER_H
#define COMPILATION_THEORY_AND_COMPILERS_SCANNER_H

#include "token.h"
#include "automata.h"

/**
 * @brief
 *
 * @param	index
 * @param	input
 * @param	A
 */
class Scanner {
public:
	Scanner();
	explicit Scanner(std::string);
public:
	void addNextLine(const std::string&);
	Token getToken();
public:
	bool isEmpty();
private:

public:
	const static std::size_t RESET_INDEX = 0;
private:
	std::string input;
	std::size_t col_index;
	std::size_t line_index;
	Automata A;
};


#endif //COMPILATION_THEORY_AND_COMPILERS_SCANNER_H
