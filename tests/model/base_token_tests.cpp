//
// Created by Dominik on 07.04.2023.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cctype>
#include <algorithm>

#include "../../includes/internal/headers/model/token/base_token.h"


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
			TEST_VALUES = {1049544336, 1074442503, 687392545, 1955552446, 1168883164, 415136718, 1398007497, 17107835, 609012671, 271730254, 841420711, 247809451, 1090393496, 562900903, 642651866, 1736305822, 1189710974, 1433360269, 1366822096, 176765774, 1692468001, 1437163006, 1957229471, 1300716634, 608641288, 612721961, 396322064, 1489715469, 880426812, 2044843973, 760576420, 1058537775, 1611151479, 1657655478, 1513337099, 1412088066, 133259820, 1672178320, 1187225268, 1851841892, 751518114, 689080411, 1864862519, 1158622757, 1512839724, 1172072986, 1813160815, 803472151, 1072352519, 1718470390, 420161254, 2067614707, 159945084, 1218305715, 425805724, 1388064247, 15727944, 193746856, 1693862347, 1670321136, 1087408429, 911855168,439179920, 351065485, 1572328760, 724255089, 776494519, 1105773086, 141525793, 257020689, 1966802994, 762097185, 502907825, 1628649589, 1079205414, 316762934, 303953491, 1713829664, 1562660061, 175715709, 141425976, 263001029, 1095674622, 636631028, 127073472, 1175641095, 1121244765, 2100698576, 565255243, 302486843, 1525295218, 61403657, 673321950, 1251157237, 540132037, 792868266, 1200370492, 652677929, 1717207950, 1735077415};
		}
		void SetUp() override {
			m0 = std::make_unique<BaseTokenMock>(BaseToken::Codes::KEYWORD, 0, 0);
		}
		void TearDown() override {}
		std::unique_ptr<BaseTokenMock> m0;
		std::array<std::size_t, 100> TEST_VALUES;
		std::string TEST_STRING;
		std::size_t DEFAULT_TEXT_POSITION;
};

TEST_F(BaseTokenTest, StaticMethodsTest) {
	//	.convertCodesToString()
	EXPECT_EQ("START", BaseToken::convertCodesToString(BaseToken::Codes::START));
	EXPECT_EQ("KEYWORD", BaseToken::convertCodesToString(BaseToken::Codes::KEYWORD));
	EXPECT_EQ("IDENTIFIER", BaseToken::convertCodesToString(BaseToken::Codes::IDENTIFIER));
	EXPECT_EQ("CONSTANTS", BaseToken::convertCodesToString(BaseToken::Codes::CONSTANTS));
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

TEST_F(BaseTokenTest, GettersAndSettersTest) {
	//	Getter methods
	for(std::size_t i: TEST_VALUES) {
		for(std::size_t j: TEST_VALUES) {
			for(std::size_t k = 1; k < BaseToken::Codes::END - 2; ++k) {
				m0 = std::make_unique<BaseTokenMock>(static_cast<BaseToken::Codes>(k), i, j);
				EXPECT_EQ(static_cast<BaseToken::Codes>(k), m0->getCode());
				EXPECT_EQ(i, m0->getLine());
				EXPECT_EQ(j, m0->getColumn());
				EXPECT_TRUE(std::find(BaseToken::POSSIBLE_COLOURS.begin(), BaseToken::POSSIBLE_COLOURS.end(), m0->getColour()) != BaseToken::POSSIBLE_COLOURS.end());
			}
		}
	}
}
