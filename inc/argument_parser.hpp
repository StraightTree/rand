#pragma once

#include <utility>
#include <vector>
#include <array>

#include "argument.hpp"

class ArgumentParser
{
public:
  ArgumentParser(std::string terminal_args, std::vector<Argument>& supported_arguments) :
  terminal_args_(std::move(terminal_args)), supported_arguments_(supported_arguments) {}

  void getSplitUpArguments(std::vector<std::pair<std::string, std::string>>& arg_list);
  static void parseArgument(Argument& arg, const std::string& value);
  std::vector<Argument> getUserArguments();

private:
  std::vector<Argument>& supported_arguments_;
  std::string terminal_args_{};

  static constexpr std::array<const char*,3> SUPPORTED_FALSE_VALUES_BOOL{"false", "f", "0"};
};
