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
{

};

static std::string toString(const std::vector<std::string>& container, const char delimiter)
{
  std::stringstream ss{};
  const auto size{container.size()};
  auto it_counter = 0;
  for (const auto& value : container)
  {
    ss << value << ((it_counter == size) ? ' ' : delimiter);
    it_counter++;
  }
}

TEST(TestParseArgument, parseArgumentStringListEmpty)
{

  Argument::DataType::StringListType value{};
  Argument arg{"","", "", value};
  const std::string argument = toString(value, ' ');
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, argument));

  ASSERT_EQ(value, *reinterpret_cast<Argument::DataType::StringListType*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentStringList)
{
  Argument::DataType::StringListType value{"This", "is", "some", "list", "which", "should", "be", "parsed"};
  Argument arg{"","", "", value};
  const std::string argument = toString(value, ',');
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, argument));

  ASSERT_EQ(value, *reinterpret_cast<Argument::DataType::StringListType*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentStringListNumericContent)
{
  Argument::DataType::StringListType value{"32", "is", "43", "list", "54", "23", "be", "4"};
  Argument arg{"","", "", value};
  const std::string argument = toString(value, ',');
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, argument));

  ASSERT_EQ(value, *reinterpret_cast<Argument::DataType::StringListType*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentString)
{
  Argument::DataType::StringType value{};
  Argument arg{"","", "", value};
  const Argument::DataType::StringType argument{"SomeArgumentInMixedCase"};
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, argument));

  ASSERT_EQ(value, *reinterpret_cast<Argument::DataType::StringType*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentEmptyString)
{
  Argument::DataType::StringType value{};
  Argument arg{"","", "", value};
  const Argument::DataType::StringType argument{};
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, argument));

  ASSERT_EQ(value, *reinterpret_cast<Argument::DataType::StringType*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentAlphaNumericString)
{
  Argument::DataType::StringType value{};
  Argument arg{"","", "", value};
  const Argument::DataType::StringType argument{"ABCDefgh1234"};
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, argument));

  ASSERT_EQ(value, *reinterpret_cast<Argument::DataType::StringType*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentFloat)
{
  Argument::DataType::FloatType value{};
  Argument arg{"","", "", value};
  const Argument::DataType::FloatType argument{3.14159};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<Argument::DataType::FloatType*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentFloatMaxValue)
{
  Argument::DataType::FloatType value{};
  Argument arg{"","", "", value};
  const Argument::DataType::FloatType argument{std::numeric_limits<Argument::DataType::FloatType>::max()};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_DOUBLE_EQ(argument, *reinterpret_cast<Argument::DataType::FloatType*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentFloatMinValue)
{
  Argument::DataType::FloatType value{};
  Argument arg{"","", "", value};
  const Argument::DataType::FloatType argument{std::numeric_limits<Argument::DataType::FloatType>::min()};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_TRUE(std::abs(argument-*reinterpret_cast<Argument::DataType::FloatType*>(arg.getArgument())) < std::numeric_limits<Argument::DataType::FloatType>::epsilon());
}

TEST(TestParseArgument, parseArgumentFloatInvalidValue)
{
  Argument::DataType::FloatType value{};
  Argument arg{"","", "", value};
  std::string str_argument = "abcd";
  ASSERT_THROW(ArgumentParser::parseArgument(arg, str_argument), std::invalid_argument);

  ASSERT_DOUBLE_EQ(value, 0.0);
}

TEST(TestParseArgument, parseArgumentSignedIntNegative)
{
  Argument::DataType::SignedIntType value{};
  Argument arg{"","", "", value};
  const Argument::DataType::SignedIntType argument{-34324};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<Argument::DataType::SignedIntType*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentSignedIntPositve)
{
  Argument::DataType::SignedIntType value{};
  Argument arg{"","", "", value};
  const Argument::DataType::SignedIntType argument{28938998};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<Argument::DataType::SignedIntType*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentSignedIntMaxValue)
{
  Argument::DataType::SignedIntType value{};
  Argument arg{"","", "", value};
  const Argument::DataType::SignedIntType argument{std::numeric_limits<Argument::DataType::SignedIntType>::max()};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<Argument::DataType::SignedIntType*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentSignedIntMinValue)
{
  Argument::DataType::SignedIntType value{};
  Argument arg{"","", "", value};
  const Argument::DataType::SignedIntType argument{std::numeric_limits<Argument::DataType::SignedIntType>::min()};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<Argument::DataType::SignedIntType*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentSignedInvalidValue1)
{
  Argument::DataType::SignedIntType value{};
  Argument arg{"","", "", value};
  std::string str_argument = "abcd";
  ASSERT_THROW(ArgumentParser::parseArgument(arg, str_argument), std::invalid_argument);

  ASSERT_EQ(value, 0);
}

TEST(TestParseArgument, parseArgumentSignedInvalidValue2)
{
  Argument::DataType::SignedIntType value{};
  Argument arg{"","", "", value};
  std::string str_argument = "2.7";
  ASSERT_THROW(ArgumentParser::parseArgument(arg, str_argument), std::invalid_argument);

  ASSERT_EQ(value, 0);
}

TEST(TestParseArgument, parseArgumentUnsignedInt)
{
  Argument::DataType::UnsignedIntType value{};
  Argument arg{"","", "", value};
  const Argument::DataType::UnsignedIntType argument{34324};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<Argument::DataType::UnsignedIntType*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentUnsignedIntMaxValue)
{
  Argument::DataType::UnsignedIntType value{};
  Argument arg{"","", "", value};
  const Argument::DataType::UnsignedIntType argument{std::numeric_limits<Argument::DataType::UnsignedIntType>::max()};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<Argument::DataType::UnsignedIntType*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentUnsignedIntMinValue)
{
  Argument::DataType::UnsignedIntType value{};
  Argument arg{"","", "", value};
  const Argument::DataType::UnsignedIntType argument{std::numeric_limits<Argument::DataType::UnsignedIntType>::min()};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<Argument::DataType::UnsignedIntType*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentUnsignedInvalidValue1)
{
  Argument::DataType::UnsignedIntType value{};
  Argument arg{"","", "", value};
  std::string str_argument = "abcd";
  ASSERT_THROW(ArgumentParser::parseArgument(arg, str_argument), std::invalid_argument);

  ASSERT_EQ(value, 0);
}

TEST(TestParseArgument, parseArgumentUnsignedInvalidValue2)
{
  Argument::DataType::UnsignedIntType value{};
  Argument arg{"","", "", value};
  std::string str_argument = "2.7";
  ASSERT_THROW(ArgumentParser::parseArgument(arg, str_argument), std::invalid_argument);

  ASSERT_EQ(value, 0);
}

TEST(TestParseArgument, parseArgumentUnsignedInvalidValue3)
{
  Argument::DataType::UnsignedIntType value{};
  Argument arg{"","", "", value};
  std::string str_argument = "-435";
  ASSERT_THROW(ArgumentParser::parseArgument(arg, str_argument), std::invalid_argument);

  ASSERT_EQ(value, 0);
}

TEST(TestParseArgument, parseArgumentBoolNoArg)
{
  Argument::DataType::BoolType value{};
  Argument arg{"","", "", value};
  const Argument::DataType::BoolType argument{};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<Argument::DataType::BoolType*>(arg.getArgument()));
}

TEST(TestParseArgument, parseArgumentBoolArg)
{
  Argument::DataType::BoolType value{};
  Argument arg{"","", "", value};
  const Argument::DataType::BoolType argument{true};
  std::string str_argument = std::to_string(argument);
  ASSERT_NO_THROW(ArgumentParser::parseArgument(arg, str_argument));

  ASSERT_EQ(argument, *reinterpret_cast<Argument::DataType::BoolType*>(arg.getArgument()));
}

TEST(TestParseArgument, getUserArgumentsSimple)
{
  Argument::DataType::UnsignedIntType numbers{};
  Argument arg1{"n", "numbers", "", numbers};

  Argument::DataType::UnsignedIntType count{};
  Argument arg2{"c", "count", "", count};

  Argument::DataType::StringType file{};
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
  Argument::DataType::SignedIntType numbers{};
  Argument arg1{"n", "numbers", "", numbers};

  Argument::DataType::UnsignedIntType count{};
  Argument arg2{"c", "count", "", count};

  Argument::DataType::StringType file{};
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
  Argument::DataType::SignedIntType numbers{};
  Argument arg1{"n", "numbers", "", numbers};

  Argument::DataType::UnsignedIntType count{};
  Argument arg2{"c", "count", "", count};

  Argument::DataType::StringType file{};
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

TEST(TestParseArgument, getUserArgumentsVerboseMultipleBlanks)
{
  Argument::DataType::SignedIntType numbers{};
  Argument arg1{"n", "numbers", "", numbers};

  Argument::DataType::UnsignedIntType count{};
  Argument arg2{"c", "count", "", count};

  Argument::DataType::StringType file{};
  Argument arg3{"f", "file", "", file};

  std::vector<Argument> supported_arguments{arg1, arg2, arg3};

  std::string terminal_args{"-n     43     -file some_file.txt"};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<Argument> provided_arguments{};
  ASSERT_NO_THROW(provided_arguments = argument_parser.getUserArguments());
  ASSERT_EQ(provided_arguments.size(), 2);
  ASSERT_EQ(provided_arguments.at(0), arg1);
  ASSERT_EQ(provided_arguments.at(1), arg3);
}

TEST(TestParseArgument, getUserArgumentsInvalidArg1)
{
  Argument::DataType::SignedIntType numbers{};
  Argument arg1{"n", "numbers", "", numbers};

  Argument::DataType::UnsignedIntType count{};
  Argument arg2{"c", "count", "", count};

  Argument::DataType::StringType file{};
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

TEST(TestParseArgument, getUserArgumentsInvalidArg2)
{
  Argument::DataType::SignedIntType numbers{};
  Argument arg1{"n", "numbers", "", numbers};

  Argument::DataType::UnsignedIntType count{};
  Argument arg2{"c", "count", "", count};

  Argument::DataType::StringType file{};
  Argument arg3{"f", "file", "", file};

  std::vector<Argument> supported_arguments{arg1, arg2, arg3};

  std::string terminal_args{"-nothing-to-do-here"};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<Argument> provided_arguments{};
  ASSERT_NO_THROW(provided_arguments = argument_parser.getUserArguments());
  ASSERT_TRUE(provided_arguments.empty());
}

TEST(TestParseArgument, getUserArgumentsInvalidArg3)
{
  Argument::DataType::SignedIntType numbers{};
  Argument arg1{"n", "numbers", "", numbers};

  Argument::DataType::UnsignedIntType count{};
  Argument arg2{"c", "count", "", count};

  Argument::DataType::StringType file{};
  Argument arg3{"f", "file", "", file};

  std::vector<Argument> supported_arguments{arg1, arg2, arg3};

  std::string terminal_args{"-n some_invalid_value"};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<Argument> provided_arguments{};
  ASSERT_THROW(provided_arguments = argument_parser.getUserArguments(), std::invalid_argument);
}

TEST(TestParseArgument, getUserArgumentsInvalidArg4)
{
  Argument::DataType::SignedIntType numbers{};
  Argument arg1{"n", "numbers", "", numbers};

  Argument::DataType::UnsignedIntType count{};
  Argument arg2{"c", "count", "", count};

  Argument::DataType::StringType file{};
  Argument arg3{"f", "file", "", file};

  std::vector<Argument> supported_arguments{arg1, arg2, arg3};

  std::string terminal_args{"-n 3.14"};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<Argument> provided_arguments{};
  ASSERT_THROW(provided_arguments = argument_parser.getUserArguments(), std::invalid_argument);
}

TEST(TestParseArgument, getUserArgumentsInvalidArg5)
{
  Argument::DataType::SignedIntType numbers{};
  Argument arg1{"n", "numbers", "", numbers};

  Argument::DataType::UnsignedIntType count{};
  Argument arg2{"c", "count", "", count};

  Argument::DataType::StringType file{};
  Argument arg3{"f", "file", "", file};

  std::vector<Argument> supported_arguments{arg1, arg2, arg3};

  std::string terminal_args{"-n 3,14"};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<Argument> provided_arguments{};
  ASSERT_THROW(provided_arguments = argument_parser.getUserArguments(), std::invalid_argument);
}

TEST(TestParseArgument, getUserArgumentsInvalidArg6)
{
  Argument::DataType::SignedIntType numbers{};
  Argument arg1{"n", "numbers", "", numbers};

  Argument::DataType::UnsignedIntType count{};
  Argument arg2{"c", "count", "", count};

  Argument::DataType::StringType file{};
  Argument arg3{"f", "file", "", file};

  std::vector<Argument> supported_arguments{arg1, arg2, arg3};

  std::string terminal_args{"-n 3 32 43 23"};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<Argument> provided_arguments{};
  ASSERT_THROW(provided_arguments = argument_parser.getUserArguments(), std::invalid_argument);
}

TEST(TestParseArgument, getUserArgumentsEmpty)
{
  Argument::DataType::SignedIntType numbers{};
  Argument arg1{"n", "numbers", "", numbers};

  Argument::DataType::UnsignedIntType count{};
  Argument arg2{"c", "count", "", count};

  Argument::DataType::StringType file{};
  Argument arg3{"f", "file", "", file};

  std::vector<Argument> supported_arguments{arg1, arg2, arg3};

  std::string terminal_args{};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<Argument> provided_arguments{};
  ASSERT_NO_THROW(provided_arguments = argument_parser.getUserArguments());
  ASSERT_TRUE(provided_arguments.empty());
}

TEST(TestParseArgument, getUserArgumentsStringList)
{
  Argument::DataType::SignedIntType numbers{};
  Argument arg1{"n", "numbers", "", numbers};

  Argument::DataType::StringListType list{};
  Argument arg2{"l", "list", "", list};

  Argument::DataType::StringType file{};
  Argument arg3{"f", "file", "", file};

  std::vector<Argument> supported_arguments{arg1, arg2, arg3};

  std::string terminal_args{"-f myFavouriteFile.csv -list Alice Bob Tom Dave Charly -n 43"};
  ArgumentParser argument_parser(terminal_args, supported_arguments);

  std::vector<Argument> provided_arguments{};
  ASSERT_NO_THROW(provided_arguments = argument_parser.getUserArguments());
  ASSERT_EQ(provided_arguments.size(), 3);

  ASSERT_EQ(*reinterpret_cast<Argument::DataType::StringType*>(provided_arguments.at(0).getArgument()), "myFavouriteFile.csv");

  const Argument::DataType::StringListType expected_arg_list{"Alice", "Bob", "Tom", "Dave", "Charly"};
  ASSERT_EQ(*reinterpret_cast<Argument::DataType::StringListType*>(provided_arguments.at(1).getArgument()), expected_arg_list);

  ASSERT_EQ(*reinterpret_cast<Argument::DataType::SignedIntType*>(provided_arguments.at(2).getArgument()), 43);
}