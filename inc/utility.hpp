#pragma once

#include <string>
#include <vector>
#include <charconv>
#include <stdexcept>

namespace util
{
  std::string trim(const std::string& str, const std::string& whitespace = " \t");


  template <typename T>
  T strToNumericType(const std::string_view& str)
  {
    if (str.empty())
    {
      return 0;
    }

    T result{};
    const auto [kPtr, kEc] = std::from_chars(str.data(), str.data() + str.size(), result);

    if (kEc == std::errc() && kPtr == str.end())
    {
      return result;
    }

    throw std::invalid_argument("This is not a valid value!");
  }

  void splitStringByDelimiter(const std::string& string, char delimiter, std::vector<std::string>& token);

  std::string createStringFromCharPtrArray(int size, char* char_ptr_array[]);
}