#include "gtest/gtest.h"
#include "../inc/argument_parser.hpp"

class TestArgument : public ::testing::Test
{};


TEST(TestArgument, ArgumentBoolConstructor)
{
  bool arg{};
  ASSERT_NO_THROW(Argument("", "", "", arg));

  const std::string BRIEF{"brief"};
  const std::string VERBOSE{"verbose"};
  const std::string DESCRIPTION{"description"};
  arg = true;
  Argument argument = Argument(BRIEF, VERBOSE, DESCRIPTION, arg);

  ASSERT_EQ(argument.getBrief(), BRIEF);
  ASSERT_EQ(argument.getVerbose(), VERBOSE);
  ASSERT_EQ(argument.getDescription(), DESCRIPTION);
  ASSERT_EQ(argument.getArgumentType(), Argument::ArgumentType::kBool);
  ASSERT_EQ(argument.getArgument(), reinterpret_cast<void*>(&arg));
  ASSERT_EQ(*reinterpret_cast<bool*>(argument.getArgument()), arg);

  arg = false;
  ASSERT_EQ(*reinterpret_cast<bool*>(argument.getArgument()), arg);
}


TEST(TestArgument, ArgumentUnsignedConstructor)
{
  unsigned long arg{};
  ASSERT_NO_THROW(Argument("", "", "", arg));

  const std::string BRIEF{"brief"};
  const std::string VERBOSE{"verbose"};
  const std::string DESCRIPTION{"description"};
  arg = 42;
  Argument argument = Argument(BRIEF, VERBOSE, DESCRIPTION, arg);

  ASSERT_EQ(argument.getBrief(), BRIEF);
  ASSERT_EQ(argument.getVerbose(), VERBOSE);
  ASSERT_EQ(argument.getDescription(), DESCRIPTION);
  ASSERT_EQ(argument.getArgumentType(), Argument::ArgumentType::kUnsignedInteger);
  ASSERT_EQ(argument.getArgument(), reinterpret_cast<void*>(&arg));
  ASSERT_EQ(*reinterpret_cast<size_t*>(argument.getArgument()), arg);

  arg = 71;
  ASSERT_EQ(*reinterpret_cast<size_t*>(argument.getArgument()), arg);
}


TEST(TestArgument, ArgumentSignedConstructor)
{
  long arg{};
  ASSERT_NO_THROW(Argument("", "", "", arg));

  const std::string BRIEF{"brief"};
  const std::string VERBOSE{"verbose"};
  const std::string DESCRIPTION{"description"};
  arg = 93;
  Argument argument = Argument(BRIEF, VERBOSE, DESCRIPTION, arg);

  ASSERT_EQ(argument.getBrief(), BRIEF);
  ASSERT_EQ(argument.getVerbose(), VERBOSE);
  ASSERT_EQ(argument.getDescription(), DESCRIPTION);
  ASSERT_EQ(argument.getArgumentType(), Argument::ArgumentType::kSignedInteger);
  ASSERT_EQ(argument.getArgument(), reinterpret_cast<void*>(&arg));
  ASSERT_EQ(*reinterpret_cast<ssize_t*>(argument.getArgument()), arg);

  arg = 42;
  ASSERT_EQ(*reinterpret_cast<ssize_t*>(argument.getArgument()), arg);
}


TEST(TestArgument, ArgumentFloatConstructor)
{
  double arg{};
  ASSERT_NO_THROW(Argument("", "", "", arg));

  const std::string BRIEF{"brief"};
  const std::string VERBOSE{"verbose"};
  const std::string DESCRIPTION{"description"};
  arg = 3.14;
  Argument argument = Argument(BRIEF, VERBOSE, DESCRIPTION, arg);

  ASSERT_EQ(argument.getBrief(), BRIEF);
  ASSERT_EQ(argument.getVerbose(), VERBOSE);
  ASSERT_EQ(argument.getDescription(), DESCRIPTION);
  ASSERT_EQ(argument.getArgumentType(), Argument::ArgumentType::kFloat);
  ASSERT_EQ(argument.getArgument(), reinterpret_cast<void*>(&arg));
  ASSERT_DOUBLE_EQ(*reinterpret_cast<double*>(argument.getArgument()), arg);

  arg = 2.7;
  ASSERT_DOUBLE_EQ(*reinterpret_cast<double*>(argument.getArgument()), arg);
}


TEST(TestArgument, ArgumentStringConstructor)
{
  std::string arg{};
  ASSERT_NO_THROW(Argument("", "", "", arg));

  const std::string BRIEF{"brief"};
  const std::string VERBOSE{"verbose"};
  const std::string DESCRIPTION{"description"};
  arg = "Hello";
  Argument argument = Argument(BRIEF, VERBOSE, DESCRIPTION, arg);

  ASSERT_EQ(argument.getBrief(), BRIEF);
  ASSERT_EQ(argument.getVerbose(), VERBOSE);
  ASSERT_EQ(argument.getDescription(), DESCRIPTION);
  ASSERT_EQ(argument.getArgumentType(), Argument::ArgumentType::kString);
  ASSERT_EQ(argument.getArgument(), reinterpret_cast<void*>(&arg));
  ASSERT_EQ(*reinterpret_cast<std::string*>(argument.getArgument()), arg);

  arg = "World";
  ASSERT_EQ(*reinterpret_cast<std::string*>(argument.getArgument()), arg);
}

TEST(TestArgument, TestDefaultValues)
{
  std::string arg{};
  Argument argument("", "", "", arg);
  ASSERT_FALSE(argument.providedByUser());

  ASSERT_NO_THROW(argument.setProvidedByUser());
  ASSERT_TRUE(argument.providedByUser());
}

TEST(TestArgument, ArgumentStringListConstructor)
{
    std::vector<std::string> arg{};
    ASSERT_NO_THROW(Argument("", "", "", arg));

    const std::string BRIEF{"brief"};
    const std::string VERBOSE{"verbose"};
    const std::string DESCRIPTION{"description"};
    arg.emplace_back("Hello");
    arg.emplace_back("World");
    Argument argument = Argument(BRIEF, VERBOSE, DESCRIPTION, arg);

    ASSERT_EQ(argument.getBrief(), BRIEF);
    ASSERT_EQ(argument.getVerbose(), VERBOSE);
    ASSERT_EQ(argument.getDescription(), DESCRIPTION);
    ASSERT_EQ(argument.getArgumentType(), Argument::ArgumentType::kStringList);
    ASSERT_EQ(argument.getArgument(), reinterpret_cast<void*>(&arg));
    ASSERT_EQ(*reinterpret_cast<std::vector<std::string>*>(argument.getArgument()), arg);

    ASSERT_EQ(arg.size(), 2);
    ASSERT_EQ(arg.at(0), "Hello");
    ASSERT_EQ(arg.at(1), "World");

    arg.erase(arg.end());
    ASSERT_EQ(*reinterpret_cast<std::vector<std::string>*>(argument.getArgument()), arg);
}