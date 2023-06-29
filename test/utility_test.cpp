//
// Created by david on 29/06/23.
//
#include "gtest/gtest.h"
#include "../inc/utility.hpp"

class TestUtil : public ::testing::Test
{
};

TEST(TestUtil, TestTrimBothSides)
{
    const std::string string_with_whitespaces{"    text   "};
    const std::string result_string = Util::trim(string_with_whitespaces);
    ASSERT_EQ(result_string, "text");
}

TEST(TestUtil, TestTrimLeft)
{
    const std::string string_with_whitespaces{"    abcd"};
    const std::string result_string = Util::trim(string_with_whitespaces);
    ASSERT_EQ(result_string, "abcd");
}

TEST(TestUtil, TestTrimRight)
{
    const std::string string_with_whitespaces{"abcd  "};
    const std::string result_string = Util::trim(string_with_whitespaces);
    ASSERT_EQ(result_string, "abcd");
}

TEST(TestUtil, TestTrimOnlyBlanks)
{
    const std::string string_with_whitespaces{"         "};
    const std::string result_string = Util::trim(string_with_whitespaces);
    ASSERT_EQ(result_string, "");
}

TEST(TestUtil, TestTrimNoBlanks)
{
    const std::string some_text_without_blank{"some_text_without_blank"};
    const std::string result_string = Util::trim(some_text_without_blank);
    ASSERT_EQ(result_string, some_text_without_blank);
}

TEST(TestUtil, TestTrimInternalBlanks)
{
    const std::string some_text_with_internal_blank{"some text with blank"};
    const std::string result_string = Util::trim(some_text_with_internal_blank);
    ASSERT_EQ(result_string, some_text_with_internal_blank);
}