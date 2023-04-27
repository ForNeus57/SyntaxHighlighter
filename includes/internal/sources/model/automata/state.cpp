//
// Created by Dominik on 10.03.2023.
//

#include "../../../headers/model/automata/state.h"

State::State(): return_code(BaseToken::Codes::UNKNOWN), is_accepting(false) {}
State::State(BaseToken::Codes c): return_code(c), is_accepting(true) {}

BaseToken::Codes State::getReturnCode() const {
	return this->return_code;
}

bool State::isAccepting() const {
	return this->is_accepting;
}
