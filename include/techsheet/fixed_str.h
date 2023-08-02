#pragma once
#include "stl_polyfill.h"
#include "types.h"

#include <algorithm>
#include <array>
#include <cstring>
#include <string_view>
#include <type_traits>


namespace techsheet
{

template<size_t max_length_p>
struct fixed_str final
{
  constexpr static auto max_length = max_length_p;

  using container = std::array<char, max_length + 1>;
  
  static constexpr const char zero_char = 0;

private:
#if __cplusplus >= 202002L
  template <std::size_t N>
  static constexpr container to_array(const char(&str)[N]) noexcept
  {
    static_assert(max_length + 1 >= N, "Cannot fit incoming string.");
    // turn the char[N] into a std::array<char, length + 1>
    return[&str]<std::size_t... I>(std::index_sequence<I...>)
    {
      return std::array{ (I < N ? str[I] : '\0')... };
    }(std::make_index_sequence<max_length + 1>());
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
    static_assert(max_length + 1 >= N, "Cannot fit incoming string.");
    return to_array(str, std::make_integer_sequence<size_t, max_length>{});
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

#pragma region const char* assignment
private:
  template<typename char_ptr>
  using ptr_check_t = std::enable_if_t<std::is_pointer_v<char_ptr>&&
    std::is_same_v<std::remove_cvref_t<std::remove_pointer_t<char_ptr>>, char>>;
public:

  template<typename char_ptr,
    typename = ptr_check_t<char_ptr>>
  fixed_str(char_ptr str)
  {
    std::strncpy(chars.data(), str, max_length);
    chars[max_length] = '\0';
  }

  template<typename char_ptr,
    typename = ptr_check_t<char_ptr>>
  fixed_str& operator=(char_ptr str)
  {
    std::strncpy(chars.data(), str, max_length);
    chars[max_length] = '\0';
    return *this;
  }
#pragma endregion

  constexpr fixed_str(std::string_view other)
  {
    (*this) = other;
  }

  constexpr fixed_str& operator=(std::string_view other)
  {
    const auto otherLen = std::min(other.size(), max_length);
    if (otherLen > 0)
    {
      if (std::is_constant_evaluated())
      {
        for (size_t i = 0; i < otherLen; ++i)
        {
          chars[i] = other[i];
        }
      }
      else
      {
        memcpy(chars.data(), other.data(), otherLen);
      }
      chars[otherLen] = '\0';
    }
    else
    {
      chars[0] = '\0';
    }
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
    static_assert(max_length >= other_length, "Cannot fit incoming string.");

    if (std::is_constant_evaluated())
    {
      for (size_t i = 0; i < other_length; ++i)
      {
        chars[i] = other[i];
      }
    }
    else
    {
      memcpy(chars.data(), other.chars.data(), other_length);
    }

    chars[other_length] = 0;
    return *this;
  }

  template <size_t new_size>
  constexpr fixed_str<new_size> expand() const
  {
    static_assert(new_size >= max_length, "Cannot 'expand' a string to smaller size");
    return fixed_str<new_size>{*this};
  }

  template <size_t additional_size>
  constexpr fixed_str<max_length+additional_size> grow_by() const
  {
    return expand<max_length + additional_size>();
  }

  std::array<char, max_length + 1> chars;

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

  constexpr bool startsWith(std::string_view str) const
  {
    auto const v = view();
    return v.find(str) == 0;
  }

  constexpr bool endsWith(std::string_view str) const
  {
    const auto other_len = str.length();
    if (other_len <= max_length)
    {
      auto const v = view();
      const auto my_len = v.length();
      if (other_len <= my_len)
      {
        return v.find(str) == my_len - other_len;
      }
    }
    return false;
  }

  constexpr bool operator==(std::string_view str) const
  {
    return str == chars.data();
  }

  constexpr bool operator!=(std::string_view str) const
  {
    return str != *this;
  }
  template<size_t other_length>
  static constexpr size_t merge_length = std::max(other_length, max_length);
  // this is not necessary but it prevents accidental truncation during concatenation
  template<size_t other_length>
  constexpr fixed_str<merge_length<other_length>> operator+(fixed_str<other_length> str)
  {
    fixed_str<merge_length<other_length>> result{ *this };
    result += str;
    return result;
  }

  constexpr fixed_str& operator+=(std::string_view str)
  {
    const auto inLen = str.length();
    const auto cpyStart = view().length();
    const auto maxCpyEnd = std::min(cpyStart + inLen, max_length);
    const auto cpyLen = maxCpyEnd - cpyStart;

    if (cpyLen > 0)
    {
      if (std::is_constant_evaluated())
      {
        for (size_t i = cpyStart; i < maxCpyEnd; ++i)
        {
          chars[i] = str[i];
        }
      }
      else
      {
        memcpy(chars.data() + cpyStart, str.data(), cpyLen);
      }
      chars[maxCpyEnd] = 0;
    }
    return *this;
  }

  constexpr fixed_str operator+(std::string_view str) const
  {
    fixed_str result{ *this };
    result += str;
    return result;
  }

  constexpr const char& operator[](size_t index) const 
  {
    if (index >= max_length)
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

// deduction guide
template<std::size_t N>
fixed_str(const char(&)[N])->fixed_str<N - 1>; // -1 for null terminator
#ifndef __MINGW32__
static_assert((fixed_str<8>{"aBLEdsa"}).contains("BLE"), "contains() failed");
static_assert(!(fixed_str<8>{"aBLEdsa"}).contains("BLA"), "contains() failed");
static_assert(fixed_str<5>{"aa"} == fixed_str<4>("aa"), "comparison failed");
static_assert((fixed_str<7>{"abcdef"}) == fixed_str<8>("abcdef"), "compare failed");
static_assert((fixed_str<6>{"abcde"}) != fixed_str<8>("abcdefg"), "compare failed");
static_assert((fixed_str<8>{"abcdef"}) != fixed_str<8>("abcdefg"), "compare failed");
#endif
//static_assert((fixed_str{"ab"}+fixed_str{"c"}).contains("abc"), "compare failed");
// does not compile in MSVS because of debug call on array [] operator
// static_assert((fixed_str<7>{"abc"} + "def") == fixed_str<7>("abcdef"), "compare or add failed");
}
