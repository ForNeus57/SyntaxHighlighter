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
	/**
	 * @brief
	 *
	 * @param	c
	 * @param	fun
	 * @param	s
	 * @param	a
	 */
	State(Codes c, pi fun, bool s, bool a);
public:
	pi getProcessInputFunction() const;
	Codes getReturnCode() const;
	bool isStarting() const;
	bool isAccepting() const;
private:
	std::variant<unsigned int, char, std::string> (*process_input)(std::string);
	Codes return_code;
	bool is_starting;
	bool is_accepting;
};


#endif	//	COMPILATION_THEORY_AND_COMPILERS_STATE_H
