//
// Created by Dominik on 15.03.2023.
//


#include <gtest/gtest.h>

#include "../../includes/internal/headers/model/token/token.h"

class TokenTest: public ::testing::Test {
	protected:
		TokenTest() {
			token_string = nullptr;
			token_char = nullptr;
			token_int = nullptr;
			token_double = nullptr;
			TEST_VALUE = 0;
			TEST_STRING = {"Lorem", "ipsum", "dolor", "sit", "amet,", "consectetur", "adipiscing", "elit.", "Donec", "semper", "finibus", "augue,", "ac", "convallis", "nibh", "placerat", "id.", "In", "hac", "habitasse", "platea", "dictumst.", "Integer", "venenatis", "luctus", "tellus", "mollis", "vehicula.", "Curabitur", "tempor", "arcu", "id", "neque", "eleifend", "cursus.", "Aenean", "sagittis", "eget", "orci", "nec", "cursus.", "Sed", "dictum", "diam", "id", "nisl", "luctus,", "ut", "aliquam", "lorem", "commodo.", "Vestibulum", "ante", "ipsum", "primis", "in", "faucibus", "orci", "luctus", "et", "ultrices", "posuere", "cubilia", "curae;", "Vestibulum", "et", "iaculis", "ipsum,", "ut", "faucibus", "risus.", "Proin", "a", "velit", "sit", "amet", "urna", "vulputate", "imperdiet", "sit", "amet", "non", "est.", "Suspendisse", "urna", "sem,", "placerat", "eu", "nisi", "a,", "egestas", "convallis", "nisl.", "Nulla", "facilisi.", "Sed", "ac", "arcu", "turpis.", "Suspendisse."};
			TEST_DOUBLES = {955.416, 847.998, -668.86, -978.628, 76.2547, 515.118, 355.661, -980.381, -257.949, 338.658, -271.724, -601.706, 180.343, 463.182, 950.981, -35.9095, 437.875, 103.853, -545.141, 710.07, -840.86, -709.797, -534.678, -525.524, 834.488, 760.039, -506.147, 195.712, 822.076, 431.888, -745.961, -256.917, 94.075, -536.518, -673.027, 161.263, 443.889, 276.246, -509.634, -365.599, 355.022, -997.922, -559.461, -504.234, -731.607, -997.947, -340.571, -443.846, 250.391, -551.13, -389.125, 177.948, 118.639, 509.646, 450.3, -892.816, -190.264, -638.204, -175.156, 114.357, -136.564, -171.537, 640.94, -554.805, 905.997, -115.528, 137.813, 492.944, -700.219, 330.998, -696.563, -820.232, -849.336, 187.731, 315.291, 708.57, -47.091, -533.574, 242.357, -562.407, -479.28, -178.091, 852.882, 259.252, 292.099, -396.761, 492.51, -569.489, -359.196,299.151, 783.028, -756.107, -831.244, 348.02, 303.689, 320.201, -16.9675, 700.465, 270.836, 204.265};
			TEST_INTS = {1049544336, 1074442503, 687392545, 1955552446, 1168883164, 415136718, 1398007497, 17107835, 609012671, 271730254, 841420711, 247809451, 1090393496, 562900903, 642651866, 1736305822, 1189710974, 1433360269, 1366822096, 176765774, 1692468001, 1437163006, 1957229471, 1300716634, 608641288, 612721961, 396322064, 1489715469, 880426812, 2044843973, 760576420, 1058537775, 1611151479, 1657655478, 1513337099, 1412088066, 133259820, 1672178320, 1187225268, 1851841892, 751518114, 689080411, 1864862519, 1158622757, 1512839724, 1172072986, 1813160815, 803472151, 1072352519, 1718470390, 420161254, 2067614707, 159945084, 1218305715, 425805724, 1388064247, 15727944, 193746856, 1693862347, 1670321136, 1087408429, 911855168,439179920, 351065485, 1572328760, 724255089, 776494519, 1105773086, 141525793, 257020689, 1966802994, 762097185, 502907825, 1628649589, 1079205414, 316762934, 303953491, 1713829664, 1562660061, 175715709, 141425976, 263001029, 1095674622, 636631028, 127073472, 1175641095, 1121244765, 2100698576, 565255243, 302486843, 1525295218, 61403657, 673321950, 1251157237, 540132037, 792868266, 1200370492, 652677929, 1717207950, 1735077415};
		}
		void SetUp() override {
		
		}
		void TearDown() override {
		
		}
		std::unique_ptr<Token<std::string>> token_string;
		std::unique_ptr<Token<char>> token_char;
		std::unique_ptr<Token<int>> token_int;
		std::unique_ptr<Token<double>> token_double;
		std::size_t TEST_VALUE;
		std::array<std::string, 100> TEST_STRING;
		std::array<int, 100> TEST_INTS;
		std::array<double, 100> TEST_DOUBLES;
};

TEST_F(TokenTest, MainConstructorTest) {
	for (const std::string& str: TEST_STRING) {
		token_string = std::make_unique<Token<std::string>>(BaseToken::Codes::KEYWORD, str, TEST_VALUE, TEST_VALUE);
		EXPECT_EQ(BaseToken::Codes::KEYWORD, token_string->getCode());
		EXPECT_EQ(str, token_string->getValue());
		EXPECT_EQ(TEST_VALUE, token_string->getLine());
		EXPECT_EQ(TEST_VALUE, token_string->getColumn());
	}
	for (const std::vector<char>& character_set: BaseToken::INPUT_ALPHABET) {
		for (const char in: character_set) {
			token_char = std::make_unique<Token<char>>(BaseToken::Codes::OPERATOR, in, TEST_VALUE, TEST_VALUE);
			EXPECT_EQ(BaseToken::Codes::OPERATOR, token_char->getCode());
			EXPECT_EQ(in, token_char->getValue());
			EXPECT_EQ(TEST_VALUE, token_char->getLine());
			EXPECT_EQ(TEST_VALUE, token_char->getColumn());
		}
	}
	for (const double& value: TEST_DOUBLES) {
		token_double = std::make_unique<Token<double>>(BaseToken::Codes::KEYWORD, value, TEST_VALUE, TEST_VALUE);
		EXPECT_EQ(BaseToken::Codes::KEYWORD, token_double->getCode());
		EXPECT_DOUBLE_EQ(value, token_double->getValue());
		EXPECT_EQ(TEST_VALUE, token_double->getLine());
		EXPECT_EQ(TEST_VALUE, token_double->getColumn());
	}
	for (const int& value: TEST_INTS) {
		token_int = std::make_unique<Token<int>>(BaseToken::Codes::KEYWORD, value, TEST_VALUE, TEST_VALUE);
		EXPECT_EQ(BaseToken::Codes::KEYWORD, token_int->getCode());
		EXPECT_DOUBLE_EQ(value, token_int->getValue());
		EXPECT_EQ(TEST_VALUE, token_int->getLine());
		EXPECT_EQ(TEST_VALUE, token_int->getColumn());
	}
}
/*
 * @todo	Finish print test
 */
TEST_F(TokenTest, printTest) {

}

TEST_F(TokenTest, ShiftTest) {
	//	valueShift(...), printShift(...) methods
	for (const std::string& str: TEST_STRING) {
		token_string = std::make_unique<Token<std::string>>(BaseToken::Codes::KEYWORD, str, TEST_VALUE, TEST_VALUE);
		EXPECT_EQ(str.size(), token_string->valueShift());
		EXPECT_EQ(token_string->print().size() - token_string->valueShift(), token_string->printShift());
		EXPECT_EQ(token_string->printHTML().size() - token_string->valueShift(), token_string->printHTMLShift());
	}
	for (const std::vector<char>& character_set: BaseToken::INPUT_ALPHABET) {
		for (const char in: character_set) {
			token_char = std::make_unique<Token<char>>(BaseToken::Codes::OPERATOR, in, TEST_VALUE, TEST_VALUE);
			EXPECT_EQ(1, token_char->valueShift());
			EXPECT_EQ(token_char->print().size() - token_char->valueShift(), token_char->printShift());
			EXPECT_EQ(token_char->printHTML().size() - token_char->valueShift(), token_char->printHTMLShift());
		}
	}
	for (const double& value: TEST_DOUBLES) {
		token_double = std::make_unique<Token<double>>(BaseToken::Codes::KEYWORD, value, TEST_VALUE, TEST_VALUE);
		EXPECT_EQ(std::to_string(value).size(), token_double->valueShift());
		EXPECT_EQ(token_double->print().size() - token_double->valueShift(), token_double->printShift());
		EXPECT_EQ(token_double->printHTML().size() - token_double->valueShift(), token_double->printHTMLShift());
	}
	for (const int& value: TEST_INTS) {
		token_int = std::make_unique<Token<int>>(BaseToken::Codes::KEYWORD, value, TEST_VALUE, TEST_VALUE);
		EXPECT_EQ(std::to_string(value).size(), token_int->valueShift());
		EXPECT_EQ(token_int->print().size() - token_int->valueShift(), token_int->printShift());
		EXPECT_EQ(token_int->printHTML().size() - token_int->valueShift(), token_int->printHTMLShift());
	}
}