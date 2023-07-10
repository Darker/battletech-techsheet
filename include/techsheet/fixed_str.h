#pragma once
#include "types.h"

#include <algorithm>
#include <array>
#include <cstring>
#include <string_view>

namespace techsheet
{

template<size_t length>
struct fixed_str
{
  constexpr static auto max_length = length;

  constexpr fixed_str(const char* str)
  {
    auto len = std::strlen(str);
    auto real_len = std::min(len, length);
    memccpy(chars.data(), str, real_len);
    chars[real_len] = 0;
  }

  std::array<char, length + 1> chars;

  operator std::string_view() const
  {
    return { chars.data() };
  }
};

}