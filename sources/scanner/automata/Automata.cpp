//
// Created by Dominik on 08.03.2023.
//

#include "Automata.h"

Automata::Automata() {
	//this->current_state_number = Automata::STARTING_STATE_NUMBER;
}

Token Automata::generateTokenOutOfCurrentState() {
	if(this->current_state_number)



	this->reset();
	return Token('+', {0,0});
}
