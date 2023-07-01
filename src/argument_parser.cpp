#include "../inc/argument_parser.hpp"

#include <algorithm>

#include "utility.hpp"

void ArgumentParser::getSplitUpArguments(std::vector<std::pair<std::string, std::string>>& arg_list)
{
  size_t pos{};
  constexpr std::array<char, 1> kDelimiter{'-'};
  while ((pos = terminal_args_.find(kDelimiter.front())) != std::string::npos)
  {
    const auto kSubstring = util::trim(terminal_args_.substr(0, pos));
    if (!kSubstring.empty())
    {
      auto p = kSubstring.find_first_of(' ');
      arg_list.emplace_back(kSubstring.substr(0, p), (p == std::string::npos ? "" : kSubstring.substr(p + 1, kSubstring.length() - p)));
    }

    terminal_args_.erase(0, pos + kDelimiter.size());
  }

  const auto kSubstring = util::trim(terminal_args_);
  if (!kSubstring.empty())
  {
    auto p = kSubstring.find_first_of(' ');
    arg_list.emplace_back(kSubstring.substr(0, p), (p == std::string::npos ? "" : kSubstring.substr(p + 1, kSubstring.length() - p)));
  }
}

void ArgumentParser::parseStringList(std::shared_ptr<Argument>& arg, const std::string& value)
{
  char separator = kDefaultListSeparator;
  for (const auto& kSep: kSupportedListSeparator)
  {
    auto pos = value.find(kSep);
    if (pos != std::string::npos)
    {
      separator = kSep;
      break;
    }
  }

  util::splitStringByDelimiter(value, separator, *reinterpret_cast<std::vector<std::string>*>(arg->getArgument()));
}

void ArgumentParser::parseArgument(std::shared_ptr<Argument>& arg, const std::string& value)
{
  switch (arg->getArgumentType())
  {
    case Argument::ArgumentType::kStringList:
    {
      parseStringList(arg, value);
      break;
    }
    case Argument::ArgumentType::kString:
    {
      auto* string_ptr = reinterpret_cast<std::string*>(arg->getArgument());
      *string_ptr = value;
      break;
    }
    case Argument::ArgumentType::kFloat:
    {
      const auto kVal = util::strToNumericType<double>(value);
      auto* double_ptr = reinterpret_cast<double*>(arg->getArgument());
      *double_ptr = kVal;
      break;
    }
    case Argument::ArgumentType::kSignedInteger:
    {
      const auto kVal = util::strToNumericType<ssize_t>(value);
      auto* signed_int_ptr = reinterpret_cast<ssize_t*>(arg->getArgument());
      *signed_int_ptr = kVal;
      break;
    }
    case Argument::ArgumentType::kUnsignedInteger:
    {
      const auto kVal = util::strToNumericType<size_t>(value);
      auto* unsigned_int_ptr = reinterpret_cast<size_t*>(arg->getArgument());
      *unsigned_int_ptr = kVal;
      break;
    }
    case Argument::ArgumentType::kBool:
    {
      std::string tmp{value};
      std::transform(tmp.begin(), tmp.end(), tmp.begin(),
                     [](unsigned char c){ return std::tolower(c); });
      const bool kVal = std::find(kSupportedFalseValuesBool.begin(), kSupportedFalseValuesBool.end(), value) ==
                        kSupportedFalseValuesBool.end();
      auto* bool_ptr = reinterpret_cast<bool*>(arg->getArgument());
      *bool_ptr = kVal;
      break;
    }
    default:
    {
      throw std::runtime_error("Argument type not supported");
    }
  }
}

std::vector<std::shared_ptr<Argument>> ArgumentParser::getUserArguments()
{
  std::vector<std::pair<std::string, std::string>> arg_list{};
  std::vector<std::shared_ptr<Argument>> provided_arguments{};
  getSplitUpArguments(arg_list);
  for (const auto& kArgPair: arg_list)
  {
    auto it = std::find_if(supported_arguments_.begin(), supported_arguments_.end(),
                           [&kArgPair](const std::shared_ptr<Argument>& supported_arg){
                               return supported_arg->getBrief() == kArgPair.first ||
                                      supported_arg->getVerbose() == kArgPair.first;
                           });

    if (it == supported_arguments_.end())
    {
      continue;
    }

    (*it)->setProvidedByUser();
    parseArgument(*it, util::trim(kArgPair.second));
    provided_arguments.emplace_back(*it);
  }
  return provided_arguments;
}