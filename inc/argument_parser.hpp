#pragma once

#include <utility>
#include <vector>
#include <array>
#include <memory>


#include "argument.hpp"

class ArgumentParser
{
public:
  ArgumentParser(std::string terminal_args, std::vector<std::shared_ptr<Argument>>& supported_arguments) :
    terminal_args_(std::move(terminal_args)), supported_arguments_(supported_arguments)
  {}

  void getSplitUpArguments(std::vector<std::pair<std::string, std::string>>& arg_list);

  static void parseStringList(std::shared_ptr<Argument>& arg, const std::string& value);

  static void parseArgument(std::shared_ptr<Argument>& arg, const std::string& value);

  std::vector<std::shared_ptr<Argument>> getUserArguments();

private:
  std::vector<std::shared_ptr<Argument>> supported_arguments_;
  std::string terminal_args_{};

  static constexpr std::array<const char*, 3> kSupportedFalseValuesBool{"false", "f", "0"};
  static constexpr char kDefaultListSeparator{' '};
  static constexpr std::array<const char, 2> kSupportedListSeparator{';', ','};
};
