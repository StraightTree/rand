#include "gtest/gtest.h"
#include "../argument.cpp"

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
  ASSERT_EQ(argument.getArgumentType(), Argument::ArgumentType::BOOL);
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
  ASSERT_EQ(argument.getArgumentType(), Argument::ArgumentType::UNSIGNED_INTEGER);
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
  ASSERT_EQ(argument.getArgumentType(), Argument::ArgumentType::SIGNED_INTEGER);
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
  ASSERT_EQ(argument.getArgumentType(), Argument::ArgumentType::FLOAT);
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
  ASSERT_EQ(argument.getArgumentType(), Argument::ArgumentType::STRING);
  ASSERT_EQ(argument.getArgument(), reinterpret_cast<void*>(&arg));
  ASSERT_EQ(*reinterpret_cast<std::string*>(argument.getArgument()), arg);

  arg = "World";
  ASSERT_EQ(*reinterpret_cast<std::string*>(argument.getArgument()), arg);
}
