//
// Created by Dominik on 08.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_AUTOMATA_H
#define COMPILATION_THEORY_AND_COMPILERS_AUTOMATA_H

#include <array>		//	std::array<...>
#include <cstddef>		// 	std::size_t

#include "Token.h"
#include "State.h"

/**
 * @brief
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
	State getCurrentState();
	bool isInAcceptingState();
	Token generateTokenOutOfCurrentState();
private:
	void initializeSetOfStates();
	void initializeSetOfTokens();
public:
	const static std::size_t STARTING_STATE_NUMBER = 0;
private:
	std::size_t current_state_number;
	std::array<State, State::TOTAL_NUMBER_OF_STATES> table_of_all_states;
	std::array<char, CodeType::INPUT_ALPHABET_LENGTH> input_to_state_number_converter;
	/**
	 *	The schema for this automata table:
	 *	State_number	|	Input '+'	|	Input '-'	|	Input '*'	|	Input '/'	|	Input '('	|	Input '('	|	Input 'Number'	|	Input 'character'
	 *	----------------|---------------|---------------|---------------|---------------|---------------|---------------|-------------------|--------------------
	 *	0 - Start		|	2		 	|				|				|				|				|				|					|
	 *	1 - Error		|	1			|	1			|	1			|	1			|	1			|	1			|	1				|	1
	 *	2 - Success '+'	|				|				|				|				|				|				|					|
	 *	3 - Success '-' |				|				|				|				|				|				|					|
	 */
	//std::array<std::array<std::size_t, STATE_NUMBER>, CODE_TYPE_SIZE> transition_table = {
	//	{
	//		{0,	0,	0,	0,	0,	0,	0,	0},
	//		{},
	//	}
	//};
};


#endif //COMPILATION_THEORY_AND_COMPILERS_AUTOMATA_H
