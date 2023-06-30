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
    const std::string result_string = util::trim(string_with_whitespaces);
    ASSERT_EQ(result_string, "text");
}

TEST(TestUtil, TestTrimLeft)
{
    const std::string string_with_whitespaces{"    abcd"};
    const std::string result_string = util::trim(string_with_whitespaces);
    ASSERT_EQ(result_string, "abcd");
}

TEST(TestUtil, TestTrimRight)
{
    const std::string string_with_whitespaces{"abcd  "};
    const std::string result_string = util::trim(string_with_whitespaces);
    ASSERT_EQ(result_string, "abcd");
}

TEST(TestUtil, TestTrimOnlyBlanks)
{
    const std::string string_with_whitespaces{"         "};
    const std::string result_string = util::trim(string_with_whitespaces);
    ASSERT_EQ(result_string, "");
}

TEST(TestUtil, TestTrimNoBlanks)
{
    const std::string some_text_without_blank{"some_text_without_blank"};
    const std::string result_string = util::trim(some_text_without_blank);
    ASSERT_EQ(result_string, some_text_without_blank);
}

TEST(TestUtil, TestTrimInternalBlanks)
{
    const std::string some_text_with_internal_blank{"some text with blank"};
    const std::string result_string = util::trim(some_text_with_internal_blank);
    ASSERT_EQ(result_string, some_text_with_internal_blank);
}

TEST(TestUtil, strToNumericTypeSignedValidMax)
{
    using arg_type = ssize_t;
    arg_type value{std::numeric_limits<arg_type>::max()};
    const std::string str_value {std::to_string(value)};
    ASSERT_NO_THROW(ASSERT_EQ(util::strToNumericType<arg_type>(str_value), value));
}

TEST(TestUtil, strToNumericTypeSignedValidMin)
{
    using arg_type = ssize_t;
    arg_type value{std::numeric_limits<arg_type>::min()};
    const std::string str_value {std::to_string(value)};
    ASSERT_NO_THROW(ASSERT_EQ(util::strToNumericType<arg_type>(str_value), value));
}

TEST(TestUtil, strToNumericTypeSignedInvalid)
{
    using arg_type = ssize_t;
    const std::string str_value {"asdf"};
    ASSERT_THROW(util::strToNumericType<arg_type>(str_value), std::invalid_argument);
}

TEST(TestUtil, strToNumericTypeSignedEmpty)
{
    using arg_type = ssize_t;
    const std::string str_value {};
    ASSERT_NO_THROW(ASSERT_EQ(util::strToNumericType<arg_type>(str_value), 0));
}

TEST(TestUtil, strToNumericTypeUnsignedValidMax)
{
    using arg_type = size_t;
    arg_type value{std::numeric_limits<arg_type>::max()};
    const std::string str_value {std::to_string(value)};
    ASSERT_NO_THROW(ASSERT_EQ(util::strToNumericType<arg_type>(str_value), value));
}

TEST(TestUtil, strToNumericTypeUnsignedValidMin)
{
    using arg_type = size_t;
    arg_type value{std::numeric_limits<arg_type>::min()};
    const std::string str_value {std::to_string(value)};
    ASSERT_NO_THROW(ASSERT_EQ(util::strToNumericType<arg_type>(str_value), value));
}

TEST(TestUtil, strToNumericTypeUnsignedInvalid1)
{
    using arg_type = size_t;
    const std::string str_value {"asdf"};
    ASSERT_THROW(util::strToNumericType<arg_type>(str_value), std::invalid_argument);
}

TEST(TestUtil, strToNumericTypeUnsignedInvalid2)
{
    using arg_type = size_t;
    const std::string str_value {"-1"};
    ASSERT_THROW(util::strToNumericType<arg_type>(str_value), std::invalid_argument);
}

TEST(TestUtil, strToNumericTypeUnsignedEmpty)
{
    using arg_type = size_t;
    const std::string str_value {};
    ASSERT_NO_THROW(ASSERT_EQ(util::strToNumericType<arg_type>(str_value), 0));
}

TEST(TestUtil, strToNumericTypeFloatValidMax)
{
    using arg_type = double;
    arg_type value{std::numeric_limits<arg_type>::max()};
    const std::string str_value {std::to_string(value)};
    ASSERT_NO_THROW(ASSERT_DOUBLE_EQ(util::strToNumericType<arg_type>(str_value), value));
}

TEST(TestUtil, strToNumericTypeFloatValidMin)
{
    using arg_type = double;
    arg_type value{std::numeric_limits<arg_type>::min()};
    const std::string str_value {std::to_string(value)};
    ASSERT_NO_THROW(ASSERT_TRUE(std::abs(util::strToNumericType<arg_type>(str_value) - value) < std::numeric_limits<arg_type>::epsilon()));
}

TEST(TestUtil, strToNumericTypeFloatInvalid1)
{
    using arg_type = double;
    const std::string str_value {"asdf"};
    ASSERT_THROW(util::strToNumericType<arg_type>(str_value), std::invalid_argument);
}

TEST(TestUtil, strToNumericTypeFloatEmpty)
{
    using arg_type = double;
    const std::string str_value {};
    ASSERT_NO_THROW(ASSERT_EQ(util::strToNumericType<arg_type>(str_value), 0));
}

TEST(TestUtil, splitStringByDelimiterEmpty)
{
  std::string list{};
  std::vector<std::string> token{};
  ASSERT_NO_THROW(util::splitStringByDelimiter(list, ' ', token));

  ASSERT_TRUE(token.empty());
}

TEST(TestUtil, splitStringByDelimiterValid)
{
  std::string list{"This is some string"};
  std::vector<std::string> token{};
  ASSERT_NO_THROW(util::splitStringByDelimiter(list, ' ', token));

  ASSERT_EQ(token.size(), 4);
  ASSERT_EQ(token.at(0), "This");
  ASSERT_EQ(token.at(1), "is");
  ASSERT_EQ(token.at(2), "some");
  ASSERT_EQ(token.at(3), "string");
}

TEST(TestUtil, splitStringByDelimiterValidMultipleBlanks)
{
  std::string list{"   This is               some string   "};
  std::vector<std::string> token{};
  ASSERT_NO_THROW(util::splitStringByDelimiter(list, ' ', token));

  ASSERT_EQ(token.size(), 4);
  ASSERT_EQ(token.at(0), "This");
  ASSERT_EQ(token.at(1), "is");
  ASSERT_EQ(token.at(2), "some");
  ASSERT_EQ(token.at(3), "string");
}

TEST(TestUtil, splitStringByDelimiterValidSemicolon)
{
  std::string list{"   This; is  ;             some ; string ;  "};
  std::vector<std::string> token{};
  ASSERT_NO_THROW(util::splitStringByDelimiter(list, ';', token));

  ASSERT_EQ(token.size(), 4);
  ASSERT_EQ(token.at(0), "This");
  ASSERT_EQ(token.at(1), "is");
  ASSERT_EQ(token.at(2), "some");
  ASSERT_EQ(token.at(3), "string");
}

TEST(TestUtil, splitStringByDelimiterDelimiterOnly)
{
  std::string list{";;;;;; ;;;;"};
  std::vector<std::string> token{};
  ASSERT_NO_THROW(util::splitStringByDelimiter(list, ';', token));

  ASSERT_TRUE(token.empty());
}


TEST(TestUtil, createStringFromCharPtrArrayEmpty)
{
  const char* string_array[1]{};
  ASSERT_NO_THROW(ASSERT_EQ(util::createStringFromCharPtrArray(0, string_array), ""));
}

TEST(TestUtil, createStringFromCharPtrArray)
{
  const char* string_array[]{"Some", "String", "Which", "Should", "Be", "Connected"};
  ASSERT_NO_THROW(ASSERT_EQ(util::createStringFromCharPtrArray(6, string_array), "Some String Which Should Be Connected "));
}

TEST(TestUtil, createStringFromCharPtrArrayEmptyStrings)
{
  const char* string_array[]{"", "", "", "", "", ""};
  ASSERT_NO_THROW(ASSERT_EQ(util::createStringFromCharPtrArray(6, string_array), "      "));
}