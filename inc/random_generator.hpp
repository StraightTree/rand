//
// Created by david on 30/06/23.
//
#pragma once

#include "random_engine.hpp"

#include <memory>
#include <vector>

namespace ns_random
{
  struct Parameter
  {
    enum class ResultType
    {
      kNumeric,
      kString
    };

    enum class CharacterType
    {
      kUpperCase,
      kLowerCase,
      kNumeric,
      kSpecialChar
    };

    ResultType result_type_{};
    std::vector<CharacterType> string_flags_{};
    ssize_t lower_bound_{};
    ssize_t upper_bound_{};
    size_t output_length_{};
  };

  template <typename T>
  class Generator
  {
  public:
    explicit Generator(std::shared_ptr<AbstractRandomEngine<T>> random_engine) : random_engine_(random_engine)
    {}

    std::string generate(const Parameter& parameter)
    {
      switch (parameter.result_type_)
      {
        case Parameter::ResultType::kNumeric:
        {
          return std::to_string(generateNumeric(parameter.lower_bound_, parameter.upper_bound_));
        }
        case Parameter::ResultType::kString:
        {
          return generateString(parameter.string_flags_, parameter.output_length_);
        }
        default:
          throw std::runtime_error("Undefined result type!");
      }
    }

    std::string generateString(const std::vector<typename Parameter::CharacterType>& flags, long output_length)
    {
      if (output_length <= 0)
        throw std::invalid_argument("Length of string must strictly be larger than 0!");

      std::vector<char> alphabet{};
      createAlphabet(flags, alphabet);
      if (alphabet.empty())
        throw std::runtime_error("Cannot create string from empty alphabet!");

      std::string result{};
      result.resize(output_length);
      for (long l{}; l < output_length; l++)
      {
        result.at(l) = alphabet.at(random_engine_->getNumber()%(alphabet.size()-1));
      }
      return result;
    }

    void createAlphabet(const std::vector<typename Parameter::CharacterType>& flags, std::vector<char>& alphabet)
    {
      bool upper_case_already_specified{};
      bool lower_case_already_specified{};
      bool numeric_already_specified{};
      bool special_char_already_specified{};
      for (const auto& kFlag : flags)
      {
        switch (kFlag)
        {
          case Parameter::CharacterType::kUpperCase:
          {
            if (upper_case_already_specified)
              throw std::invalid_argument("Flag for upper-case was specified more than once!");
            upper_case_already_specified = true;

            constexpr std::array<char,26> kCharacter{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
            alphabet.insert(alphabet.end(), kCharacter.begin(), kCharacter.end());
            break;
          }
          case Parameter::CharacterType::kLowerCase:
          {
            if (lower_case_already_specified)
              throw std::invalid_argument("Flag for lower-case was specified more than once!");
            lower_case_already_specified = true;

            constexpr std::array<char,26> kCharacter{'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
            alphabet.insert(alphabet.end(), kCharacter.begin(), kCharacter.end());
            break;
          }
          case Parameter::CharacterType::kNumeric:
          {
            if (numeric_already_specified)
              throw std::invalid_argument("Flag numerics was specified more than once!");
            numeric_already_specified = true;

            constexpr std::array<char,10> kCharacter{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
            alphabet.insert(alphabet.end(), kCharacter.begin(), kCharacter.end());
            break;
          }
          case Parameter::CharacterType::kSpecialChar:
          {
            if (special_char_already_specified)
              throw std::invalid_argument("Flag special character was specified more than once!");
            special_char_already_specified = true;

            constexpr std::array<char,27> kCharacter{'!', '#', '$', '%', '&', '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', ']', '^', '_', '{', '}', '~'};
            alphabet.insert(alphabet.end(), kCharacter.begin(), kCharacter.end());
            break;
          }
          default:
            throw std::invalid_argument("Undefined flag for random string generation!");
        }
      }

      if (alphabet.empty())
        throw std::invalid_argument("Using an empty alphabet is not allowed");
    }

    T generateNumeric(T lower_bound, T upper_bound)
    {
      if (lower_bound >= upper_bound)
        throw std::invalid_argument("lower bound cannot be larger or equal to upper bound!");

      return lower_bound + random_engine_->getNumber() % (upper_bound - lower_bound);
    }

  private:
    std::shared_ptr<AbstractRandomEngine<T>> random_engine_{};
  };
}