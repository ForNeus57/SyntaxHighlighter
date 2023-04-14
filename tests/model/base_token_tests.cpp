//
// Created by Dominik on 07.04.2023.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cctype>
#include <algorithm>

#include "../../includes/syntax_colorizer_lib/headers/model/token/base_token.h"


class BaseTokenMock: public BaseToken {
	public:
		BaseTokenMock(Codes c, std::size_t line, std::size_t col): BaseToken(c, line, col) {}
		virtual ~BaseTokenMock() = default;
	public:
		MOCK_METHOD(std::string, print, (), (const override));
		MOCK_METHOD(std::string, printHTML, (), (const override));
};

class BaseTokenTest: public ::testing::Test {
	protected:
		BaseTokenTest(): m0(nullptr), TEST_STRING("TEST") {
			m0 = nullptr;
			TEST_STRING = "TEST";
			DEFAULT_TEXT_POSITION = 0;
			ITERATION_LIMIT = 100;
		}
		void SetUp() override {
			m0 = new BaseTokenMock(BaseToken::Codes::KEYWORD, 0, 0);
		}
		void TearDown() override {
			delete m0;
		}
		BaseTokenMock* m0;
		std::string TEST_STRING;
		std::size_t DEFAULT_TEXT_POSITION;
		std::size_t ITERATION_LIMIT;
};

TEST_F(BaseTokenTest, StaticMethdosTest) {
	EXPECT_FALSE(BaseToken::isValidCode(BaseToken::Codes::START));
	EXPECT_FALSE(BaseToken::isValidCode(BaseToken::Codes::UNKNOWN));
	EXPECT_FALSE(BaseToken::isValidCode(BaseToken::Codes::END));
	for(std::size_t i = 1; i < BaseToken::Codes::END - 2; ++i)
		EXPECT_TRUE(BaseToken::isValidCode(static_cast<BaseToken::Codes>(i)));
	
	EXPECT_EQ(BaseToken::END + 1, BaseToken::getNumberOfCodes());
}

TEST_F(BaseTokenTest, StaticVariableTest) {
	//	Tests for INPUT_ALPHABET[...][...]
	for(char x : BaseToken::INPUT_ALPHABET[BaseToken::Alphabet::LETTERS])
		EXPECT_TRUE(std::isalpha(x));
	for(char x : BaseToken::INPUT_ALPHABET[BaseToken::Alphabet::NUMBERS])
		EXPECT_TRUE(std::isdigit(x));
	for(char x : BaseToken::INPUT_ALPHABET[BaseToken::Alphabet::WHITE_CHARACTERS])
		EXPECT_TRUE(std::isspace(x));
	for(char x : BaseToken::INPUT_ALPHABET[BaseToken::Alphabet::OPERATORS])
		EXPECT_TRUE(isascii(x) && ispunct(x));
	
	//	Tests for BaseToken::CODES_TYPES[...]
	EXPECT_EQ(BaseToken::getNumberOfCodes(), BaseToken::CODES_TYPES.size());
	EXPECT_EQ(BaseToken::CODES_TYPES.size(), BaseToken::CODES_TYPES.capacity());
	
	for(std::size_t i = 1; i < BaseToken::CODES_TYPES.size(); ++i) {
		EXPECT_TRUE(BaseToken::CODES_TYPES[i - 1] + 1 == BaseToken::CODES_TYPES[i]);
		EXPECT_TRUE(BaseToken::CODES_TYPES[i] >= BaseToken::Codes::START and BaseToken::CODES_TYPES[i] <= BaseToken::Codes::END);
	}
	
	//	Tests for BaseToken::POSSIBLE_COLOURS[...]
	EXPECT_LT(BaseToken::POSSIBLE_COLOURS.size(), BaseToken::getNumberOfCodes());
	
	EXPECT_NO_THROW(BaseToken::POSSIBLE_COLOURS[BaseToken::Codes::START]);
	EXPECT_NO_THROW(BaseToken::POSSIBLE_COLOURS[BaseToken::Codes::UNKNOWN]);
	EXPECT_NO_THROW(BaseToken::POSSIBLE_COLOURS[BaseToken::Codes::END]);
	
	for(const std::string& x : BaseToken::POSSIBLE_COLOURS)
		EXPECT_FALSE(x.empty());
}

TEST_F(BaseTokenTest, VirtualMethodsTest) {
	//	Tests for .print() method
	EXPECT_CALL(*m0, print())
			.Times(1)
			.WillOnce(::testing::Return(TEST_STRING));
	EXPECT_EQ(TEST_STRING, m0->print());
	//	Tests for .printHTML() method
	EXPECT_CALL(*m0, printHTML())
			.Times(1)
			.WillOnce(::testing::Return(TEST_STRING));
	EXPECT_EQ(TEST_STRING, m0->printHTML());
}

TEST_F(BaseTokenTest, MainConstructorTest) {
	EXPECT_THROW(BaseTokenMock(BaseToken::Codes::START, DEFAULT_TEXT_POSITION, DEFAULT_TEXT_POSITION), std::invalid_argument);
	EXPECT_THROW(BaseTokenMock(BaseToken::Codes::UNKNOWN, DEFAULT_TEXT_POSITION, DEFAULT_TEXT_POSITION), std::invalid_argument);
	EXPECT_THROW(BaseTokenMock(BaseToken::Codes::END, DEFAULT_TEXT_POSITION, DEFAULT_TEXT_POSITION), std::invalid_argument);
	for(std::size_t i = 1; i < BaseToken::Codes::END - 2; ++i)
		EXPECT_NO_THROW(BaseTokenMock(static_cast<BaseToken::Codes>(i), DEFAULT_TEXT_POSITION, DEFAULT_TEXT_POSITION));
}

TEST_F(BaseTokenTest, GettersAndSettersTest) {
	//	Getter methods
	for(std::size_t i = DEFAULT_TEXT_POSITION; i < ITERATION_LIMIT; ++i) {
		for(std::size_t j = DEFAULT_TEXT_POSITION; j < ITERATION_LIMIT; ++j) {
			for(std::size_t k = 1; k < BaseToken::Codes::END - 2; ++k) {
				delete m0;
				m0 = new BaseTokenMock(static_cast<BaseToken::Codes>(k), i, j);
				EXPECT_EQ(static_cast<BaseToken::Codes>(k), m0->getCode());
				EXPECT_EQ(i, m0->getLine());
				EXPECT_EQ(j, m0->getColumn());
				EXPECT_TRUE(std::find(BaseToken::POSSIBLE_COLOURS.begin(), BaseToken::POSSIBLE_COLOURS.end(), m0->getColour()) != BaseToken::POSSIBLE_COLOURS.end());
			}
		}
	}
}
