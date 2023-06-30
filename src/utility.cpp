#include "utility.hpp"

namespace Util
{
    std::string trim(const std::string& str, const std::string& whitespace /*= " \t"*/)
    {
        const auto strBegin = str.find_first_not_of(whitespace);
        if (strBegin == std::string::npos)
            return ""; // no content

        const auto strEnd = str.find_last_not_of(whitespace);
        const auto strRange = strEnd - strBegin + 1;

        return str.substr(strBegin, strRange);
    }

  void splitStringByDelimiter(const std::string& string, const char delimiter, std::vector<std::string>& token)
  {
      std::string loc_string{string};
      size_t pos{};
      while ((pos = loc_string.find(delimiter)) != std::string::npos)
      {
          const auto tmp = Util::trim(loc_string.substr(0, pos));
          if (!tmp.empty())
          {
              token.emplace_back(tmp);
          }

          loc_string.erase(0, pos + 1);
      }

      const auto tmp = Util::trim(loc_string);
      if (!tmp.empty())
      {
          token.emplace_back(tmp);
      }
  }
}