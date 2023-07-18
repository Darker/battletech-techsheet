#pragma once
#include <array>
#include <optional>
#include <string_view>
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

template<auto TVal>
struct always_happens_v : std::true_type
{};

#pragma region enums

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
    return { (static_cast<EnumType>(Indices))...};
  }
public:
  static constexpr std::array<EnumType, static_cast<ValueType>(LENGTH)> values
    = GenerateArray(std::make_integer_sequence<ValueType, static_cast<ValueType>(LENGTH)>{});
};

template <typename EnumType, EnumType LENGTH>
constexpr auto EnumValues = EnumValues_t<EnumType, LENGTH>::values;

template<typename TEnum, TEnum value>
constexpr auto underlyingEnumValue = to_underlying(value);

template <typename TEnum, TEnum size, const std::array<const char*, underlyingEnumValue<TEnum, size>>* names>
constexpr auto enumNameLookup = [](TEnum val) -> std::string_view
{
  if (val < size && to_underlying(val) >= 0)
  {
    return names->operator[](to_underlying(val));
  }
  else
  {
    return "InvalidEnumField";
  }
};

template <typename TEnum, TEnum size, const std::array<const char*, underlyingEnumValue<TEnum, size>>* names>
constexpr auto enumValueLookup = [](std::string_view name) -> std::optional<TEnum>
{
  for (size_t i = 0; i < to_underlying(size); ++i)
  {
    if (name == names->operator[](i))
    {
      return static_cast<TEnum>(i);
    }
  }
  return std::nullopt;
};

template <typename TEnum, TEnum size, const std::array<const char*, underlyingEnumValue<TEnum, size>>* names>
constexpr auto enumValueLookupNoOpt = [](std::string_view name) -> TEnum
{
  for (size_t i = 0; i < to_underlying(size); ++i)
  {
    if (name == names->operator[](i))
    {
      return static_cast<TEnum>(i);
    }
  }
  return size;
};

template <typename TEnum, TEnum size, const std::array<const char*, underlyingEnumValue<TEnum, size>>* names>
constexpr bool staticEnumNameCheck()
{
  constexpr auto enumToStr = enumNameLookup<TEnum, size, names>;
  constexpr auto strToEnum = enumValueLookupNoOpt<TEnum, size, names>;
  for (constexpr auto entry : EnumValues<TEnum, size>)
  {
    if constexpr (strToEnum(enumToStr(entry)) == entry)
    {
      return false;
    }
  }
  return true;
}
#pragma endregion

}