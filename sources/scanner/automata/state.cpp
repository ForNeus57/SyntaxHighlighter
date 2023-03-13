//
// Created by Dominik on 10.03.2023.
//

#include "state.h"

State::State(): return_code(Codes::UNKNOWN), is_starting(false), is_accepting(false) {}
State::State(bool s): return_code(Codes::UNKNOWN), is_starting(s), is_accepting(false) {}
State::State(Codes c): return_code(c), is_starting(false), is_accepting(true) {}
State::State(const State& source): return_code(Codes::UNKNOWN), is_starting(false), is_accepting(false) {
	this->copy(source);
}
State::State(State&& source) noexcept: return_code(Codes::UNKNOWN), is_starting(false), is_accepting(false) {
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
bool State::operator==(const State &rhs) const {
	return return_code == rhs.return_code &&
		   is_starting == rhs.is_starting &&
		   is_accepting == rhs.is_accepting;
}

bool State::operator!=(const State &rhs) const {
	return !(rhs == *this);
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

void State::copy(const State& source) {
	this->return_code = source.return_code;
	this->is_starting = source.is_starting;
	this->is_accepting = source.is_accepting;
}

void State::move(State&& source) {
	this->return_code = source.return_code;
	this->is_starting = source.is_starting;
	this->is_accepting = source.is_accepting;
}
