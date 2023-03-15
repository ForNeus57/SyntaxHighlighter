/**
 * @file 	state.h
 * @version 0.027
 * @author 	Dominik Breksa, dominikbreksa@gmail.com
 * @date 	10.03.2023
 * @brief	Header file relating to State class.
 * @see		state.cpp file.
**/

#ifndef COMPILATION_THEORY_AND_COMPILERS_STATE_H
#define COMPILATION_THEORY_AND_COMPILERS_STATE_H

#include <iostream>

#include "token.h"

/**
 * @brief
 * @see		Automata class
 */
class State {
public:
	/**
	 * @brief	Default constructor making a state that returns Codes::UNKNOWN and isn't final.
	 */
	State();
	/**
	 * @brief
	 *
	 * @param	c	-
	 */
	explicit State(Codes c);
	/**
	 * @brief
	 * @param source
	 */
	State(const State& source);
	/**
	 * @brief
	 * @param source
	 */
	State(State&& source) noexcept;
public:
	State& operator=(const State& rhs) noexcept;
	State& operator=(State&& rhs) noexcept;
public:
	Codes getReturnCode() const;
	bool isAccepting() const;
private:
	void copy(const State & source);
	void move(State && source);
private:
	/**
	 * @brief	Instructions given to a Token constructor how to create token.
	 */
	Codes return_code;
	/**
	 * @brief	True / false if this state is accepting and have a meaning full value stored in a
	 */
	bool is_accepting;
};

#endif	//	COMPILATION_THEORY_AND_COMPILERS_STATE_H
