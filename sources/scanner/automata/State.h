//
// Created by Dominik on 10.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_STATE_H
#define COMPILATION_THEORY_AND_COMPILERS_STATE_H

#include <iostream>

#include "Token.h"

typedef std::variant<unsigned int, char, std::string> (*pi)(std::string);

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
	explicit State(Codes c, pi fun);
	State(const State& source);
	State(State&& source) noexcept;
public:
	State& operator=(const State& rhs) noexcept;
	State& operator=(State&& rhs) noexcept;
	bool operator==(const State &rhs) const;
	bool operator!=(const State &rhs) const;
public:
	pi getProcessInputFunction() const;
	Codes getReturnCode() const;
	bool isStarting() const;
	bool isAccepting() const;
private:
	void copy(const State & source);
	void move(State && source);
private:
	std::variant<unsigned int, char, std::string> (*process_input)(std::string);
	Codes return_code;
	bool is_starting;
	bool is_accepting;
};


#endif	//	COMPILATION_THEORY_AND_COMPILERS_STATE_H
