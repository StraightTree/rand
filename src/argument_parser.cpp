#include "../inc/argument_parser.hpp"

#include <algorithm>
#include <sstream>

#include "utility.hpp"

void ArgumentParser::getSplitUpArguments(std::vector<std::pair<std::string, std::string>>& arg_list)
{
  size_t pos{};
  constexpr std::array<char,1>DELIMITER{'-'};
  while ((pos = terminal_args_.find(DELIMITER.front())) != std::string::npos)
  {
    const auto tmp = Util::trim(terminal_args_.substr(0, pos));
    if (!tmp.empty())
    {
      auto p = tmp.find_first_of(' ');
      arg_list.emplace_back(tmp.substr(0, p), tmp.substr(p+1, tmp.length()-p));
    }

    terminal_args_.erase(0, pos + DELIMITER.size());
  }

  const auto tmp = Util::trim(terminal_args_);
  if (!tmp.empty())
  {
    auto p = tmp.find_first_of(' ');
    arg_list.emplace_back(tmp.substr(0, p), tmp.substr(p+1, tmp.length()-p));
  }
}
/*
bool ArgumentParser::strToUnsignedInt(std::string string)
{
  std::istringstream iss(string);
  float f;
  iss >> std::noskipws >> f;
  // Check the entire string was consumed and if either failbit or badbit is set
  return iss.eof() && !iss.fail();
}*/

void ArgumentParser::parseArgument(Argument& arg, const std::string& value)
{
  switch (arg.getArgumentType())
  {
    case Argument::ArgumentType::STRING:
    {
      auto* string_ptr = reinterpret_cast<std::string*>(arg.getArgument());
      *string_ptr = value;
      break;
    }
    case Argument::ArgumentType::FLOAT:
    {
      const auto val = std::stod(value);
      auto* double_ptr = reinterpret_cast<double*>(arg.getArgument());
      *double_ptr = val;
      break;
    }
    case Argument::ArgumentType::SIGNED_INTEGER:
    {
      const auto val = std::stoll(value);
      auto* signed_int_ptr = reinterpret_cast<ssize_t *>(arg.getArgument());
      *signed_int_ptr = val;
      break;
    }
    case Argument::ArgumentType::UNSIGNED_INTEGER:
    {
      const auto val = std::stoull(value);
      auto* unsigned_int_ptr = reinterpret_cast<size_t *>(arg.getArgument());
      *unsigned_int_ptr = val;
      break;
    }
    case Argument::ArgumentType::BOOL:
    {
      std::string tmp{value};
      std::transform(tmp.begin(), tmp.end(), tmp.begin(),
                     [](unsigned char c){ return std::tolower(c); });
      const bool val = std::find(SUPPORTED_FALSE_VALUES_BOOL.begin(), SUPPORTED_FALSE_VALUES_BOOL.end(), value) == SUPPORTED_FALSE_VALUES_BOOL.end();
      auto* bool_ptr = reinterpret_cast<bool *>(arg.getArgument());
      *bool_ptr = val;
      break;
    }
    default:
    {
      throw std::runtime_error("Argument type not supported");
    }
  }
  arg.setProvidedByUser();
}

std::vector<Argument> ArgumentParser::getUserArguments()
{
  std::vector<std::pair<std::string, std::string>> arg_list{};
  std::vector<Argument> provided_arguments{};
  getSplitUpArguments(arg_list);
  for (const auto& arg_pair: arg_list)
  {
    auto it = std::find_if(supported_arguments_.begin(), supported_arguments_.end(), [&arg_pair](const Argument& supported_arg)
    {
      return supported_arg.getBrief() == arg_pair.first || supported_arg.getVerbose() == arg_pair.first;
    });

    if (it == supported_arguments_.cend())
      continue;

    parseArgument(*it, arg_pair.second);
    provided_arguments.emplace_back(*it);
  }
  return provided_arguments;
}