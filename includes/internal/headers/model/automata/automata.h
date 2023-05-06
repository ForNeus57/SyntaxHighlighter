/**
 * @file 	automata.h
 * @version 0.027
 * @author 	Dominik Breksa
 * @date 	08.03.2023
 * @brief	Header file relating to Automata class.
 * @see		automata.cpp file.
**/

#ifndef SYNTAX_HIGHLIGHTER_AUTOMATA_H
#define SYNTAX_HIGHLIGHTER_AUTOMATA_H


#include <cstddef>			// 	std::size_t
#include <vector>
#include <map>
#include <algorithm>

#include "../token/base_token.h"
#include "state.h"
#include "../../exceptions/unknown_symbol.h"

/**
 * @brief	Implementation of DFA (Deterministic Finite Automata), that is used by the model to construct next Tokens.
 *
 * @note	Skips all BaseToken::INPUT_ALPHABET[BaseToken::Alphabet::WHITE_SPACE] symbols when creating token values.
 */
class Automata {
	public:
		/**
		 * @brief	Constructor for Automata class.
		 *
		 * @param	input_alphabet	- Group of characters that are considered valid inputs to the transition function ot the DFA.
		 *
		 * @see		Token class.
		 * @see		Token::INPUT_ALPHABET.
		 */
		explicit Automata(const std::vector<std::vector<char>>& alphabet);
	public:
		/**
		 * @brief	Moves the cursor (index in the State table) to the next state.
		 * @param	in	- One of input parameters of transition_function.
		 */
		void changeState(char in);
		/**
		 * @brief	If current state is accepting it will return token created using instructions provided in a State.return_code.
		 *
		 * @return	Created token.
		 */
		std::unique_ptr<BaseToken> generateTokenOutOfCurrentState(std::size_t, std::size_t);
		/**
		 * @brief	Extra information that
		 * @return	True / false it there occurs a need to subtract 1 from index, to process specific letter once more.
		 */
		bool synchroniseIndex();
		/*
		 * @brief	Resets the current state number and clears the input_since_last_reset string.
		 * @note	It prepares these automata to generate new token.
		 */
		void reset();
	public:
		/**
		 * @brief	Simple method tha informs outside environment if we have reached through input an accepting state.
		 * @return 	True/False if current state have true/false of is_finishing attribute.
		 *
		 * @see	State class.
		 */
		bool isInAcceptingState() const;
	private:
		void initializeStateTable();
		void initializeInputAlphabetMap(const std::vector<std::vector<char>>& alphabet);
		void initializeTransitionFunction(const std::vector<std::vector<char>>& alphabet);
	public:
		/**
		 * @brief	The state index, that will be assigned as a starting one.
		 */
		const static std::size_t STARTING_STATE_NUMBER = 0;
		const static std::size_t ERROR_STATE_NUMBER = 21;
	private:
		/**
		 * @brief	The cursor, that points to the index in state_table which corresponds to a specific state.
		 *
		 * @see		State class.
		 * @see		state_table attribute in this class.
		 */
		std::size_t current_state_number;
		/**
		 * @brief	The table of all the states that are in a Automata.
		 * @note	Serves the same function, as a table of Tokens,
		 * @note	In this Automata we are not moving through individual states, but rather to save time and memory through state indexes in this table.
		 *
		 * @see		State class.
		 */
		std::vector<State> state_table;
		/**
		 * @brief	Variable that maps any character in a input alphabet to a specific index in transition table.
		 * @note	It is a function: char -> column index in transition function.
		 */
		std::map<char, std::size_t> input_map;
		/**
		 * @brief	2D vector that contains the how to behave if we are in current state and have specific input character.
		 * @note	It is a function: (char, curr_state_index) -> next_state_index in state table.
		 * @note	This table is nothing more fancy then a table style provided to us on Formal linguistics and automata course last semester.
		 */
		std::vector<std::vector<std::size_t>> transition_function;
		/**
		 * @brief	The input that have lead this automata to accepting state.
		 */
		std::string input_since_last_reset;
};


#endif	//	SYNTAX_HIGHLIGHTER_AUTOMATA_H
