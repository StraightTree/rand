//
// Created by david on 01/07/23.
//
#include "gtest/gtest.h"
#include "../inc/rand.hpp"

TEST(RandTest, TestRandomWithoutRange)
{
  const std::string kTerminalArgs{"-r"};
  auto rand = Rand{};
  std::string output{};
  ASSERT_NO_THROW(output = rand.run(kTerminalArgs));

  for (const auto kChar : output)
  {
    ASSERT_TRUE(std::isdigit(kChar));
  }
}

TEST(RandTest, TestRandomWithUpperBound)
{
  const std::string kTerminalArgs{"-r 43"};
  auto rand = Rand{};
  constexpr short kIterations{250};

  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_NO_THROW(output = rand.run(kTerminalArgs));
    ASSERT_LE(output.length(), 2);
    ASSERT_FALSE(output.empty());

    ASSERT_NO_THROW(ASSERT_LE(std::stoi(output), 43));
  }
}

TEST(RandTest, TestRandomWithLowerUpperBound)
{
  const std::string kTerminalArgs{"-r 5 64"};
  auto rand = Rand{};
  constexpr short kIterations{250};

  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_NO_THROW(output = rand.run(kTerminalArgs));
    ASSERT_LE(output.length(), 2);
    ASSERT_FALSE(output.empty());

    ASSERT_NO_THROW(ASSERT_LE(std::stoi(output), 64));
    ASSERT_NO_THROW(ASSERT_GE(std::stoi(output), 5));
  }
}

TEST(RandTest, TestRandomWithLowerUpperBoundVerbose)
{
  const std::string kTerminalArgs{"-random 5 64"};
  auto rand = Rand{};
  constexpr short kIterations{250};

  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_NO_THROW(output = rand.run(kTerminalArgs));
    ASSERT_LE(output.length(), 2);
    ASSERT_FALSE(output.empty());

    ASSERT_NO_THROW(ASSERT_LE(std::stoi(output), 64));
    ASSERT_NO_THROW(ASSERT_GE(std::stoi(output), 5));
  }
}

TEST(RandTest, TestStringNoArgs)
{
  const std::string kTerminalArgs{"-s"};
  auto rand = Rand{};
  constexpr short kIterations{250};

  size_t length{};
  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_NO_THROW(output = rand.run(kTerminalArgs));
    if (length == 0)
      length = output.length();

    ASSERT_EQ(output.length(), length);

    std::string output_unique{output};
    std::sort(output_unique.begin(), output_unique.end());
    output_unique.erase(std::unique(output_unique.begin(), output_unique.end()), output_unique.end());
    ASSERT_GT(output_unique.length(), length*0.6) << output;
  }
}

TEST(RandTest, TestStringNumericOnly)
{
  const std::string kTerminalArgs{"-s n"};
  auto rand = Rand{};
  constexpr short kIterations{250};

  size_t length{};
  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_NO_THROW(output = rand.run(kTerminalArgs));
    if (length == 0)
      length = output.length();

    for (const auto kChar : output)
      ASSERT_TRUE(std::isdigit(kChar));
  }
}

TEST(RandTest, TestStringNumericOnlyVerbose)
{
  const std::string kTerminalArgs{"-string n"};
  auto rand = Rand{};
  constexpr short kIterations{250};

  size_t length{};
  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_NO_THROW(output = rand.run(kTerminalArgs));
    if (length == 0)
      length = output.length();

    for (const auto kChar : output)
      ASSERT_TRUE(std::isdigit(kChar));
  }
}

TEST(RandTest, TestStringNumericOnlyVerboseDoubleDash)
{
  const std::string kTerminalArgs{"--string n"};
  auto rand = Rand{};
  constexpr short kIterations{250};

  size_t length{};
  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_NO_THROW(output = rand.run(kTerminalArgs));
    if (length == 0)
      length = output.length();

    for (const auto kChar : output)
      ASSERT_TRUE(std::isdigit(kChar));
  }
}

TEST(RandTest, TestStringUpperCaseOnly)
{
  const std::string kTerminalArgs{"-s u"};
  auto rand = Rand{};
  constexpr short kIterations{250};

  size_t length{};
  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_NO_THROW(output = rand.run(kTerminalArgs));
    if (length == 0)
      length = output.length();

    for (const auto kChar : output)
      ASSERT_TRUE(std::isupper(kChar));
  }
}

TEST(RandTest, TestStringLowerCaseOnly)
{
  const std::string kTerminalArgs{"-s l"};
  auto rand = Rand{};
  constexpr short kIterations{250};

  size_t length{};
  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_NO_THROW(output = rand.run(kTerminalArgs));
    if (length == 0)
      length = output.length();

    for (const auto kChar : output)
      ASSERT_TRUE(std::islower(kChar));
  }
}

TEST(RandTest, TestStringRandomFlagOrder1)
{
  const std::string kTerminalArgs{"-s nslu"};
  auto rand = Rand{};
  constexpr short kIterations{3};

  size_t length{};
  bool numeric{};
  bool upper_case{};
  bool lower_case{};
  bool special_char{};
  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_NO_THROW(output = rand.run(kTerminalArgs));
    if (length == 0)
      length = output.length();

    for (const auto kChar : output)
    {
      if (std::isupper(kChar))
      {
        upper_case = true;
      }
      else if (std::islower(kChar))
      {
        lower_case = true;
      }
      else if (std::isdigit(kChar))
      {
        numeric = true;
      }
      else
      {
        special_char = true;
      }
    }
  }

  ASSERT_TRUE(numeric);
  ASSERT_TRUE(upper_case);
  ASSERT_TRUE(lower_case);
  ASSERT_TRUE(special_char);
}

TEST(RandTest, TestStringRandomFlagOrder2)
{
  const std::string kTerminalArgs{"-s nusl"};
  auto rand = Rand{};
  constexpr short kIterations{3};

  size_t length{};
  bool numeric{};
  bool upper_case{};
  bool lower_case{};
  bool special_char{};
  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_NO_THROW(output = rand.run(kTerminalArgs));
    if (length == 0)
      length = output.length();

    for (const auto kChar : output)
    {
      if (std::isupper(kChar))
      {
        upper_case = true;
      }
      else if (std::islower(kChar))
      {
        lower_case = true;
      }
      else if (std::isdigit(kChar))
      {
        numeric = true;
      }
      else
      {
        special_char = true;
      }
    }
  }

  ASSERT_TRUE(numeric);
  ASSERT_TRUE(upper_case);
  ASSERT_TRUE(lower_case);
  ASSERT_TRUE(special_char);
}

TEST(RandTest, TestStringDuplicateFlag)
{
  const std::string kTerminalArgs{"-s lsunl"};
  auto rand = Rand{};
  constexpr short kIterations{250};

  size_t length{};
  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_THROW(output = rand.run(kTerminalArgs), std::invalid_argument);
    ASSERT_EQ(output.length(), 0);
  }
}

TEST(RandTest, TestStringInvalidFlag)
{
  const std::string kTerminalArgs{"-s luzn"};
  auto rand = Rand{};
  constexpr short kIterations{250};

  size_t length{};
  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_THROW(output = rand.run(kTerminalArgs), std::invalid_argument);
    ASSERT_EQ(output.length(), 0);
  }
}

TEST(RandTest, TestStringLengthSpecifiedNoFlags)
{
  const std::string kTerminalArgs{"-s -l 43"};
  auto rand = Rand{};
  constexpr short kIterations{250};
  constexpr short kLength{43};

  size_t length{};
  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_NO_THROW(output = rand.run(kTerminalArgs));
    ASSERT_EQ(output.length(), kLength);
  }
}

TEST(RandTest, TestStringAllCharacterUsed)
{
  const std::string kTerminalArgs{"-s ul -l 1500"};
  auto rand = Rand{};
  constexpr short kIterations{40};
  constexpr short kLength{1500};

  size_t length{};
  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_NO_THROW(output = rand.run(kTerminalArgs));
    ASSERT_EQ(output.length(), kLength);

    std::string output_unique{output};
    std::sort(output_unique.begin(), output_unique.end());
    output_unique.erase(std::unique(output_unique.begin(), output_unique.end()), output_unique.end());
    ASSERT_EQ(output_unique.length(), 52) << "Used character: " << output_unique;
  }
}

TEST(RandTest, TestStringLengthSpecifiedNoFlagsVerbose)
{
  const std::string kTerminalArgs{"-string --length 43"};
  auto rand = Rand{};
  constexpr short kIterations{250};
  constexpr short kLength{43};

  size_t length{};
  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_NO_THROW(output = rand.run(kTerminalArgs));
    ASSERT_EQ(output.length(), kLength);
  }
}

TEST(RandTest, TestStringLengthSpecifiedFlagsSpecified)
{
  const std::string kTerminalArgs{"-s ul -l 12"};
  auto rand = Rand{};
  constexpr short kIterations{250};
  constexpr short kLength{12};

  size_t length{};
  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_NO_THROW(output = rand.run(kTerminalArgs));
    ASSERT_EQ(output.length(), kLength);

    for (const auto kChar : output)
    {
      ASSERT_TRUE(std::isupper(kChar) || std::islower(kChar));
      ASSERT_FALSE(std::isdigit(kChar));
    }
  }
}

TEST(RandTest, TestInvalidFlagBrief)
{
  const std::string kTerminalArgs{"-y sdf"};
  auto rand = Rand{};
  constexpr short kIterations{250};

  size_t length{};
  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_THROW(output = rand.run(kTerminalArgs), std::invalid_argument);
    ASSERT_EQ(output.length(), 0);
  }
}

TEST(RandTest, TestInvalidFlagVerbose)
{
  const std::string kTerminalArgs{"-ionw s d f -l 32"};
  auto rand = Rand{};
  constexpr short kIterations{250};

  size_t length{};
  for (short i{}; i < kIterations; i++)
  {
    std::string output{};
    ASSERT_THROW(output = rand.run(kTerminalArgs), std::invalid_argument);
    ASSERT_EQ(output.length(), 0);
  }
}