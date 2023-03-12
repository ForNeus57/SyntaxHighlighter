//
// Created by Dominik on 10.03.2023.
//

#include "State.h"

State::State(Codes c, pi fun, bool s, bool a): process_input(fun), return_code(c), is_starting(s), is_accepting(a) {}

pi State::getProcessInputFunction() const {
	return this->process_input;
}

Codes State::getReturnCode() const {
	return this->return_code;
}

bool State::isStarting() const {
	return this->is_starting;
}

bool State::isAccepting() const {
	return this->is_accepting;
}