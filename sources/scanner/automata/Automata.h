//
// Created by Dominik on 08.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_AUTOMATA_H
#define COMPILATION_THEORY_AND_COMPILERS_AUTOMATA_H

#include <array>			//	std::array<...>
#include <cstddef>			// 	std::size_t
#include <vector>
#include <map>

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
	/**
	 * @brief
	 *
	 * @todo	Make this method safe from generating token out of nothing...
	 * @return
	 */
	Token generateTokenOutOfCurrentState(Attributes);
	bool synchroniseIndex();
	void reset();
public:

public:
	bool isInAcceptingState() const;
private:
	void initializeStateTable();
	void initializeInputAlphabetMap(std::string);
	void initializeTransitionFunction();
public:
	const static std::size_t STARTING_STATE_NUMBER = 0;
private:
	std::size_t current_state_number;
	std::vector<State> state_table;
	std::map<char, std::size_t> input_map;
	std::vector<std::vector<std::size_t>> transition_function;
	std::string input_since_last_reset;
};


#endif //COMPILATION_THEORY_AND_COMPILERS_AUTOMATA_H
