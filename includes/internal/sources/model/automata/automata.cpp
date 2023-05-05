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
	this->input_since_last_reset.push_back(in);
}

std::unique_ptr<BaseToken> Automata::generateTokenOutOfCurrentState(std::size_t line, std::size_t column) {
	//	Prevent creation of a token not from final state.
	if(!this->isInAcceptingState()) throw std::runtime_error("Cannot attempt to generate a token not from accepting state!");
	try {
		if (this->synchroniseIndex()) {
			return this->state_table[this->current_state_number].constructToken(this->input_since_last_reset.substr(0, this->input_since_last_reset.size() - 1), line, column);
		} else
			return this->state_table[this->current_state_number].constructToken(this->input_since_last_reset, line, column);
	} catch(ErrorStateReached& err) {
		std::cerr << err.what();
		exit(1);
	}
}

bool Automata::synchroniseIndex() {
	return this->state_table[this->current_state_number].getSynchronizeIndex();
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
	
	//	Identifier and keyword state configuration
	//	1
	this->state_table.emplace_back();
	//	2
	this->state_table.emplace_back(BaseToken::Codes::IDENTIFIER, true);
	
	//	Literal int state configuration
	//	3
	this->state_table.emplace_back();
	//	4
	this->state_table.emplace_back(BaseToken::Codes::LITERAL_INT, true);
	
	//	Literal double state configuration
	//	5
	this->state_table.emplace_back();
	//	6
	this->state_table.emplace_back(BaseToken::Codes::LITERAL_DOUBLE, true);
	
	//	Special characters state configuration
	//	7
	this->state_table.emplace_back(BaseToken::Codes::SPECIAL_CHARACTERS, false);
	
	//	Strings state configuration
	//	8
	this->state_table.emplace_back();
	//	9
	this->state_table.emplace_back(BaseToken::Codes::STRINGS, false);
	
	//	Operator state configuration
	//	10
	this->state_table.emplace_back();
	//	11
	this->state_table.emplace_back();
	//	12
	this->state_table.emplace_back();
	//	13
	this->state_table.emplace_back();
	//	14
	this->state_table.emplace_back();
	//	15
	this->state_table.emplace_back();
	//	16
	this->state_table.emplace_back();
	//	17
	this->state_table.emplace_back(BaseToken::Codes::OPERATOR, false);
	//	18
	this->state_table.emplace_back(BaseToken::Codes::OPERATOR, true);
	
	//	19
	this->state_table.emplace_back();
	//	20
	this->state_table.emplace_back(BaseToken::Codes::WHITE_SYMBOL, true);
	
	//	Error state id = 21
	this->state_table.emplace_back(BaseToken::Codes::UNKNOWN, true);
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
	this->transition_function = std::vector<std::vector<std::size_t>>(this->state_table.size(), std::vector<std::size_t>(this->input_map.size(), Automata::ERROR_STATE_NUMBER));
	
	//	Initial state configuration
	for(const char& in : alphabet[BaseToken::Alphabet::LETTERS])
		this->transition_function[0][this->input_map[in]] = 1;
	for(const char& in : alphabet[BaseToken::Alphabet::NUMBERS])
		this->transition_function[0][this->input_map[in]] = 3;
	for(const char& in : alphabet[BaseToken::Alphabet::WHITE_CHARACTERS])
		this->transition_function[0][this->input_map[in]] = 19;
	
	this->transition_function[0][this->input_map['[']] = 7;
	this->transition_function[0][this->input_map[']']] = 7;
	this->transition_function[0][this->input_map['(']] = 7;
	this->transition_function[0][this->input_map[')']] = 7;
	this->transition_function[0][this->input_map['{']] = 7;
	this->transition_function[0][this->input_map['}']] = 7;
	this->transition_function[0][this->input_map[',']] = 7;
	this->transition_function[0][this->input_map['#']] = 7;
	this->transition_function[0][this->input_map[':']] = 7;
	this->transition_function[0][this->input_map[';']] = 7;
	this->transition_function[0][this->input_map['%']] = 7;
	
	this->transition_function[0][this->input_map['"']] = 8;
	
	this->transition_function[0][this->input_map['*']] = 10;
	this->transition_function[0][this->input_map['/']] = 10;
	this->transition_function[0][this->input_map['!']] = 10;
	this->transition_function[0][this->input_map['=']] = 10;
	
	this->transition_function[0][this->input_map['+']] = 11;
	this->transition_function[0][this->input_map['-']] = 12;
	this->transition_function[0][this->input_map['|']] = 13;
	this->transition_function[0][this->input_map['&']] = 14;
	this->transition_function[0][this->input_map['<']] = 15;
	this->transition_function[0][this->input_map['>']] = 16;
	
	this->transition_function[0][this->input_map['.']] = 17;
	this->transition_function[0][this->input_map[',']] = 17;
	this->transition_function[0][this->input_map['^']] = 17;
	this->transition_function[0][this->input_map['~']] = 17;
	
	//	Identifier and keyword state configuration
	for(const char& in : alphabet[BaseToken::Alphabet::LETTERS])
		this->transition_function[1][this->input_map[in]] = 1;
	for(const char& in : alphabet[BaseToken::Alphabet::NUMBERS])
		this->transition_function[1][this->input_map[in]] = 1;
	for(const char& in : alphabet[BaseToken::Alphabet::WHITE_CHARACTERS])
		this->transition_function[1][this->input_map[in]] = 2;
	for(const char& in : alphabet[BaseToken::Alphabet::OPERATORS])
		this->transition_function[1][this->input_map[in]] = 2;
	
	//	Literal int state configuration
	for(const char& in : alphabet[BaseToken::Alphabet::LETTERS])
		this->transition_function[3][this->input_map[in]] = 4;
	for(const char& in : alphabet[BaseToken::Alphabet::NUMBERS])
		this->transition_function[3][this->input_map[in]] = 3;
	for(const char& in : alphabet[BaseToken::Alphabet::WHITE_CHARACTERS])
		this->transition_function[3][this->input_map[in]] = 4;
	for(const char& in : alphabet[BaseToken::Alphabet::OPERATORS])
		this->transition_function[3][this->input_map[in]] = 4;
	
	this->transition_function[3][this->input_map['.']] = 5;
	
	//	Literal double state configuration
	for(const char& in : alphabet[BaseToken::Alphabet::LETTERS])
		this->transition_function[5][this->input_map[in]] = 6;
	for(const char& in : alphabet[BaseToken::Alphabet::NUMBERS])
		this->transition_function[5][this->input_map[in]] = 5;
	for(const char& in : alphabet[BaseToken::Alphabet::WHITE_CHARACTERS])
		this->transition_function[5][this->input_map[in]] = 6;
	for(const char& in : alphabet[BaseToken::Alphabet::OPERATORS])
		this->transition_function[5][this->input_map[in]] = 6;
	
	//	Special characters state configuration
	
	//	String state configuration
	for(const char& in : alphabet[BaseToken::Alphabet::LETTERS])
		this->transition_function[8][this->input_map[in]] = 8;
	for(const char& in : alphabet[BaseToken::Alphabet::NUMBERS])
		this->transition_function[8][this->input_map[in]] = 8;
	for(const char& in : alphabet[BaseToken::Alphabet::WHITE_CHARACTERS])
		this->transition_function[8][this->input_map[in]] = 8;
	for(const char& in : alphabet[BaseToken::Alphabet::OPERATORS])
		this->transition_function[8][this->input_map[in]] = 8;
	
	this->transition_function[8][this->input_map['"']] = 9;
	
	//	Operator state configuration
	for(const char& in : alphabet[BaseToken::Alphabet::LETTERS])
		this->transition_function[10][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::NUMBERS])
		this->transition_function[10][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::WHITE_CHARACTERS])
		this->transition_function[10][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::OPERATORS])
		this->transition_function[10][this->input_map[in]] = 18;
	
	this->transition_function[10][this->input_map['=']] = 17;
	
	for(const char& in : alphabet[BaseToken::Alphabet::LETTERS])
		this->transition_function[11][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::NUMBERS])
		this->transition_function[11][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::WHITE_CHARACTERS])
		this->transition_function[11][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::OPERATORS])
		this->transition_function[11][this->input_map[in]] = 18;
	
	this->transition_function[11][this->input_map['+']] = 17;
	this->transition_function[11][this->input_map['=']] = 17;
	
	for(const char& in : alphabet[BaseToken::Alphabet::LETTERS])
		this->transition_function[12][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::NUMBERS])
		this->transition_function[12][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::WHITE_CHARACTERS])
		this->transition_function[12][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::OPERATORS])
		this->transition_function[12][this->input_map[in]] = 18;
	
	this->transition_function[12][this->input_map['-']] = 17;
	this->transition_function[12][this->input_map['=']] = 17;
	
	for(const char& in : alphabet[BaseToken::Alphabet::LETTERS])
		this->transition_function[13][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::NUMBERS])
		this->transition_function[13][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::WHITE_CHARACTERS])
		this->transition_function[13][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::OPERATORS])
		this->transition_function[13][this->input_map[in]] = 18;
	
	this->transition_function[13][this->input_map['|']] = 17;
	
	for(const char& in : alphabet[BaseToken::Alphabet::LETTERS])
		this->transition_function[14][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::NUMBERS])
		this->transition_function[14][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::WHITE_CHARACTERS])
		this->transition_function[14][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::OPERATORS])
		this->transition_function[14][this->input_map[in]] = 18;
	
	this->transition_function[14][this->input_map['&']] = 17;
	
	for(const char& in : alphabet[BaseToken::Alphabet::LETTERS])
		this->transition_function[15][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::NUMBERS])
		this->transition_function[15][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::WHITE_CHARACTERS])
		this->transition_function[15][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::OPERATORS])
		this->transition_function[15][this->input_map[in]] = 18;
	
	this->transition_function[15][this->input_map['=']] = 17;
	this->transition_function[15][this->input_map['<']] = 17;
	
	for(const char& in : alphabet[BaseToken::Alphabet::LETTERS])
		this->transition_function[16][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::NUMBERS])
		this->transition_function[16][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::WHITE_CHARACTERS])
		this->transition_function[16][this->input_map[in]] = 18;
	for(const char& in : alphabet[BaseToken::Alphabet::OPERATORS])
		this->transition_function[16][this->input_map[in]] = 18;
	
	this->transition_function[16][this->input_map['=']] = 17;
	this->transition_function[16][this->input_map['>']] = 17;
	
	//	White symbols ....
	for(const char& in : alphabet[BaseToken::Alphabet::LETTERS])
		this->transition_function[19][this->input_map[in]] = 20;
	for(const char& in : alphabet[BaseToken::Alphabet::NUMBERS])
		this->transition_function[19][this->input_map[in]] = 20;
	for(const char& in : alphabet[BaseToken::Alphabet::WHITE_CHARACTERS])
		this->transition_function[19][this->input_map[in]] = 19;
	for(const char& in : alphabet[BaseToken::Alphabet::OPERATORS])
		this->transition_function[19][this->input_map[in]] = 20;
}