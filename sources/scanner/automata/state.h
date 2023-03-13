//
// Created by Dominik on 10.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_STATE_H
#define COMPILATION_THEORY_AND_COMPILERS_STATE_H

#include <iostream>

#include "token.h"

/**
 * @brief
 *
 * @param	count				-
 * @param	id					-
 * @param	generated_token_id	-
 * @param	is_accepting		-
 */
class State {
public:
	State();
	explicit State(bool);
	/**
	 * @brief
	 *
	 * @param	c
	 * @param	fun
	 */
	explicit State(Codes c);
	State(const State& source);
	State(State&& source) noexcept;
public:
	State& operator=(const State& rhs) noexcept;
	State& operator=(State&& rhs) noexcept;
	bool operator==(const State &rhs) const;
	bool operator!=(const State &rhs) const;
public:
	Codes getReturnCode() const;
	bool isStarting() const;
	bool isAccepting() const;
private:
	void copy(const State & source);
	void move(State && source);
private:
	Codes return_code;
	bool is_starting;
	bool is_accepting;
};

#endif	//	COMPILATION_THEORY_AND_COMPILERS_STATE_H
