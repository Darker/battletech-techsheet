#pragma once
#include <array>
#include <type_traits>
#include <utility>

namespace techsheet
{

// Use this to force a false assertion only when template is actually instantiated
template<typename T>
struct never_happens : std::false_type
{};

// Use this to force a false assertion only when template is actually instantiated
template<auto TVal>
struct never_happens_v : std::false_type
{};

template<typename TEnum>
inline constexpr std::underlying_type_t<TEnum> to_underlying(TEnum val)
{
  return static_cast<std::underlying_type_t<TEnum>>(val);
}

template <typename EnumType, EnumType LENGTH>
struct EnumValues_t
{
private:
  using ValueType = typename std::underlying_type<EnumType>::type;
  template <ValueType... Indices>
  static constexpr auto GenerateArray(std::integer_sequence<ValueType, Indices...>)
    ->std::array<EnumType, sizeof...(Indices)>
  {
    return { (static_cast<EnumType>(Indices))... };
  }
public:
  static constexpr std::array<EnumType, static_cast<ValueType>(LENGTH)> values
    = GenerateArray(std::make_integer_sequence<ValueType, static_cast<ValueType>(LENGTH)>{});
};

template <typename EnumType, EnumType LENGTH>
constexpr auto EnumValues = EnumValues_t<EnumType, LENGTH>::values;

}