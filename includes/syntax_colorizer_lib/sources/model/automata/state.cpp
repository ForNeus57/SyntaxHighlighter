//
// Created by Dominik on 10.03.2023.
//

#include "../../../headers/model/automata/state.h"

State::State(): return_code(BaseToken::Codes::UNKNOWN), is_accepting(false) {}
State::State(BaseToken::Codes c): return_code(c), is_accepting(true) {}
State::State(const State& source): return_code(BaseToken::Codes::UNKNOWN), is_accepting(false) {
	this->copy(source);
}
State::State(State&& source) noexcept: return_code(BaseToken::Codes::UNKNOWN), is_accepting(false) {
	this->move(std::move(source));
}

State& State::operator=(const State& rhs) noexcept {
	if (this == &rhs) return *this;

	this->copy(rhs);
	return *this;
}
State& State::operator=(State&& rhs) noexcept {
	if(this != &rhs) {
		this->move(std::move(rhs));
	}
	return *this;
}

BaseToken::Codes State::getReturnCode() const {
	return this->return_code;
}

bool State::isAccepting() const {
	return this->is_accepting;
}

void State::copy(const State& source) {
	this->return_code = source.return_code;
	this->is_accepting = source.is_accepting;
}

void State::move(State&& source) {
	this->return_code = source.return_code;
	this->is_accepting = source.is_accepting;
}
