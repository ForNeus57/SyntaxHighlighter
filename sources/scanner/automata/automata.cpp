//
// Created by Dominik on 08.03.2023.
//

#include "automata.h"

Automata::Automata(): current_state_number(Automata::STARTING_STATE_NUMBER) {
	this->initializeStateTable();
	this->initializeInputAlphabetMap(Token::INPUT_ALPHABET);
	this->initializeTransitionFunction();
}

void Automata::changeState(char in) {
	this->current_state_number = this->transition_function[this->current_state_number][this->input_map[in]];
	this->input_since_last_reset.push_back(in);
}

Token Automata::generateTokenOutOfCurrentState(Attributes a) {
	return {this->state_table[this->current_state_number].getReturnCode(),
			this->input_since_last_reset,
			{a.first, a.second - this->input_since_last_reset.size()}
	};
}

bool Automata::synchroniseIndex() {
	if(!this->isInAcceptingState()) return false;

	switch (this->state_table[this->current_state_number].getReturnCode()) {
		case Codes::IDENTIFIER: case Codes::UNSIGNED_INTEGER_NUMBER:
			return true;
		case Codes::UNKNOWN: case Codes::LEFT_BRACKET: case Codes::RIGHT_BRACKET: case Codes::TIMES: case Codes::PLUS: case Codes::MINUS: case Codes::DIVIDED:
			return false;
	}
	return false;
}

void Automata::reset() {
	this->current_state_number = Automata::STARTING_STATE_NUMBER;
	this->input_since_last_reset.clear();
}

bool Automata::isInAcceptingState() const {
	return this->state_table[this->current_state_number].isAccepting();
}

void Automata::initializeStateTable() {
	this->state_table = std::vector<State>();
	//	Starting State
	this->state_table.emplace_back(true);
	//	Finishing state
	for(Codes x : Token::CODES_TYPES) {
		if(x == Codes::UNKNOWN) continue;
		else this->state_table.emplace_back(x);
	}
	for(size_t i = 0; i < 2; ++i)
		this->state_table.emplace_back(false);
	//	Error state id = 11
	this->state_table.emplace_back(false);
}
void Automata::initializeInputAlphabetMap(std::string in) {
	for(std::size_t i = 0; i < in.size(); ++i)
		input_map.insert({in[i], i});
}

void Automata::initializeTransitionFunction() {
	this->transition_function = std::vector<std::vector<std::size_t>>(this->state_table.size(), std::vector<std::size_t>(this->input_map.size(), 11));

	this->transition_function[0][this->input_map['(']] = 1;
	this->transition_function[0][this->input_map[')']] = 2;
	this->transition_function[0][this->input_map['*']] = 3;
	this->transition_function[0][this->input_map['+']] = 4;
	this->transition_function[0][this->input_map['-']] = 5;
	this->transition_function[0][this->input_map['/']] = 6;
	this->transition_function[0][this->input_map[' ']] = 0;
	this->transition_function[0][this->input_map['\n']] = 0;

	for(char i = '0'; i < '9' + 1; ++i)
		this->transition_function[0][this->input_map[i]] = 9;
	for(char i = 'A'; i < 'Z' + 1; ++i)
		this->transition_function[0][this->input_map[i]] = 10;
	for(char i = 'a'; i < 'z' + 1; ++i)
		this->transition_function[0][this->input_map[i]] = 10;

	this->transition_function[9][this->input_map['(']] = 7;
	this->transition_function[9][this->input_map[')']] = 7;
	this->transition_function[9][this->input_map['*']] = 7;
	this->transition_function[9][this->input_map['+']] = 7;
	this->transition_function[9][this->input_map['-']] = 7;
	this->transition_function[9][this->input_map['/']] = 7;
	this->transition_function[9][this->input_map[' ']] = 7;
	this->transition_function[9][this->input_map['\n']] = 7;

	for(char i = '0'; i < '9' + 1; ++i)
		this->transition_function[9][this->input_map[i]] = 9;
	for(char i = 'A'; i < 'Z' + 1; ++i)
		this->transition_function[9][this->input_map[i]] = 7;
	for(char i = 'a'; i < 'z' + 1; ++i)
		this->transition_function[9][this->input_map[i]] = 7;

	this->transition_function[10][this->input_map['(']] = 8;
	this->transition_function[10][this->input_map[')']] = 8;
	this->transition_function[10][this->input_map['*']] = 8;
	this->transition_function[10][this->input_map['+']] = 8;
	this->transition_function[10][this->input_map['-']] = 8;
	this->transition_function[10][this->input_map['/']] = 8;
	this->transition_function[10][this->input_map[' ']] = 8;
	this->transition_function[10][this->input_map['\n']] = 8;

	for(char i = '0'; i < '9' + 1; ++i)
		this->transition_function[10][this->input_map[i]] = 10;
	for(char i = 'A'; i < 'Z' + 1; ++i)
		this->transition_function[10][this->input_map[i]] = 10;
	for(char i = 'a'; i < 'z' + 1; ++i)
		this->transition_function[10][this->input_map[i]] = 10;
}