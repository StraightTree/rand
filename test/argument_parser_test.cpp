#include "gtest/gtest.h"
#include "../inc/argument_parser.hpp"

class TestArgumentParser : public ::testing::Test
{
protected:
  static std::string buildArgumentString(const std::vector<std::pair<char, std::string>>& args)
  {
    std::stringstream ss{};
    for (const auto& arg : args)
    {
      ss << '-' << arg.first << ' ' << arg.second << ' ';
    }
    return ss.str();
  }
};


TEST(TestArgumentParser, getSplitUpArguments)
{
  std::string terminal_args{"-n 32 -l 20 -d N --verbose"};
  std::vector<Argument> supported_arguments{};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<std::pair<std::string, std::string>> token{};
  ASSERT_NO_THROW(argument_parser.getSplitUpArguments(token));
  ASSERT_EQ(token.size(), 4);
  ASSERT_EQ(token.at(0).first, "n");
  ASSERT_EQ(token.at(0).second, "32");
  ASSERT_EQ(token.at(1).first, "l");
  ASSERT_EQ(token.at(1).second, "20");
  ASSERT_EQ(token.at(2).first, "d");
  ASSERT_EQ(token.at(2).second, "N");
  ASSERT_EQ(token.at(3).first, "verbose");
}


TEST(TestArgumentParser, getSplitUpArgumentsEmpty)
{
  std::string terminal_args{};
  std::vector<Argument> supported_arguments{};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<std::pair<std::string, std::string>> token{};
  ASSERT_NO_THROW(argument_parser.getSplitUpArguments(token));
  ASSERT_EQ(token.size(), 0);
}

TEST(TestArgumentParser, getSplitUpArgumentsEmptyString)
{
  std::string terminal_args{"            "};
  std::vector<Argument> supported_arguments{};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<std::pair<std::string, std::string>> token{};
  ASSERT_NO_THROW(argument_parser.getSplitUpArguments(token));
  ASSERT_EQ(token.size(), 0);
}


TEST(TestArgumentParser, getSplitUpArgumentsNonParseableString)
{
  std::string terminal_args{"HelloWorld"};
  std::vector<Argument> supported_arguments{};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<std::pair<std::string, std::string>> token{};
  ASSERT_NO_THROW(argument_parser.getSplitUpArguments(token));
  ASSERT_EQ(token.size(), 1);
  ASSERT_EQ(token.front().first, terminal_args);
}

TEST(TestArgumentParser, getSplitUpArgumentsNonParseableString2)
{
  std::string terminal_args{"---"};
  std::vector<Argument> supported_arguments{};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<std::pair<std::string, std::string>> token{};
  ASSERT_NO_THROW(argument_parser.getSplitUpArguments(token));
  ASSERT_EQ(token.size(), 0);
}

TEST(TestArgumentParser, getSplitUpArgumentsNonParseableString3)
{
  std::string terminal_args{"#*78387"};
  std::vector<Argument> supported_arguments{};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<std::pair<std::string, std::string>> token{};
  ASSERT_NO_THROW(argument_parser.getSplitUpArguments(token));
  ASSERT_EQ(token.size(), 1);
  ASSERT_EQ(token.front().first, terminal_args);
}

TEST(TestArgumentParser, getSplitUpArgumentsNonParseableString4)
{
  std::string terminal_args{"   -   -    -"};
  std::vector<Argument> supported_arguments{};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<std::pair<std::string, std::string>> token{};
  ASSERT_NO_THROW(argument_parser.getSplitUpArguments(token));
  ASSERT_EQ(token.size(), 0);
}

class TestParseArgument : public TestArgumentParser
{};

TEST(TestParseArgument, parseArgumentString)
{
  using arg_type = std::string;
  arg_type value{};
  Argument arg{"","", "", value};
  const arg_type argument{"SomeArgumentInMixedCase"};
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, argument));

  ASSERT_EQ(value, *reinterpret_cast<arg_type*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentEmptyString)
{
  using arg_type = std::string;
  arg_type value{};
  Argument arg{"","", "", value};
  const arg_type argument{};
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, argument));

  ASSERT_EQ(value, *reinterpret_cast<arg_type*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentAlphaNumericString)
{
  using arg_type = std::string;
  arg_type value{};
  Argument arg{"","", "", value};
  const arg_type argument{"ABCDefgh1234"};
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, argument));

  ASSERT_EQ(value, *reinterpret_cast<arg_type*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentFloat)
{
  using arg_type = double;
  arg_type value{};
  Argument arg{"","", "", value};
  const arg_type argument{3.14159};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<arg_type*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentFloatMaxValue)
{
  using arg_type = double;
  arg_type value{};
  Argument arg{"","", "", value};
  const arg_type argument{std::numeric_limits<arg_type>::max()};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_DOUBLE_EQ(argument, *reinterpret_cast<arg_type*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentFloatMinValue)
{
  using arg_type = double;
  arg_type value{};
  Argument arg{"","", "", value};
  const arg_type argument{std::numeric_limits<arg_type>::min()};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_TRUE(std::abs(argument-*reinterpret_cast<arg_type*>(arg.getArgument())) < std::numeric_limits<arg_type>::epsilon());
}

TEST(TestParseArgument, parseArgumentFloatInvalidValue)
{
  using arg_type = double;
  arg_type value{};
  Argument arg{"","", "", value};
  std::string str_argument = "abcd";
  ASSERT_THROW(ArgumentParser::parseArgument(arg, str_argument), std::invalid_argument);

  ASSERT_DOUBLE_EQ(value, 0.0);
}

TEST(TestParseArgument, parseArgumentSignedIntNegative)
{
  using arg_type = ssize_t;
  arg_type value{};
  Argument arg{"","", "", value};
  const arg_type argument{-34324};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<arg_type*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentSignedIntPositve)
{
  using arg_type = ssize_t;
  arg_type value{};
  Argument arg{"","", "", value};
  const arg_type argument{28938998};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<arg_type*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentSignedIntMaxValue)
{
  using arg_type = ssize_t;
  arg_type value{};
  Argument arg{"","", "", value};
  const arg_type argument{std::numeric_limits<arg_type>::max()};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<arg_type*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentSignedIntMinValue)
{
  using arg_type = ssize_t;
  arg_type value{};
  Argument arg{"","", "", value};
  const arg_type argument{std::numeric_limits<arg_type>::min()};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<arg_type*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentSignedInvalidValue1)
{
  using arg_type = ssize_t;
  arg_type value{};
  Argument arg{"","", "", value};
  std::string str_argument = "abcd";
  ASSERT_THROW(ArgumentParser::parseArgument(arg, str_argument), std::invalid_argument);

  ASSERT_EQ(value, 0);
}

TEST(TestParseArgument, parseArgumentSignedInvalidValue2)
{
  using arg_type = ssize_t;
  arg_type value{};
  Argument arg{"","", "", value};
  std::string str_argument = "2.7";
  ASSERT_THROW(ArgumentParser::parseArgument(arg, str_argument), std::invalid_argument);

  ASSERT_EQ(value, 0);
}

TEST(TestParseArgument, parseArgumentUnsignedInt)
{
  using arg_type = size_t;
  arg_type value{};
  Argument arg{"","", "", value};
  const arg_type argument{34324};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<arg_type*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentUnsignedIntMaxValue)
{
  using arg_type = ssize_t;
  arg_type value{};
  Argument arg{"","", "", value};
  const arg_type argument{std::numeric_limits<arg_type>::max()};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<arg_type*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentUnsignedIntMinValue)
{
  using arg_type = ssize_t;
  arg_type value{};
  Argument arg{"","", "", value};
  const arg_type argument{std::numeric_limits<arg_type>::min()};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<arg_type*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentUnsignedInvalidValue1)
{
  using arg_type = ssize_t;
  arg_type value{};
  Argument arg{"","", "", value};
  std::string str_argument = "abcd";
  ASSERT_THROW(ArgumentParser::parseArgument(arg, str_argument), std::invalid_argument);

  ASSERT_EQ(value, 0);
}

TEST(TestParseArgument, parseArgumentUnsignedInvalidValue2)
{
  using arg_type = ssize_t;
  arg_type value{};
  Argument arg{"","", "", value};
  std::string str_argument = "2.7";
  ASSERT_THROW(ArgumentParser::parseArgument(arg, str_argument), std::invalid_argument);

  ASSERT_EQ(value, 0);
}

TEST(TestParseArgument, parseArgumentUnsignedInvalidValue3)
{
  using arg_type = ssize_t;
  arg_type value{};
  Argument arg{"","", "", value};
  std::string str_argument = "-435";
  ASSERT_THROW(ArgumentParser::parseArgument(arg, str_argument), std::invalid_argument);

  ASSERT_EQ(value, 0);
}

TEST(TestParseArgument, parseArgumentBoolNoArg)
{
  using arg_type = bool;
  arg_type value{};
  Argument arg{"","", "", value};
  const arg_type argument{};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<arg_type*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentBoolArg)
{
  using arg_type = bool;
  arg_type value{};
  Argument arg{"","", "", value};
  const arg_type argument{true};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<arg_type*>(arg.getArgument()));
}

TEST(TestParseArgument, getUserArgumentsSimple)
{
  ssize_t numbers{};
  Argument arg1{"n", "numbers", "", numbers};

  size_t count{};
  Argument arg2{"c", "count", "", count};

  std::string file{};
  Argument arg3{"f", "file", "", file};

  std::vector<Argument> supported_arguments{arg1, arg2, arg3};

  std::string terminal_args{"-n 43"};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<Argument> provided_arguments{};
  ASSERT_NO_THROW(provided_arguments = argument_parser.getUserArguments());
  ASSERT_EQ(provided_arguments.size(), 1);
  ASSERT_EQ(provided_arguments.front(), arg1);
}

TEST(TestParseArgument, getUserArguments)
{
  ssize_t numbers{};
  Argument arg1{"n", "numbers", "", numbers};

  size_t count{};
  Argument arg2{"c", "count", "", count};

  std::string file{};
  Argument arg3{"f", "file", "", file};

  std::vector<Argument> supported_arguments{arg1, arg2, arg3};

  std::string terminal_args{"-n 43 -f some_file.txt"};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<Argument> provided_arguments{};
  ASSERT_NO_THROW(provided_arguments = argument_parser.getUserArguments());
  ASSERT_EQ(provided_arguments.size(), 2);
  ASSERT_EQ(provided_arguments.at(0), arg1);
  ASSERT_EQ(provided_arguments.at(1), arg3);
}

TEST(TestParseArgument, getUserArgumentsVerbose)
{
  ssize_t numbers{};
  Argument arg1{"n", "numbers", "", numbers};

  size_t count{};
  Argument arg2{"c", "count", "", count};

  std::string file{};
  Argument arg3{"f", "file", "", file};

  std::vector<Argument> supported_arguments{arg1, arg2, arg3};

  std::string terminal_args{"-n 43 -file some_file.txt"};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<Argument> provided_arguments{};
  ASSERT_NO_THROW(provided_arguments = argument_parser.getUserArguments());
  ASSERT_EQ(provided_arguments.size(), 2);
  ASSERT_EQ(provided_arguments.at(0), arg1);
  ASSERT_EQ(provided_arguments.at(1), arg3);
}

TEST(TestParseArgument, getUserArgumentsInvalidArg)
{
  ssize_t numbers{};
  Argument arg1{"n", "numbers", "", numbers};

  size_t count{};
  Argument arg2{"c", "count", "", count};

  std::string file{};
  Argument arg3{"f", "file", "", file};

  std::vector<Argument> supported_arguments{arg1, arg2, arg3};

  std::string terminal_args{"-n 43 -file some_file.txt"};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<Argument> provided_arguments{};
  ASSERT_NO_THROW(provided_arguments = argument_parser.getUserArguments());
  ASSERT_EQ(provided_arguments.size(), 2);
  ASSERT_EQ(provided_arguments.at(0), arg1);
  ASSERT_EQ(provided_arguments.at(1), arg3);
}