//
// Created by david on 30/06/23.
//
#include "rand.hpp"
#include "argument_parser.hpp"
#include "random_engine.hpp"
#include "utility.hpp"

#include <memory>
#include <iostream>
#include <sstream>

Rand::Rand()
{
  supported_args_.emplace_back(argument_help_);
  supported_args_.emplace_back(argument_random_number_);
  supported_args_.emplace_back(argument_random_string_);
  supported_args_.emplace_back(argument_length_);
}

void Rand::runInTerminal(const std::string& terminal_args)
{
  std::cout << run(terminal_args) << std::endl;
}

std::string Rand::run(const std::string& terminal_args)
{
  std::for_each(supported_args_.begin(), supported_args_.end(), [](std::shared_ptr<Argument>& arg){arg->initialize();});

  ArgumentParser argument_parser(terminal_args, supported_args_);
  argument_parser.getUserArguments();

  return handleUserInput();
}

std::string Rand::handleUserInput()
{
  if (argument_help_->providedByUser() && arg_print_help_text_)
  {
    return printHelpText();
  }

  auto parameter = buildParameterFromArguments();
  auto random_engine = std::make_shared<UniformRandomEngine<ssize_t>>();
  auto random_generator = ns_random::Generator<ssize_t>(random_engine);

  return random_generator.generate(parameter);
}

ns_random::Parameter Rand::buildParameterFromArguments()
{
  if (argument_random_number_->providedByUser() == argument_random_string_->providedByUser())
    throw std::invalid_argument("Invalid arguments!");

  ns_random::Parameter parameter{};
  if (argument_random_string_->providedByUser())
  {
    parameter.result_type_ = ns_random::Parameter::ResultType::kString;
    if (!arg_random_string_flag_.empty())
    {
      bool upper_case_already_specified{};
      bool lower_case_already_specified{};
      bool numeric_already_specified{};
      bool special_char_already_specified{};
      for (auto c : arg_random_string_flag_)
      {
        c = static_cast<char>(std::tolower(c));
        switch (c)
        {
          case 'u':
          {
            if (upper_case_already_specified)
              throw std::invalid_argument("Cannot specify string flag more than once!");

            upper_case_already_specified = true;
            parameter.string_flags_.emplace_back(ns_random::Parameter::CharacterType::kUpperCase);
            break;
          }
          case 'l':
          {
            if (lower_case_already_specified)
              throw std::invalid_argument("Cannot specify string flag more than once!");

            lower_case_already_specified = true;
            parameter.string_flags_.emplace_back(ns_random::Parameter::CharacterType::kLowerCase);
            break;
          }
          case 'n':
          {
            if (numeric_already_specified)
              throw std::invalid_argument("Cannot specify string flag more than once!");

            numeric_already_specified = true;
            parameter.string_flags_.emplace_back(ns_random::Parameter::CharacterType::kNumeric);
            break;
          }
          case 's':
          {
            if (special_char_already_specified)
              throw std::invalid_argument("Cannot specify string flag more than once!");

            special_char_already_specified = true;
            parameter.string_flags_.emplace_back(ns_random::Parameter::CharacterType::kSpecialChar);
            break;
          }
          default:
            throw std::invalid_argument("Unknown flag specified!");
        }
      }
    }
    else
    {
      //default values
      parameter.string_flags_.emplace_back(ns_random::Parameter::CharacterType::kUpperCase);
      parameter.string_flags_.emplace_back(ns_random::Parameter::CharacterType::kLowerCase);
    }
  }
  else
  {
    parameter.result_type_ = ns_random::Parameter::ResultType::kNumeric;
    switch (arg_random_number_in_range_.size())
    {
      case 0:
      {
        //default values
        parameter.lower_bound_ = 0;
        parameter.upper_bound_ = std::numeric_limits<ssize_t>::max();
        break;
      }
      case 1:
      {
        parameter.lower_bound_ = 0;
        parameter.upper_bound_ = util::strToNumericType<ssize_t>(arg_random_number_in_range_.front());
        break;
      }
      case 2:
      {
        parameter.lower_bound_ = util::strToNumericType<ssize_t>(arg_random_number_in_range_.front());
        parameter.upper_bound_ = util::strToNumericType<ssize_t>(arg_random_number_in_range_.back());
        break;
      }
      default:
      {
        throw std::invalid_argument("Only specification of upper- and lower-bound allowed!");
      }
    }
  }

  if (argument_length_->providedByUser())
    parameter.output_length_ = arg_output_length_;
  else
    parameter.output_length_ = kDefaultStringLength;

  return parameter;
}

std::string Rand::printHelpText() const
{
  std::stringstream ss{};
   ss << *argument_help_ << std::endl
      << *argument_random_number_ << std::endl
      << *argument_random_string_ << std::endl
      << *argument_length_ << std::endl;

   return ss.str();
}