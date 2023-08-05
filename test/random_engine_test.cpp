//
// Created by david on 30/06/23.
//
#include "gtest/gtest.h"
#include "../inc/random_engine.hpp"

class TestUniformRandomEngine : public ::testing::Test
{
};

TEST(TestUniformRandomEngine, TestConstructor)
{
  ASSERT_NO_THROW(UniformRandomEngine<char>());
}

TEST(TestUniformRandomEngine, getNumberReturnsDifferentValuesChar)
{
  UniformRandomEngine<unsigned char> uniform_random_engine{};
  constexpr int kIterations{1000};
  std::unordered_map<unsigned char, unsigned char> occurrence_counts{};
  for (int i{}; i < kIterations; i++)
  {
    occurrence_counts[uniform_random_engine.getNumber()]++;
  }

  for (const auto& kPair : occurrence_counts)
  {
    EXPECT_LE(kPair.second, 12) << static_cast<int>(kPair.first) << " has " << static_cast<int>(kPair.second) << " occurrences"; //each number should be in the map at most three times
  }
}

TEST(TestUniformRandomEngine, getNumberReturnsOnlyPositiveValues)
{
  UniformRandomEngine<short> uniform_random_engine{};
  constexpr int kIterations{1000};
  for (int i{}; i < kIterations; i++)
  {
    ASSERT_GE(uniform_random_engine.getNumber(), 0);
  }
}

TEST(TestUniformRandomEngine, getNumberReturnsCompleteRange)
{
  using ValType = unsigned char;
  UniformRandomEngine<ValType> uniform_random_engine{};
  constexpr ValType kMinVal = std::numeric_limits<ValType>::min();
  bool min_value_hit{};
  constexpr ValType kMaxVal = std::numeric_limits<ValType>::max();
  bool max_value_hit{};

  constexpr int kIterations{1000};
  for (int i{}; i < kIterations; i++)
  {
    const auto kVal = uniform_random_engine.getNumber();
    if (!min_value_hit && kMinVal == kVal)
      min_value_hit = true;

    if (!max_value_hit && kMaxVal == kVal)
      max_value_hit = true;
  }

  ASSERT_TRUE(min_value_hit);
  ASSERT_TRUE(max_value_hit);
}

TEST(TestUniformRandomEngine, getNumberReturnsDifferentValuesSignedLong)
{
  UniformRandomEngine<ssize_t> uniform_random_engine{};
  constexpr int kIterations{1000};
  std::unordered_map<ssize_t, unsigned char> occurrence_counts{};
  for (int i{}; i < kIterations; i++)
  {
    occurrence_counts[uniform_random_engine.getNumber()]++;
  }

  for (const auto& kPair : occurrence_counts)
  {
    EXPECT_LT(kPair.second, 2) << kPair.first << " has " << kPair.second << " occurrences"; //each number should be in the map at most three times
  }
}

TEST(TestUniformRandomEngine, differentEnginesReturnDifferentValues)
{
  constexpr int kIterations{1000};
  UniformRandomEngine<short> uniform_random_engine_1{};
  std::vector<short> result_1{};
  result_1.reserve(kIterations);
  UniformRandomEngine<short> uniform_random_engine_2{};
  std::vector<short> result_2{};
  result_2.reserve(kIterations);

  for (int i{}; i < kIterations; i++)
  {
    result_1.emplace_back(uniform_random_engine_1.getNumber());
    result_2.emplace_back(uniform_random_engine_2.getNumber());
  }

  ASSERT_EQ(result_1.size(), kIterations);
  ASSERT_EQ(result_1.size(), result_2.size());

  ASSERT_NE(result_1, result_2);
}