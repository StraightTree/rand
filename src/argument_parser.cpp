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

void ArgumentParser::parseStringList(Argument& arg, const std::string& value)
{
  char separator = kDefaultListSeparator;
  for (const auto& sep : kSupportedListSeparator)
  {
    auto pos = value.find(sep);
    if (pos != std::string::npos)
    {
      separator = sep;
      break;
    }
  }

  Util::splitStringByDelimiter(value, separator, *reinterpret_cast<std::vector<std::string>*>(arg.getArgument()));
}

void ArgumentParser::parseArgument(Argument& arg, const std::string& value)
{
  switch (arg.getArgumentType())
  {
    case Argument::ArgumentType::kStringList:
    {
        parseStringList(arg, value);
        break;
    }
    case Argument::ArgumentType::kString:
    {
      auto* string_ptr = reinterpret_cast<std::string*>(arg.getArgument());
      *string_ptr = value;
      break;
    }
    case Argument::ArgumentType::kFloat:
    {
      const auto val = Util::strToNumericType<double>(value);
      auto* double_ptr = reinterpret_cast<double*>(arg.getArgument());
      *double_ptr = val;
      break;
    }
    case Argument::ArgumentType::kSignedInteger:
    {
      const auto val = Util::strToNumericType<ssize_t>(value);
      auto* signed_int_ptr = reinterpret_cast<ssize_t *>(arg.getArgument());
      *signed_int_ptr = val;
      break;
    }
    case Argument::ArgumentType::kUnsignedInteger:
    {
      const auto val = Util::strToNumericType<size_t>(value);
      auto* unsigned_int_ptr = reinterpret_cast<size_t *>(arg.getArgument());
      *unsigned_int_ptr = val;
      break;
    }
    case Argument::ArgumentType::kBool:
    {
      std::string tmp{value};
      std::transform(tmp.begin(), tmp.end(), tmp.begin(),
                     [](unsigned char c){ return std::tolower(c); });
      const bool val = std::find(kSupportedFalseValuesBool.begin(), kSupportedFalseValuesBool.end(), value) == kSupportedFalseValuesBool.end();
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

    parseArgument(*it, Util::trim(arg_pair.second));
    provided_arguments.emplace_back(*it);
  }
  return provided_arguments;
}