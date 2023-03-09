//
// Created by Dominik on 08.03.2023.
//

#include "Automata.h"

Automata::Automata() {

}

std::size_t Automata::translateInputToAutomataTable(char in) {
	switch (in) {
		case '+':
			return 0;
		case '-':
			return 1;
		default:
			//	Throw error
			throw std::exception();
	}
}

void Automata::InitializeTokenTable() {

}
