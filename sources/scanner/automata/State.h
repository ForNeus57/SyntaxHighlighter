//
// Created by Dominik on 10.03.2023.
//

#ifndef COMPILATION_THEORY_AND_COMPILERS_STATE_H
#define COMPILATION_THEORY_AND_COMPILERS_STATE_H

#include <iostream>

/**
 * @brief
 *
 * @param	count
 * @param	id
 * @param	is_accepting
 */
class State {
public:
	State();
	explicit State(bool);
public:
	std::size_t getId();
	bool isAccepting();
private:
	static std::size_t count;
	std::size_t id;
	bool is_accepting;
};

class StateTable {
public:

public:
	const static std::size_t TOTAL_NUMBER_OF_STATES = 256;
};


#endif	//	COMPILATION_THEORY_AND_COMPILERS_STATE_H
