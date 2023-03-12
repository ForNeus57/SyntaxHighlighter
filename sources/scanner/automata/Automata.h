//
// Created by Dominik on 08.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_AUTOMATA_H
#define COMPILATION_THEORY_AND_COMPILERS_AUTOMATA_H

#include <array>			//	std::array<...>
#include <cstddef>			// 	std::size_t
#include <vector>
#include <list>

#include "Token.h"
#include "State.h"

/**
 * @brief
 *
 * @param	current_state_number	-
 * @param	token_table				-
 */
class Automata {
public:
	Automata();
public:
	void changeState(char in);
	void reset();
public:

public:
	Token getToken();
	bool isInAcceptingState();
private:
	void initializeStateTable();
public:
	const static std::size_t STARTING_STATE_NUMBER = 0;
private:
	std::size_t current_state_number;
	std::size_t previous_state_number;
	std::vector<State> state_table;
	std::list<char> input_since_last_reset;
};


#endif //COMPILATION_THEORY_AND_COMPILERS_AUTOMATA_H
