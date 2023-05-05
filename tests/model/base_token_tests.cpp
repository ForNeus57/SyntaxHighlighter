//
// Created by Dominik on 07.04.2023.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cctype>
#include <algorithm>
#include <fstream>

#include "../../includes/internal/headers/model/token/base_token.h"


std::vector<std::size_t> getTestDataFromFile(const std::string& file_name) {
	int num_values;
	
	// Read the number of values from the binary file
	std::ifstream file(file_name, std::ios::binary);
	if (file.is_open())
		file.read(reinterpret_cast<char*>(&num_values), sizeof(int));
	else
		throw std::runtime_error("Unable to input text file:" + file_name);
	
	// Read the values from the binary file
	std::vector<std::size_t> values(static_cast<std::size_t>(num_values));
	file.read(reinterpret_cast<char*>(values.data()), unsigned(num_values) * sizeof(int));
	
	file.close();
	
	return values;
}

class BaseTokenMock: public BaseToken {
	public:
		BaseTokenMock(Codes c, std::size_t line, std::size_t col): BaseToken(c, line, col) {}
		~BaseTokenMock() override = default;
	public:
		MOCK_METHOD(std::string, print, (), (const override));
		MOCK_METHOD(std::string, printHTML, (), (const override));
		MOCK_METHOD(std::size_t , valueShift, (), (const override));
		MOCK_METHOD(std::size_t , printShift, (), (const override));
		MOCK_METHOD(std::size_t , printHTMLShift, (), (const override));
};

class BaseTokenTest: public ::testing::Test {
	protected:
		BaseTokenTest(): m0(nullptr), TEST_STRING("TEST"), DEFAULT_TEXT_POSITION(0), TEST_VALUES() {
			TEST_VALUES = getTestDataFromFile(R"(..\..\tests\input\test_data\random_size_t_values.bin)");
		}
		void SetUp() override {
			m0 = std::make_unique<BaseTokenMock>(BaseToken::Codes::KEYWORD, 0, 0);
		}
		void TearDown() override {}
		std::unique_ptr<BaseTokenMock> m0;
		std::string TEST_STRING;
		std::size_t DEFAULT_TEXT_POSITION;
		std::vector<std::size_t> TEST_VALUES;
};

TEST_F(BaseTokenTest, StaticMethodsTest) {
	//	.convertCodesToString()
	EXPECT_EQ("START", BaseToken::convertCodesToString(BaseToken::Codes::START));
	EXPECT_EQ("KEYWORD", BaseToken::convertCodesToString(BaseToken::Codes::KEYWORD));
	EXPECT_EQ("IDENTIFIER", BaseToken::convertCodesToString(BaseToken::Codes::IDENTIFIER));
	EXPECT_EQ("LITERAL_INT", BaseToken::convertCodesToString(BaseToken::Codes::LITERAL_INT));
	EXPECT_EQ("LITERAL_DOUBLE", BaseToken::convertCodesToString(BaseToken::Codes::LITERAL_DOUBLE));
	EXPECT_EQ("SPECIAL_CHARACTERS", BaseToken::convertCodesToString(BaseToken::Codes::SPECIAL_CHARACTERS));
	EXPECT_EQ("STRINGS", BaseToken::convertCodesToString(BaseToken::Codes::STRINGS));
	EXPECT_EQ("OPERATOR", BaseToken::convertCodesToString(BaseToken::Codes::OPERATOR));
	EXPECT_EQ("UNKNOWN", BaseToken::convertCodesToString(BaseToken::Codes::UNKNOWN));
	EXPECT_EQ("END", BaseToken::convertCodesToString(BaseToken::Codes::END));
	
	//	.isValidCode()
	EXPECT_FALSE(BaseToken::isValidCode(BaseToken::Codes::START));
	EXPECT_FALSE(BaseToken::isValidCode(BaseToken::Codes::UNKNOWN));
	EXPECT_FALSE(BaseToken::isValidCode(BaseToken::Codes::END));
	for(std::size_t i = 1; i < BaseToken::Codes::END - 2; ++i)
		EXPECT_TRUE(BaseToken::isValidCode(static_cast<BaseToken::Codes>(i)));
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
		EXPECT_TRUE(isascii(x) and ispunct(x));
	
	//	Tests for BaseToken::CODES_TYPES[...]
	EXPECT_EQ(BaseToken::CODES_TYPES.size(), BaseToken::CODES_TYPES.capacity());
	
	for(std::size_t i = 1; i < BaseToken::CODES_TYPES.size(); ++i) {
		EXPECT_TRUE(BaseToken::CODES_TYPES[i - 1] + 1 == BaseToken::CODES_TYPES[i]);
		EXPECT_TRUE(BaseToken::CODES_TYPES[i] >= BaseToken::Codes::START and BaseToken::CODES_TYPES[i] <= BaseToken::Codes::END);
	}
	
	//	Tests for BaseToken::POSSIBLE_COLOURS[...]
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

TEST_F(BaseTokenTest, GettersAndSettersAndMemoryLeakTest) {
	//	Getter methods
	for(std::size_t i: TEST_VALUES) {
		for(std::size_t j: TEST_VALUES) {
			for(std::size_t k = 1; k < BaseToken::Codes::END - 2; ++k) {
				m0 = std::make_unique<BaseTokenMock>(static_cast<BaseToken::Codes>(k), i, j);
				ASSERT_NE(m0.get(), nullptr);
				EXPECT_EQ(static_cast<BaseToken::Codes>(k), m0->getCode());
				EXPECT_EQ(i, m0->getLine());
				EXPECT_EQ(j, m0->getColumn());
				EXPECT_TRUE(std::find(BaseToken::POSSIBLE_COLOURS.begin(), BaseToken::POSSIBLE_COLOURS.end(), m0->getColour()) != BaseToken::POSSIBLE_COLOURS.end());
				m0.reset();
				ASSERT_EQ(m0.get(), nullptr);
			}
		}
	}
}
