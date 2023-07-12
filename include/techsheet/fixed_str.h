#pragma once
#include "types.h"

#include <algorithm>
#include <array>
#include <cstring>
#include <string_view>
#include <type_traits>

#if __cplusplus < 202002L
namespace std
{
inline constexpr bool is_constant_evaluated() { return false; }
}
#endif

namespace techsheet
{

template<size_t length>
struct fixed_str final
{
  using container = std::array<char, length + 1>;

  constexpr static auto max_length = length;
  static constexpr const char zero_char = 0;

private:
#if __cplusplus >= 202002L
  template <std::size_t N>
  static constexpr container to_array(const char(&str)[N]) noexcept
  {
    static_assert(length >= N, "Cannot fit incoming string.");
    // turn the char[N] into a std::array<char, length + 1>
    return[&str]<std::size_t... I>(std::index_sequence<I...>)
    {
      return std::array{ (I < N ? str[I] : '\0')... };
    }(std::make_index_sequence<length + 1>());
  }
#else

  template <size_t input_size, size_t... Indices>
  static constexpr auto to_array(const char(&str)[input_size], std::integer_sequence<size_t, Indices...>)
    ->container
  {
    return { (Indices < input_size ? str[Indices] : '\0')...};
  }
  template <std::size_t N>
  static constexpr container to_array(const char(&str)[N]) noexcept
  {
    static_assert(length >= N, "Cannot fit incoming string.");
    return to_array(str, std::make_integer_sequence<size_t, length>{});
  }
#endif
public:

  constexpr fixed_str()
  {
    chars[0] = 0;
  }

  template <std::size_t N>
  constexpr fixed_str(const char(&str)[N]) noexcept : chars{ to_array<N>(str) } {}

  template <std::size_t N>
  constexpr fixed_str& operator=(const char(&str)[N]) noexcept
  {
    chars = to_array(str);
    return *this;
  }

  template<size_t other_length>
  constexpr fixed_str(const fixed_str<other_length>& other)
  {
    (*this) = other;
  }

  template<size_t other_length>
  constexpr fixed_str& operator=(const fixed_str<other_length>& other)
  {
    static_assert(length >= other_length, "Cannot fit incoming string.");

    if (std::is_constant_evaluated())
    {
      for (size_t i = 0; i < other_length; ++i)
      {
        chars[i] = other[i];
      }
    }
    else
    {
      memcpy(chars.data(), other.data(), other_length);
    }

    chars[other_length] = 0;
  }

  std::array<char, length + 1> chars;

  constexpr auto begin() const { return chars.begin(); }
  constexpr auto end() const { return chars.end(); }
  constexpr auto begin() { return chars.begin(); }
  constexpr auto end() { return chars.end(); }
  constexpr auto cbegin() const { return chars.cbegin(); }
  constexpr auto cend() const { return chars.cend(); }

  constexpr operator std::string_view() const
  {
    return { chars.data() };
  }

  constexpr std::string_view view() const
  {
    return { *this };
  }

  constexpr const char* c_str() const
  {
    return static_cast<const char*>(chars.data());
  }

  constexpr bool contains(std::string_view str) const
  {
    auto const v = view();
    return v.find(str) != v.npos;
  }

  constexpr bool operator==(std::string_view str) const
  {
    return str == chars.data();
  }

  constexpr bool operator!=(std::string_view str) const
  {
    return str != *this;
  }

  constexpr const char& operator[](size_t index) const 
  {
    if (index >= length)
    {
      return zero_char;
    }
    return chars[index];
  }

  constexpr char& operator[](size_t index)
  {
    return chars[index];
  }
};

static_assert((fixed_str<8>{"aBLEdsa"}).contains("BLE"), "contains() failed");
static_assert(!(fixed_str<8>{"aBLEdsa"}).contains("BLA"), "contains() failed");
static_assert(fixed_str<5>{"aa"} == fixed_str<4>("aa"), "comparison failed");

}
