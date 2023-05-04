/**
 * @file 	automata.cpp
 * @version 0.027
 * @author 	Dominik Breksa
 * @date 	08.03.2023
 * @brief	Source file relating to Automata class.
 * @see		automata.h file.
**/

#include "../../../headers/model/automata/automata.h"

Automata::Automata(const std::vector<std::vector<char>>& alphabet): current_state_number(Automata::STARTING_STATE_NUMBER) {
	this->initializeStateTable();
	this->initializeInputAlphabetMap(alphabet);
	this->initializeTransitionFunction(alphabet);
}

void Automata::changeState(char in) {
	//	Make sure that we try to insert characters that are in provided in the alphabet.
	if (this->input_map.find(in) == this->input_map.end()) throw UnknownSymbol(this->input_since_last_reset);

	this->current_state_number = this->transition_function[this->current_state_number][this->input_map[in]];
	if (std::find(BaseToken::INPUT_ALPHABET[BaseToken::Alphabet::WHITE_CHARACTERS].begin(), BaseToken::INPUT_ALPHABET[BaseToken::Alphabet::WHITE_CHARACTERS].end(), in) == BaseToken::INPUT_ALPHABET[BaseToken::Alphabet::WHITE_CHARACTERS].end()){
		this->input_since_last_reset.push_back(in);
	}
}

std::unique_ptr<BaseToken> Automata::generateTokenOutOfCurrentState(std::size_t line, std::size_t column) {
	//	Prevent creation of a token not from final state.
	if(!this->isInAcceptingState()) throw std::runtime_error("Cannot attempt to generate a token not from accepting state!");
	try {
		return this->state_table[this->current_state_number].constructToken(this->input_since_last_reset, line, column);
	} catch(ErrorStateReached& err) {
		std::cerr << err.what();
		exit(1);
	}
}

bool Automata::synchroniseIndex() {
	if(!this->isInAcceptingState()) return false;

	/*switch (this->state_table[this->current_state_number].getReturnCode()) {
		case Codes::IDENTIFIER: case Codes::UNSIGNED_INTEGER_NUMBER:
			return true;
		case Codes::UNKNOWN: case Codes::LEFT_BRACKET: case Codes::RIGHT_BRACKET: case Codes::TIMES: case Codes::PLUS: case Codes::MINUS: case Codes::DIVIDED:
			return false;
	}
	return false;*/
}

void Automata::reset() {
	this->current_state_number = Automata::STARTING_STATE_NUMBER;
	this->input_since_last_reset.clear();
}

bool Automata::isInAcceptingState() const {
	return this->state_table[this->current_state_number].isAccepting();
}

void Automata::initializeStateTable() {
	this->state_table = std::vector<State>();
	//	Starting State id = 0
	this->state_table.emplace_back();
	//	Finishing state
	for(Codes x : Token::CODES_TYPES) {
		if(x == Codes::UNKNOWN) continue;
		else this->state_table.emplace_back(x);
	}
	for(size_t i = 0; i < 2; ++i)
		this->state_table.emplace_back();
	//	Error state id = 11
	this->state_table.emplace_back();
}
void Automata::initializeInputAlphabetMap(const std::vector<std::vector<char>>& alphabet) {
	size_t i = 0;
	for(const auto& val: alphabet)
		for(const auto& y : val) {
			this->input_map.insert({y, i});
			++i;
		}
}

void Automata::initializeTransitionFunction(const std::vector<std::vector<char>>& alphabet) {
	//	Allocate the memory and set all the values to error state, for protection.
	this->transition_function = std::vector<std::vector<std::size_t>>(this->state_table.size(), std::vector<std::size_t>(this->input_map.size(), 11));

	//	Set the next state to other symbols
	this->transition_function[0][this->input_map['(']] = 1;
	this->transition_function[0][this->input_map[')']] = 2;
	this->transition_function[0][this->input_map['*']] = 3;
	this->transition_function[0][this->input_map['+']] = 4;
	this->transition_function[0][this->input_map['-']] = 5;
	this->transition_function[0][this->input_map['/']] = 6;

	for(char i : alphabet[Alphabet::WHITE_CHARACTERS])
		this->transition_function[0][this->input_map[i]] = 0;
	for(char i : alphabet[Alphabet::NUMBERS])
		this->transition_function[0][this->input_map[i]] = 9;
	for(char i : alphabet[Alphabet::LETTERS])
		this->transition_function[0][this->input_map[i]] = 10;

	for(char i : alphabet[Alphabet::SYMBOLS])
		this->transition_function[9][this->input_map[i]] = 7;
	for(char i : alphabet[Alphabet::WHITE_CHARACTERS])
		this->transition_function[9][this->input_map[i]] = 7;

	for(char i : alphabet[Alphabet::NUMBERS])
		this->transition_function[9][this->input_map[i]] = 9;
	for(char i : alphabet[Alphabet::LETTERS])
		this->transition_function[9][this->input_map[i]] = 7;

	for(char i : alphabet[Alphabet::SYMBOLS])
		this->transition_function[10][this->input_map[i]] = 8;
	for(char i : alphabet[Alphabet::WHITE_CHARACTERS])
		this->transition_function[10][this->input_map[i]] = 8;

	for(char i : alphabet[Alphabet::NUMBERS])
		this->transition_function[10][this->input_map[i]] = 10;
	for(char i : alphabet[Alphabet::LETTERS])
		this->transition_function[10][this->input_map[i]] = 10;
}