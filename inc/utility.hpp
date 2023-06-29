#pragma once
#include <string>
#include <charconv>
#include <stdexcept>

namespace Util
{
    std::string trim(const std::string& str, const std::string& whitespace = " \t");


    template<typename T>
    T strToNumericType(const std::string_view& str)
    {
        if (str.empty())
            return 0;

      T result{};
      const auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), result);

      if (ec == std::errc() && ptr == str.end())
        return result;

      throw std::invalid_argument("This is not a valid value!");
    }
}