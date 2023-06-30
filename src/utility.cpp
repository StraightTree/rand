#include "utility.hpp"

namespace util
{
  std::string trim(const std::string& str, const std::string& whitespace /*= " \t"*/)
  {
    const auto kStrBegin = str.find_first_not_of(whitespace);
    if (kStrBegin == std::string::npos)
    {
        return "";
    } // no content

    const auto kStrEnd = str.find_last_not_of(whitespace);
    const auto kStrRange = kStrEnd - kStrBegin + 1;

    return str.substr(kStrBegin, kStrRange);
  }

  void splitStringByDelimiter(const std::string& string, const char delimiter, std::vector<std::string>& token)
  {
    std::string loc_string{string};
    size_t pos{};
    while ((pos = loc_string.find(delimiter)) != std::string::npos)
    {
      const auto kTmp = util::trim(loc_string.substr(0, pos));
      if (!kTmp.empty())
      {
        token.emplace_back(kTmp);
      }

      loc_string.erase(0, pos + 1);
    }

    const auto kTmp = util::trim(loc_string);
    if (!kTmp.empty())
    {
      token.emplace_back(kTmp);
    }
  }
}