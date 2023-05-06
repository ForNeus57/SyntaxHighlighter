/**
 * @file 	state.h
 * @version 0.027
 * @author 	Dominik Breksa
 * @date 	10.03.2023
 * @brief	Header file relating to State class.
 * @see		state.cpp file.
**/

#ifndef SYNTAX_HIGHLIGHTER_STATE_H
#define SYNTAX_HIGHLIGHTER_STATE_H


#include <iostream>
#include <memory>
#include <functional>
#include <algorithm>
#include <regex>

#include "../token/token.h"
#include "../../exceptions/error_state_reached.h"


/**
 * @brief	Class representing single State in Automata class. It is also responsible of creating correct token pointer to base class.
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
		explicit State(BaseToken::Codes c, bool);
		/**
		 * @brief
		 * @param source
		 */
		State(const State& source) = default;
		/**
		 * @brief
		 * @param source
		 */
		State(State&& source) noexcept = default;
	public:
		State& operator=(const State& rhs) = default;
		State& operator=(State&& rhs) noexcept = default;
	public:
		/**
		 * @brief
		 * @return
		 */
		BaseToken::Codes getReturnCode() const;
		/**
		 * @brief
		 * @return
		 */
		bool isAccepting() const;
		bool getSynchronizeIndex() const;
	public:
		/**
		 * @brief
		 *
		 * @todo	Make this method more safe to use
		 *
		 * @return
		 */
		std::unique_ptr<BaseToken> constructToken(const std::string&, std::size_t, std::size_t);
	public:
		const static std::vector<std::function<std::unique_ptr<BaseToken>(BaseToken::Codes, const std::string&, std::size_t, std::size_t)>> token_constructor_dispatcher;
	private:
		/**
		 * @brief	True / false if this state is accepting and have a meaning full value stored in a
		 */
		bool is_accepting;
		bool synchronize_index;
		/**
		 * @brief	Instructions given to a Token constructor how to create token.
		 */
		BaseToken::Codes return_code;
};

#endif	//	SYNTAX_HIGHLIGHTER_STATE_H
