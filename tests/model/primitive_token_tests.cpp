//
// Created by Dominik on 11.04.2023.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../includes/syntax_colorizer_lib/headers/model/token/primitive_token.h"

class PrimitiveTokenMock: public PrimitiveToken {
	public:
		MOCK_METHOD(std::string, print, (), (const override));
		MOCK_METHOD(std::string, printHTML, (), (const override));
};

TEST(MyClassTest, TestMyMethod) {
	PrimitiveTokenMock mock;
	EXPECT_CALL(mock, print()).WillOnce(testing::Return("TEST"));
	EXPECT_EQ(mock.print(), "TEST");
	EXPECT_CALL(mock, printHTML()).WillOnce(testing::Return("TEST"));
	EXPECT_EQ(mock.printHTML(), "TEST");
}
