//
// Created by david on 30/06/23.
//
#pragma once

#include <vector>
#include <string>
#include <memory>

#include "argument.hpp"
#include "random_generator.hpp"

class Rand
{
public:
  Rand();
  void runInTerminal(const std::string& terminal_args);
  std::string run(const std::string& terminal_args);
  ns_random::Parameter buildParameterFromArguments();

private:
  [[nodiscard]] std::string printHelpText() const;
  [[nodiscard]] std::string handleUserInput();

  static constexpr Argument::DataType::UnsignedIntType kDefaultStringLength{20};

  std::vector<std::shared_ptr<Argument>> supported_args_{};
  Argument::DataType::BoolType arg_print_help_text_{};
  Argument::DataType::StringListType arg_random_number_in_range_{};
  Argument::DataType::StringType arg_random_string_flag_{};
  Argument::DataType::UnsignedIntType arg_output_length_{kDefaultStringLength};

  //Help-Text
  std::shared_ptr<Argument> argument_help_{std::make_shared<Argument>("h", "help", "Prints this help text", arg_print_help_text_)};

  //Random Number
  std::shared_ptr<Argument> argument_random_number_{std::make_shared<Argument>("r", "random", "Generates a random number in range (a, b). Usage -r a b", arg_random_number_in_range_)};

  //Random String
  std::shared_ptr<Argument> argument_random_string_{std::make_shared<Argument>("s", "string", "Generates a random string. Usage -s [nuls] (n...numbers; u...upper-case; l...lower-case; s...special character)", arg_random_string_flag_)};

  //Length
  std::shared_ptr<Argument> argument_length_{std::make_shared<Argument>("l", "length", "Limits the output to n character. Usage -l n", arg_output_length_)};
};
