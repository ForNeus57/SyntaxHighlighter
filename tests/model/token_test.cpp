//
// Created by Dominik on 15.03.2023.
//


#include <gtest/gtest.h>

#include <fstream>
#include <algorithm>

#include "../../includes/internal/headers/model/token/token.h"

std::vector<std::string> getTextTestDataFromFile(const std::string& file_name) {
	std::ifstream file(file_name, std::ios::in);
	file.unsetf(std::ios_base::skipws);
	
	//	Count how many lines given file have
	long long line_count = std::count(std::istream_iterator<char>(file),std::istream_iterator<char>(),'\n');
	
	std::vector<std::string> output(static_cast<std::size_t>(line_count));
	if (file.is_open())
		for (std::size_t i = 0; std::getline(file, output[i]); ++i);
	else
		throw std::runtime_error("Unable to input text file:" + file_name);
	
	file.close();
	
	return output;
}

template<typename T>
std::vector<T> getTestDataFromFile(const std::string& file_name) {
	int num_values;
	
	// Read the number of values from the binary file
	std::ifstream file(file_name, std::ios::binary);
	if (file.is_open())
		file.read(reinterpret_cast<char*>(&num_values), sizeof(int));
	else
		throw std::runtime_error("Unable to input text file:" + file_name);
	
	// Read the values from the binary file
	std::vector<T> values(static_cast<std::size_t>(num_values));
	file.read(reinterpret_cast<char*>(values.data()), unsigned(num_values) * sizeof(T));
	
	file.close();
	
	return values;
}

template std::vector<double> getTestDataFromFile<double>(const std::string&);
template std::vector<int> getTestDataFromFile<int>(const std::string&);

class TokenTest: public ::testing::Test {
	protected:
		TokenTest(): token_string(nullptr), token_int(nullptr), token_double(nullptr), token_char(nullptr), TEST_STRING(), TEST_INTS(), TEST_DOUBLES(), TEST_VALUE(0) {
			TEST_STRING = getTextTestDataFromFile(R"(..\..\tests\input\test_data\random_strings_values.txt)");
			TEST_DOUBLES = getTestDataFromFile<double>(R"(..\..\tests\input\test_data\random_double_values.bin)");
			TEST_INTS = getTestDataFromFile<int>(R"(..\..\tests\input\test_data\random_int_values.bin)");
		}
		void SetUp() override {
		
		}
		void TearDown() override {
		
		}
	protected:
		std::unique_ptr<Token<std::string>> token_string;
		std::unique_ptr<Token<int>> token_int;
		std::unique_ptr<Token<double>> token_double;
		std::unique_ptr<Token<char>> token_char;
	protected:
		std::vector<std::string> TEST_STRING;
		std::vector<int> TEST_INTS;
		std::vector<double> TEST_DOUBLES;
		std::size_t TEST_VALUE;
};


TEST_F(TokenTest, MainConstructorAndMemoryLeakTest) {
	for (const std::string& str: TEST_STRING) {
		for (BaseToken::Codes code : BaseToken::CODES_TYPES) {
			if (BaseToken::isValidCode(code)) {
				token_string = std::make_unique<Token<std::string>>(code, str, TEST_VALUE, TEST_VALUE);
				ASSERT_NE(token_string.get(), nullptr);
				EXPECT_EQ(code, token_string->getCode());
				EXPECT_EQ(str, token_string->getValue());
				EXPECT_EQ(TEST_VALUE, token_string->getLine());
				EXPECT_EQ(TEST_VALUE, token_string->getColumn());
				token_string.reset();
				ASSERT_EQ(token_string.get(), nullptr);
			}
		}
	}
	for (const std::vector<char>& character_set: BaseToken::INPUT_ALPHABET) {
		for (const char in: character_set) {
			for (BaseToken::Codes code : BaseToken::CODES_TYPES) {
				if (BaseToken::isValidCode(code)) {
					token_char = std::make_unique<Token<char>>(code, in, TEST_VALUE, TEST_VALUE);
					ASSERT_NE(token_char.get(), nullptr);
					EXPECT_EQ(code, token_char->getCode());
					EXPECT_EQ(in, token_char->getValue());
					EXPECT_EQ(TEST_VALUE, token_char->getLine());
					EXPECT_EQ(TEST_VALUE, token_char->getColumn());
					token_char.reset();
					ASSERT_EQ(token_char.get(), nullptr);
				}
			}
		}
	}
	for (const double& value: TEST_DOUBLES) {
		for (BaseToken::Codes code : BaseToken::CODES_TYPES) {
			if (BaseToken::isValidCode(code)) {
				token_double = std::make_unique<Token<double>>(code, value, TEST_VALUE, TEST_VALUE);
				ASSERT_NE(token_double.get(), nullptr);
				EXPECT_EQ(code, token_double->getCode());
				EXPECT_DOUBLE_EQ(value, token_double->getValue());
				EXPECT_EQ(TEST_VALUE, token_double->getLine());
				EXPECT_EQ(TEST_VALUE, token_double->getColumn());
				token_double.reset();
				ASSERT_EQ(token_double.get(), nullptr);
			}
		}
	}
	for (const int& value: TEST_INTS) {
		for (BaseToken::Codes code : BaseToken::CODES_TYPES) {
			if (BaseToken::isValidCode(code)) {
				token_int = std::make_unique<Token<int>>(code, value, TEST_VALUE, TEST_VALUE);
				ASSERT_NE(token_int.get(), nullptr);
				EXPECT_EQ(code, token_int->getCode());
				EXPECT_DOUBLE_EQ(value, token_int->getValue());
				EXPECT_EQ(TEST_VALUE, token_int->getLine());
				EXPECT_EQ(TEST_VALUE, token_int->getColumn());
				token_int.reset();
				ASSERT_EQ(token_int.get(), nullptr);
			}
		}
	}
}

TEST_F(TokenTest, ShiftTest) {
	//	valueShift(...), printShift(...) methods
	for (const std::string& str: TEST_STRING) {
		for (BaseToken::Codes code : BaseToken::CODES_TYPES) {
			if (BaseToken::isValidCode(code)) {
				token_string = std::make_unique<Token<std::string>>(code, str, TEST_VALUE, TEST_VALUE);
				EXPECT_EQ(str.size(), token_string->valueShift());
				EXPECT_EQ(token_string->print().size() - token_string->valueShift(), token_string->printShift());
				EXPECT_EQ(token_string->printHTML().size() - token_string->valueShift(), token_string->printHTMLShift());
			}
		}
	}
	for (const std::vector<char>& character_set: BaseToken::INPUT_ALPHABET) {
		for (const char in: character_set) {
			for (BaseToken::Codes code : BaseToken::CODES_TYPES) {
				if (BaseToken::isValidCode(code)) {
					token_char = std::make_unique<Token<char>>(code, in, TEST_VALUE, TEST_VALUE);
					EXPECT_EQ(1, token_char->valueShift());
					EXPECT_EQ(token_char->print().size() - token_char->valueShift(), token_char->printShift());
					EXPECT_EQ(token_char->printHTML().size() - token_char->valueShift(), token_char->printHTMLShift());
				}
			}
		}
	}
	for (const double& value: TEST_DOUBLES) {
		for (BaseToken::Codes code : BaseToken::CODES_TYPES) {
			if (BaseToken::isValidCode(code)) {
				token_double = std::make_unique<Token<double>>(code, value, TEST_VALUE, TEST_VALUE);
				EXPECT_EQ(std::to_string(value).size(), token_double->valueShift());
				EXPECT_EQ(token_double->print().size() - token_double->valueShift(), token_double->printShift());
				EXPECT_EQ(token_double->printHTML().size() - token_double->valueShift(), token_double->printHTMLShift());
			}
		}
	}
	for (const int& value: TEST_INTS) {
		for (BaseToken::Codes code : BaseToken::CODES_TYPES) {
			if (BaseToken::isValidCode(code)) {
				token_int = std::make_unique<Token<int>>(code, value, TEST_VALUE, TEST_VALUE);
				EXPECT_EQ(std::to_string(value).size(), token_int->valueShift());
				EXPECT_EQ(token_int->print().size() - token_int->valueShift(), token_int->printShift());
				EXPECT_EQ(token_int->printHTML().size() - token_int->valueShift(), token_int->printHTMLShift());
			}
		}
	}
}
