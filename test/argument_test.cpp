#include "gtest/gtest.h"
#include "../inc/argument_parser.hpp"

class TestArgument : public ::testing::Test
{};


TEST(TestArgument, ArgumentBoolConstructor)
{
  Argument::DataType::BoolType arg{};
  ASSERT_NO_THROW(Argument("", "", "", arg));

  const std::string kBrief{"brief"};
  const std::string kVerbose{"verbose"};
  const std::string kDescription{"description"};
  arg = true;
  Argument argument = Argument(kBrief, kVerbose, kDescription, arg);

  ASSERT_EQ(argument.getBrief(), kBrief);
  ASSERT_EQ(argument.getVerbose(), kVerbose);
  ASSERT_EQ(argument.getDescription(), kDescription);
  ASSERT_EQ(argument.getArgumentType(), Argument::ArgumentType::kBool);
  ASSERT_EQ(argument.getArgument(), reinterpret_cast<void*>(&arg));
  ASSERT_EQ(*reinterpret_cast<Argument::DataType::BoolType*>(argument.getArgument()), arg);

  arg = false;
  ASSERT_EQ(*reinterpret_cast<Argument::DataType::BoolType*>(argument.getArgument()), arg);
}


TEST(TestArgument, ArgumentUnsignedConstructor)
{
  Argument::DataType::UnsignedIntType arg{};
  ASSERT_NO_THROW(Argument("", "", "", arg));

  const std::string kBrief{"brief"};
  const std::string kVerbose{"verbose"};
  const std::string kDescription{"description"};
  arg = 42;
  Argument argument = Argument(kBrief, kVerbose, kDescription, arg);

  ASSERT_EQ(argument.getBrief(), kBrief);
  ASSERT_EQ(argument.getVerbose(), kVerbose);
  ASSERT_EQ(argument.getDescription(), kDescription);
  ASSERT_EQ(argument.getArgumentType(), Argument::ArgumentType::kUnsignedInteger);
  ASSERT_EQ(argument.getArgument(), reinterpret_cast<void*>(&arg));
  ASSERT_EQ(*reinterpret_cast<Argument::DataType::UnsignedIntType*>(argument.getArgument()), arg);

  arg = 71;
  ASSERT_EQ(*reinterpret_cast<Argument::DataType::UnsignedIntType*>(argument.getArgument()), arg);
}


TEST(TestArgument, ArgumentSignedConstructor)
{
  Argument::DataType::SignedIntType arg{};
  ASSERT_NO_THROW(Argument("", "", "", arg));

  const std::string kBrief{"brief"};
  const std::string kVerbose{"verbose"};
  const std::string kDescription{"description"};
  arg = 93;
  Argument argument = Argument(kBrief, kVerbose, kDescription, arg);

  ASSERT_EQ(argument.getBrief(), kBrief);
  ASSERT_EQ(argument.getVerbose(), kVerbose);
  ASSERT_EQ(argument.getDescription(), kDescription);
  ASSERT_EQ(argument.getArgumentType(), Argument::ArgumentType::kSignedInteger);
  ASSERT_EQ(argument.getArgument(), reinterpret_cast<void*>(&arg));
  ASSERT_EQ(*reinterpret_cast<Argument::DataType::SignedIntType*>(argument.getArgument()), arg);

  arg = 42;
  ASSERT_EQ(*reinterpret_cast<Argument::DataType::SignedIntType*>(argument.getArgument()), arg);
}


TEST(TestArgument, ArgumentFloatConstructor)
{
  Argument::DataType::FloatType arg{};
  ASSERT_NO_THROW(Argument("", "", "", arg));

  const std::string kBrief{"brief"};
  const std::string kVerbose{"verbose"};
  const std::string kDescription{"description"};
  arg = 3.14;
  Argument argument = Argument(kBrief, kVerbose, kDescription, arg);

  ASSERT_EQ(argument.getBrief(), kBrief);
  ASSERT_EQ(argument.getVerbose(), kVerbose);
  ASSERT_EQ(argument.getDescription(), kDescription);
  ASSERT_EQ(argument.getArgumentType(), Argument::ArgumentType::kFloat);
  ASSERT_EQ(argument.getArgument(), reinterpret_cast<void*>(&arg));
  ASSERT_DOUBLE_EQ(*reinterpret_cast<Argument::DataType::FloatType*>(argument.getArgument()), arg);

  arg = 2.7;
  ASSERT_DOUBLE_EQ(*reinterpret_cast<Argument::DataType::FloatType*>(argument.getArgument()), arg);
}


TEST(TestArgument, ArgumentStringConstructor)
{
  Argument::DataType::StringType arg{};
  ASSERT_NO_THROW(Argument("", "", "", arg));

  const std::string kBrief{"brief"};
  const std::string kVerbose{"verbose"};
  const std::string kDescription{"description"};
  arg = "Hello";
  Argument argument = Argument(kBrief, kVerbose, kDescription, arg);

  ASSERT_EQ(argument.getBrief(), kBrief);
  ASSERT_EQ(argument.getVerbose(), kVerbose);
  ASSERT_EQ(argument.getDescription(), kDescription);
  ASSERT_EQ(argument.getArgumentType(), Argument::ArgumentType::kString);
  ASSERT_EQ(argument.getArgument(), reinterpret_cast<void*>(&arg));
  ASSERT_EQ(*reinterpret_cast<Argument::DataType::StringType*>(argument.getArgument()), arg);

  arg = "World";
  ASSERT_EQ(*reinterpret_cast<Argument::DataType::StringType*>(argument.getArgument()), arg);
}

TEST(TestArgument, TestDefaultValues)
{
  Argument::DataType::StringType arg{};
  Argument argument("", "", "", arg);
  ASSERT_FALSE(argument.providedByUser());

  ASSERT_NO_THROW(argument.setProvidedByUser());
  ASSERT_TRUE(argument.providedByUser());
}

TEST(TestArgument, ArgumentStringListConstructor)
{
  Argument::DataType::StringListType arg{};
  ASSERT_NO_THROW(Argument("", "", "", arg));

  const std::string kBrief{"brief"};
  const std::string kVerbose{"verbose"};
  const std::string kDescription{"description"};
  arg.emplace_back("Hello");
  arg.emplace_back("World");
  Argument argument = Argument(kBrief, kVerbose, kDescription, arg);

  ASSERT_EQ(argument.getBrief(), kBrief);
  ASSERT_EQ(argument.getVerbose(), kVerbose);
  ASSERT_EQ(argument.getDescription(), kDescription);
  ASSERT_EQ(argument.getArgumentType(), Argument::ArgumentType::kStringList);
  ASSERT_EQ(argument.getArgument(), reinterpret_cast<void*>(&arg));
  ASSERT_EQ(*reinterpret_cast<Argument::DataType::StringListType*>(argument.getArgument()), arg);

  ASSERT_EQ(arg.size(), 2);
  ASSERT_EQ(arg.at(0), "Hello");
  ASSERT_EQ(arg.at(1), "World");

  arg.erase(arg.end());
  ASSERT_EQ(*reinterpret_cast<Argument::DataType::StringListType*>(argument.getArgument()), arg);
}