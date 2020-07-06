#include "pch.h"
//#include"../2/2.cpp"

TEST(IsLeapYear, YearThatNotMultipleOfFour) {
    EXPECT_EQ(IsLeapYear(1933), false);
}

TEST(IsLeapYear, YearThatMultipleOfFour) {
	EXPECT_EQ(IsLeapYear(4), true);
}

TEST(IsLeapYear, YearThatMultipleOfHundredButNotMultipleOfFourHundred) {
	EXPECT_EQ(IsLeapYear(1900), false);
}

TEST(IsLeapYear, YearThatNotMultipleOfHundredAndMultipleOfFourHundred) {
	EXPECT_EQ(IsLeapYear(2000), true);
}

TEST(IsLeapYear, YearIsZero) {
	EXPECT_EQ(IsLeapYear(0), true);
}

TEST(IsLeapYear, YearThatNegative) {
	EXPECT_THROW(IsLeapYear(-100), std::out_of_range);
}
