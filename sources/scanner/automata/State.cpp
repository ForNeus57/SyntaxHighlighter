//
// Created by Dominik on 10.03.2023.
//

#include "State.h"

State::State() {
	this->id = count;
	this->is_accepting = false;
	State::count++;
}

State::State(bool a) {
	this->id = count;
	this->is_accepting = a;
	State::count++;
}

std::size_t State::getId() {
	return this->id;
}

bool State::isAccepting() {
	return this->is_accepting;
}