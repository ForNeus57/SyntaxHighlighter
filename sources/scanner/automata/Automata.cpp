//
// Created by Dominik on 08.03.2023.
//

#include "Automata.h"

Automata::Automata() {
	this->initializeStateTable();
}

Token Automata::generateTokenOutOfCurrentState() {
	if(this->current_state_number)



	this->reset();
	return Token('+', {0,0});
}

void Automata::initializeStateTable() {
	this->state_table = {
			{true, false},
			{false, false},
			{false, false},
			{false, false},
			{false, false},
			{false, false},
			{false, false},
			{false, false},
	}
}
