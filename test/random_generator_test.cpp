//
// Created by david on 30/06/23.
//
#include "gtest/gtest.h"
#include "../inc/random_generator.hpp"

using namespace ns_random;

TEST(TestRandomGenerator, TestConstructor)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  ASSERT_NO_THROW(Generator<long> random_generator(uniform_random_engine));
}

TEST(TestRandomGenerator, TestGetNumericValid)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  long result{};
  ASSERT_NO_THROW(result = random_generator.generateNumeric(1,2));
  ASSERT_EQ(result, 1);
}

TEST(TestRandomGenerator, TestGetNumericNegativNumber)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  constexpr short kIterations{1000};
  for (short i{}; i < kIterations; i++)
  {
    long result{};
    ASSERT_NO_THROW(result = random_generator.generateNumeric(-4000, 0));
    ASSERT_LT(result, 0);
  }
}

TEST(TestRandomGenerator, TestGetNumericPositivNumber)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  constexpr short kIterations{1000};
  for (short i{}; i < kIterations; i++)
  {
    long result{};
    ASSERT_NO_THROW(result = random_generator.generateNumeric(0, 4000));
    ASSERT_GE(result, 0);
  }
}

TEST(TestRandomGenerator, TestGetNumericInvalid1)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  constexpr short kIterations{20};
  for (short i{}; i < kIterations; i++)
  {
    long result{};
    ASSERT_THROW(result = random_generator.generateNumeric(32, 32), std::invalid_argument);
  }
}

TEST(TestRandomGenerator, TestGetNumericInvalid2)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  constexpr short kIterations{20};
  for (short i{}; i < kIterations; i++)
  {
    long result{};
    ASSERT_THROW(result = random_generator.generateNumeric(60, 32), std::invalid_argument);
  }
}

TEST(TestRandomGenerator, TestCreateAlphabetValid)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  std::vector<char> alphabet{};
  std::vector<ns_random::Parameter::CharacterType> types{ns_random::Parameter::CharacterType::kLowerCase, ns_random::Parameter::CharacterType::kUpperCase};
  ASSERT_NO_THROW(random_generator.createAlphabet(types, alphabet));

  ASSERT_EQ(alphabet.size(), 52);
  for (char a = 'A'; a <= 'Z'; a++)
  {
    ASSERT_NE(alphabet.cend(), std::find(alphabet.cbegin(), alphabet.cend(), a) ) << "not found: " << a;
  }

  for (char a = 'a'; a <= 'z'; a++)
  {
    ASSERT_NE(alphabet.cend(), std::find(alphabet.cbegin(), alphabet.cend(), a) );
  }
}

TEST(TestRandomGenerator, TestCreateAlphabetValid2)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  std::vector<char> alphabet{};
  std::vector<ns_random::Parameter::CharacterType> types{ns_random::Parameter::CharacterType::kLowerCase, ns_random::Parameter::CharacterType::kUpperCase, ns_random::Parameter::CharacterType::kNumeric};
  ASSERT_NO_THROW(random_generator.createAlphabet(types, alphabet));

  for (char a = 'A'; a <= 'Z'; a++)
  {
    ASSERT_NE(alphabet.cend(), std::find(alphabet.cbegin(), alphabet.cend(), a) );
  }

  for (char a = 'a'; a <= 'z'; a++)
  {
    ASSERT_NE(alphabet.cend(), std::find(alphabet.cbegin(), alphabet.cend(), a) );
  }

  for (char a = '0'; a <= '9'; a++)
  {
    ASSERT_NE(alphabet.cend(), std::find(alphabet.cbegin(), alphabet.cend(), a) );
  }
}

TEST(TestRandomGenerator, TestCreateAlphabetInvalid)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  std::vector<char> alphabet{};
  const std::vector<ns_random::Parameter::CharacterType> kTypes{ns_random::Parameter::CharacterType::kLowerCase, ns_random::Parameter::CharacterType::kUpperCase, ns_random::Parameter::CharacterType::kNumeric, ns_random::Parameter::CharacterType::kSpecialChar};

  for (const auto& kType : kTypes)
  {
    std::vector<ns_random::Parameter::CharacterType> types{kType, kType};
    ASSERT_THROW(random_generator.createAlphabet(types, alphabet), std::invalid_argument);
  }
}

TEST(TestRandomGenerator, TestCreateAlphabetInvalid2)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  std::vector<char> alphabet{};
  ASSERT_THROW(random_generator.createAlphabet({}, alphabet), std::invalid_argument);
}

TEST(TestRandomGenerator, TestCreateAlphabetUndefinedFlag)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  std::vector<char> alphabet{};
  const std::vector<ns_random::Parameter::CharacterType> kTypes{static_cast<ns_random::Parameter::CharacterType>(99), static_cast<ns_random::Parameter::CharacterType>(3)};
  ASSERT_THROW(random_generator.createAlphabet(kTypes, alphabet), std::invalid_argument);
}

TEST(TestRandomGenerator, TestGenerateStringValid)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  const std::vector<ns_random::Parameter::CharacterType> kTypes{ns_random::Parameter::CharacterType::kLowerCase, ns_random::Parameter::CharacterType::kUpperCase, ns_random::Parameter::CharacterType::kNumeric, ns_random::Parameter::CharacterType::kSpecialChar};
  constexpr long kLength{27};
  std::string result{};
  ASSERT_NO_THROW(result = random_generator.generateString(kTypes, kLength));
  ASSERT_EQ(result.length(), kLength);

  std::sort(result.begin(), result.end());
  result.erase(std::unique(result.begin(), result.end()), result.end());
  //at least 60% of the character should be different
  ASSERT_GT(result.length(), kLength*0.6);
}

TEST(TestRandomGenerator, TestGenerateStringValidLongString)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  const std::vector<ns_random::Parameter::CharacterType> kTypes{ns_random::Parameter::CharacterType::kLowerCase, ns_random::Parameter::CharacterType::kUpperCase, ns_random::Parameter::CharacterType::kNumeric, ns_random::Parameter::CharacterType::kSpecialChar};
  constexpr long kLength{1500};
  std::string result{};
  ASSERT_NO_THROW(result = random_generator.generateString(kTypes, kLength));
  ASSERT_EQ(result.length(), kLength);

  std::sort(result.begin(), result.end());
  result.erase(std::unique(result.begin(), result.end()), result.end());
  ASSERT_GT(result.length(), 87);
}

TEST(TestRandomGenerator, TestGenerateStringNegativeLength)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  const std::vector<ns_random::Parameter::CharacterType> kTypes{ns_random::Parameter::CharacterType::kLowerCase, ns_random::Parameter::CharacterType::kUpperCase, ns_random::Parameter::CharacterType::kNumeric, ns_random::Parameter::CharacterType::kSpecialChar};
  constexpr long kLength{-42};
  ASSERT_THROW(random_generator.generateString(kTypes, kLength), std::invalid_argument);
}

TEST(TestRandomGenerator, TestGenerateStringZeroLength)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  const std::vector<ns_random::Parameter::CharacterType> kTypes{ns_random::Parameter::CharacterType::kLowerCase, ns_random::Parameter::CharacterType::kUpperCase, ns_random::Parameter::CharacterType::kNumeric, ns_random::Parameter::CharacterType::kSpecialChar};
  constexpr long kLength{0};
  std::string result{};
  ASSERT_THROW(result = random_generator.generateString(kTypes, kLength), std::invalid_argument);
  ASSERT_TRUE(result.empty());
}

TEST(TestRandomGenerator, TestGenerateStringReturnsDifferentStrings)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  const std::vector<ns_random::Parameter::CharacterType> kTypes{ns_random::Parameter::CharacterType::kLowerCase, ns_random::Parameter::CharacterType::kUpperCase, ns_random::Parameter::CharacterType::kNumeric, ns_random::Parameter::CharacterType::kSpecialChar};
  constexpr long kLength{19};
  constexpr short kIterations{100};
  std::vector<std::string> results{};
  results.reserve(kIterations);
  for (auto i = 0; i < kIterations; i++)
  {
    ASSERT_NO_THROW(results.emplace_back(random_generator.generateString(kTypes, kLength)));
  }

  std::sort(results.begin(), results.end());
  results.erase(std::unique(results.begin(), results.end()), results.end());
  ASSERT_GE(results.size(), kIterations*0.98);
}

TEST(TestRandomGenerator, TestGenerateStringUndefinedFlag)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  const std::vector<ns_random::Parameter::CharacterType> kTypes{static_cast<ns_random::Parameter::CharacterType>(99)};
  constexpr long kLength{19};
  ASSERT_THROW(random_generator.generateString(kTypes, kLength), std::invalid_argument);
}

TEST(TestRandomGenerator, TestGenerateStringNumericOnly)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  const std::vector<ns_random::Parameter::CharacterType> kTypes{ns_random::Parameter::CharacterType::kNumeric};
  constexpr long kLength{10};
  constexpr short kIterations{100};
  for (auto i = 0; i < kIterations; i++)
  {
    std::string result{};
    ASSERT_NO_THROW(result = random_generator.generateString(kTypes, kLength));
    ASSERT_NO_THROW(std::stoll(result));
  }
}

TEST(TestRandomGenerator, TestGenerateStringUpperCaseOnly)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  const std::vector<ns_random::Parameter::CharacterType> kTypes{ns_random::Parameter::CharacterType::kUpperCase};
  constexpr long kLength{40};
  constexpr short kIterations{100};
  for (auto i = 0; i < kIterations; i++)
  {
    std::string result{};
    ASSERT_NO_THROW(result = random_generator.generateString(kTypes, kLength));
    ASSERT_NO_THROW(std::for_each(result.begin(), result.end(), [](const char c){if (!std::isupper(c)){throw std::runtime_error("character is not upper case!");}}));
  }
}

TEST(TestRandomGenerator, TestGenerateStringLowerCaseOnly)
{
  auto uniform_random_engine = std::make_shared<UniformRandomEngine<long>>();
  Generator<long> random_generator(uniform_random_engine);

  const std::vector<ns_random::Parameter::CharacterType> kTypes{ns_random::Parameter::CharacterType::kLowerCase};
  constexpr long kLength{40};
  constexpr short kIterations{100};
  for (auto i = 0; i < kIterations; i++)
  {
    std::string result{};
    ASSERT_NO_THROW(result = random_generator.generateString(kTypes, kLength));
    ASSERT_NO_THROW(std::for_each(result.begin(), result.end(), [](const char c){if (!std::islower(c)){throw std::runtime_error("character is not lower case!");}}));
  }
}