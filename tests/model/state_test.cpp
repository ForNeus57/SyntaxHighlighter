//
// Created by Dominik on 15.03.2023.
//


#include <gtest/gtest.h>

#include "../../includes/internal/headers/model/automata/state.h"


class StateTest: public ::testing::Test {
	protected:
		StateTest(): state(nullptr) {}
		void SetUp() override {}
		void TearDown() override {}
	protected:
		std::unique_ptr<State> state;
};

TEST_F(StateTest, ConstructorTest) {
	//	Default constructor
	state = std::make_unique<State>();
	EXPECT_FALSE(state->isAccepting());
	EXPECT_EQ(state->getReturnCode(), BaseToken::Codes::UNKNOWN);
	
	//	Custom constructor
	for (int i = BaseToken::Codes::START + 1; i < BaseToken::Codes::END; ++i) {
		state = std::make_unique<State>(static_cast<BaseToken::Codes>(i));
		EXPECT_TRUE(state->isAccepting());
		EXPECT_EQ(state->getReturnCode(), static_cast<BaseToken::Codes>(i));
	}
	
	EXPECT_THROW(std::make_unique<State>(BaseToken::Codes::START), std::invalid_argument);
	EXPECT_THROW(std::make_unique<State>(BaseToken::Codes::END), std::invalid_argument);
}

TEST_F(StateTest, StaticVariablesTest) {
}

TEST_F(StateTest, ConstructionTest) {

}