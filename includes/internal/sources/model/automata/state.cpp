/**
 * @file 	state.cpp
 * @version 0.027
 * @author 	Dominik Breksa
 * @date 	10.03.2023
 * @brief	Source file relating to State class.
 * @see		state.h file.
**/

#include "../../../headers/model/automata/state.h"

const std::vector<std::function<std::unique_ptr<BaseToken>(BaseToken::Codes, const std::string&, std::size_t, std::size_t)>> State::token_constructor_dispatcher = {
	std::function<std::unique_ptr<BaseToken>(BaseToken::Codes, const std::string&, std::size_t, std::size_t)>(),						//	If the index == BaseToken::Codes::Start throw an exception
	[](BaseToken::Codes token_code, const std::string& input, std::size_t line, std::size_t column) -> std::unique_ptr<BaseToken> {
		return std::unique_ptr<BaseToken>(new Token<std::string>(token_code, input, line, column));
	},
	[](BaseToken::Codes token_code, const std::string& input, std::size_t line, std::size_t column) -> std::unique_ptr<BaseToken> {
		std::vector<std::string> keywords = {
			"auto",	"break", "case", "char", "const", "continue", "default", "do", "double",
			"else", "enum", "extern", "float",	"for", "goto", "if", "int", "long", "register",	"return",
			"short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned",
			"void", "volatile", "while", "false", "true"
		};
		if(std::find(keywords.begin(), keywords.end(), input) != keywords.end())
			token_code = BaseToken::Codes::KEYWORD;
		
		return std::unique_ptr<BaseToken>(new Token<std::string>(token_code, input, line, column));
	},
	[](BaseToken::Codes token_code, const std::string& input, std::size_t line, std::size_t column) -> std::unique_ptr<BaseToken> {
		int value = std::stoi(input);
		return std::unique_ptr<BaseToken>(new Token<int>(token_code, value, line, column));
	},
	[](BaseToken::Codes token_code, const std::string& input, std::size_t line, std::size_t column) -> std::unique_ptr<BaseToken> {
		double value = std::stod(input);
		return std::unique_ptr<BaseToken>(new Token<double>(token_code, value, line, column));
	},
	[](BaseToken::Codes token_code, const std::string& input, std::size_t line, std::size_t column) -> std::unique_ptr<BaseToken> {
		char value = input[0];
		return std::unique_ptr<BaseToken>(new Token<char>(token_code, value, line, column));
	},
	[](BaseToken::Codes token_code, const std::string& input, std::size_t line, std::size_t column) -> std::unique_ptr<BaseToken> {
		return std::unique_ptr<BaseToken>(new Token<std::string>(token_code, input, line, column));
	},
	[](BaseToken::Codes token_code, const std::string& input, std::size_t line, std::size_t column) -> std::unique_ptr<BaseToken> {		//	If the index == BaseToken::Codes::OPERATOR
		return std::unique_ptr<BaseToken>(new Token<std::string>(token_code, input, line, column));
	},
	[](BaseToken::Codes token_code, const std::string& input, std::size_t line, std::size_t column) -> std::unique_ptr<BaseToken> {		//	If the index == BaseToken::Codes::OPERATOR
		std::string change(input);
		change = std::regex_replace(change, std::regex(" "), "&nbsp");
		change = std::regex_replace(change, std::regex("\t"), "&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp");
		return std::unique_ptr<BaseToken>(new Token<std::string>(token_code, change, line, column));
	},
	std::function<std::unique_ptr<BaseToken>(BaseToken::Codes, const std::string&, std::size_t, std::size_t)>(),						//	If the index == BaseToken::Codes::UNKNOWN throw an exception
	std::function<std::unique_ptr<BaseToken>(BaseToken::Codes, const std::string&, std::size_t, std::size_t)>()							//	If the index == BaseToken::Codes::End throw an exception
};


State::State(): is_accepting(false), synchronize_index(false), return_code(BaseToken::Codes::UNKNOWN) {}
State::State(BaseToken::Codes c, bool index): is_accepting(true), synchronize_index(index), return_code(BaseToken::Codes::START) {
	//	BaseToken::Codes::UNKNOWN can be final for example it can be error state
	if (c == BaseToken::Codes::START || c == BaseToken::Codes::END) throw std::invalid_argument("Provided code for an argument is not a valid one! Please refer to: BaseToken::isValidCode({Provided BaseToke::Codes value}) static method.");
	
	this->return_code = c;
}

BaseToken::Codes State::getReturnCode() const {
	return this->return_code;
}
bool State::isAccepting() const {
	return this->is_accepting;
}
bool State::getSynchronizeIndex() const {
	return this->synchronize_index;
}

std::unique_ptr<BaseToken> State::constructToken(const std::string& input, std::size_t line, std::size_t column) {
	if (!this->is_accepting) throw std::runtime_error("Cannot create a token not from finishing state!");
	if (this->return_code == BaseToken::Codes::UNKNOWN) throw ErrorStateReached(input, line, column);
	
	return State::token_constructor_dispatcher[this->return_code](this->return_code, input, line, column);
}
