/**
 * @file 	Scanner.cpp
 * @version 0.027
 * @author 	Dominik Breksa
 * @date 	08.03.2023
 * @brief	Source file relating to Scanner class.
 * @see		Scanner.h
**/

#include "../../headers/model/scanner.h"

Scanner::Scanner(): col_index(Scanner::RESET_INDEX), line_index(Scanner::RESET_INDEX), shift_index(Scanner::RESET_INDEX), difference(Scanner::RESET_INDEX), A(BaseToken::INPUT_ALPHABET){}

std::stringstream Scanner::operator()(std::istream* in, std::ostream* out, std::string (BaseToken::*format)() const) {
	std::stringstream s;
	std::string line;
	
	while(std::getline(*in, line)) {
		if (in->fail() || in->eof()) {
			*out << "Exiting...\n";
			break;
		}
		this->addNextLine(line);
		s << this->processLine();
	}
	
	return s;
}
std::stringstream Scanner::operator()(std::ifstream& in_file, std::string (BaseToken::*format)() const) {
	std::stringstream s;
	std::string line;
	
	while(std::getline(in_file, line)) {
		this->addNextLine(line);
		s << this->processLine();
	}
	
	return s;
}
void Scanner::operator()(std::ifstream& in_file, std::ofstream& out_file, std::string (BaseToken::*format)() const) {
	std::string line;
	
	while(std::getline(in_file, line)) {
		this->addNextLine(line);
		out_file << this->processLine();
	}
}
void Scanner::addNextLine(const std::string& in) {
	this->input = in;
	this->col_index = Scanner::RESET_INDEX;
	this->shift_index = Scanner::RESET_INDEX;
	this->difference = Scanner::RESET_INDEX;
	this->line_index++;
}
std::string Scanner::processLine() {
	std::string output{};
	while(true) {							//	Generate all the tokens in this line.
		std::optional<std::unique_ptr<BaseToken>> generated_token;
		try {
			generated_token = this->getToken();			//	I use a method call instead of a function, but I think, that it isn't much of a problem.
		} catch (const UnknownSymbol& err) {
			std::cout << err.what();
			break;
		} catch (const ErrorStateReached& err) {
			std::cout << err.what();
			break;
		}
		if (generated_token) {
			std::string print{};
			std::size_t shift = generated_token.value()->valueShift();
			std::size_t tmp_shift = generated_token.value()->printHTMLShift();
			std::cout <<BaseToken::convertCodesToString(generated_token.value()->getCode()) << std::endl;
			switch (generated_token.value()->getCode()) {
				case BaseToken::KEYWORD:
				case BaseToken::IDENTIFIER:
				case BaseToken::STRINGS: {
					auto* token_string = dynamic_cast<Token<std::string>*>(generated_token.value().get());
					print = token_string->printHTML();
					break;
				}
				case BaseToken::LITERAL_INT: {
					auto* token_int = dynamic_cast<Token<int>*>(generated_token.value().get());
					print = token_int->printHTML();
					break;
				}
				case BaseToken::LITERAL_DOUBLE: {
					auto* token_double = dynamic_cast<Token<double>*>(generated_token.value().get());
					print = token_double->printHTML();
					break;
				}
				case BaseToken::SPECIAL_CHARACTERS: {
					auto* token_char = dynamic_cast<Token<char>*>(generated_token.value().get());
					print = token_char->printHTML();
					break;
				}
				case BaseToken::OPERATOR: {
					auto* token_string = dynamic_cast<Token<std::string>*>(generated_token.value().get());
					if (token_string->getValue().size() == 1 and token_string->getValue()[0] == '<') {
						print = "<pra style=\"color: " + token_string->getColour() +"\">&lt</pra>";
						shift = 3;
					} else if (token_string->getValue().size() == 1 and token_string->getValue()[0] == '>') {
						print = "<pra style=\"color: " + token_string->getColour() +"\">&gt</pra>";
						shift = 3;
					} else {
						print = token_string->printHTML();
					}
					break;
				}
				case BaseToken::WHITE_SYMBOL: {
					auto* token_string = dynamic_cast<Token<std::string>*>(generated_token.value().get());
					print = token_string->printHTML();
					break;
				}
				default:
					std::cerr << "Error!" << std::endl;
					print = "";
					break;
			}
			std::cout << print << std::endl;
			std::cout << this->col_index << std::endl;
			output.append(print);
			this->shift_index += tmp_shift;
			std::cout << output << std::endl;
		} else break;
	}
	return output;
}
std::optional<std::unique_ptr<BaseToken>> Scanner::getToken() {
	difference = Scanner::RESET_INDEX;
	//	Make sure we are at the accepting state
	for (; !A.isInAcceptingState() and col_index < input.size(); col_index++, shift_index++, difference++)
		A.changeState(input[col_index]);
	if (A.isInAcceptingState()) {
		//	See what state we are in add create token with states instructions.
		std::unique_ptr<BaseToken> t = A.generateTokenOutOfCurrentState(line_index, col_index + 1);
		if (A.synchroniseIndex()) {
			col_index--;
			shift_index--;
			difference--;
		}
		//	Reset DFA current input, to be ready for next token.
		A.reset();
		return t;
	}
	A.reset();
	return {};
}
bool Scanner::isEmpty() {
	return this->col_index >= this->input.size();
}