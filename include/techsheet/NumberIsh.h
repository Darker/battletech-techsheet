#pragma once
#include "is_safe_numeric_cast.h"
#include "template_defs.h"

#include <initializer_list>
#include <limits>
#include <type_traits>


namespace techsheet
{

using CalcOptions_t = unsigned char;
enum class CalcOptions : CalcOptions_t
{
  NONE = 0,
  SELF = 0b100, // can perform calculation on self (return self type)
  UNDERLYING_TO_SELF = 0b010,  // can perform calculation on the underlying type (return self type)
  UNDERLYING_DECAY = 0b001    // can perform calculation with underlaying, but converts to underlying
};

// Since & is used for testing it makes little sense to cast back to enum
inline constexpr CalcOptions_t operator&(CalcOptions a, CalcOptions b)
{
  return static_cast<CalcOptions_t>(a) & static_cast<CalcOptions_t>(b);
}

// Used to merge multiple options together
inline constexpr CalcOptions operator|(CalcOptions a, CalcOptions b)
{
  return static_cast<CalcOptions>(static_cast<CalcOptions_t>(a) | static_cast<CalcOptions_t>(b));
}

constexpr auto CalcOption_all_to_self = CalcOptions::SELF | CalcOptions::UNDERLYING_TO_SELF;
constexpr auto CalcOption_self_and_decay = CalcOptions::SELF | CalcOptions::UNDERLYING_DECAY;
constexpr auto CalcOption_default_add = CalcOptions::NONE;
constexpr auto CalcOption_default_mult = CalcOptions::NONE;
constexpr auto CalcOption_default_compare = CalcOptions::SELF;

template<CalcOptions opts>
inline constexpr bool NumberIsh_underlying_enabled()
{
  constexpr auto both = CalcOptions::UNDERLYING_DECAY | CalcOptions::UNDERLYING_TO_SELF;
  static_assert((opts & both) != to_underlying(both), "NumberIsh UNDERLYING options are mutually exclusive");
  return (opts & both) != 0;
}

template<typename base_t,
  // this is the type that inherits NumberIsh
  typename type_t,
  // add and subtract
  CalcOptions add = CalcOption_default_add,
  // multiply and divide
  CalcOptions mult = CalcOption_default_mult,
  // == and != are always enabled, size comparison requires SELF
  // comparison with underlying type requires the underlying flag (either one)
  CalcOptions compare = CalcOption_default_compare,
  bool implicit_ctor = false>
struct NumberIsh
{
  static_assert(std::is_arithmetic_v<base_t>, "NumberIsh needs a numeric underlying type");
  using base_type = base_t;
  using WrapperType = type_t;

  constexpr static base_type max_base_value = std::numeric_limits<base_type>::max();
  constexpr static base_type min_base_value = std::numeric_limits<base_type>::min();

  // handy so that inheriting class does not have to repeat all template arguments
  using SelfType = NumberIsh;
  template <typename TTest>
  static constexpr bool is_constructible_from = is_safe_numeric_cast_v<base_type, TTest> || std::is_same_v<WrapperType, TTest>;

  explicit constexpr NumberIsh(base_type value) : value(value) {}
  explicit constexpr NumberIsh(const WrapperType& value) : value(value.value) 
  {
    static_assert(std::is_base_of_v<NumberIsh, WrapperType>, "Must provide struct that inherits NumberIsh");
  }
  constexpr NumberIsh() : value{} { static_assert(implicit_ctor, "NumberIsh implicit ctor must be explicitly enabled"); }
  // explicit conversion is allowed
  explicit constexpr operator base_type() const
  {
    return value;
  }

  base_type value;

#pragma region self comparison
  constexpr bool operator==(WrapperType other) const
  {
    return other.value == value;
  }
  constexpr bool operator!=(WrapperType other) const
  {
    return other.value != value;
  }

  constexpr bool operator>(WrapperType other) const
  {
    static_assert(compare & CalcOptions::SELF, "Size comparison with same type not supported");
    return value > other.value;
  }
  constexpr bool operator<(WrapperType other) const
  {
    static_assert(compare & CalcOptions::SELF, "Size comparison with same type not supported");
    return value < other.value;
  }
  constexpr bool operator>=(WrapperType other) const
  {
    return *this > other || *this == other;
  }
  constexpr bool operator<=(WrapperType other) const
  {
    return *this < other || *this == other;
  }
#pragma endregion
#pragma region base type comparison
  static constexpr auto base_comparison_enabled = NumberIsh_underlying_enabled<compare>();
  constexpr bool operator==(base_type other) const
  {
    static_assert(base_comparison_enabled, "Cannot compare with underlying type");
    return other == value;
  }
  constexpr bool operator!=(base_type other) const
  {
    static_assert(base_comparison_enabled, "Cannot compare with underlying type");
    return other != value;
  }

  constexpr bool operator>(base_type other) const
  {
    static_assert(base_comparison_enabled, "Cannot compare with underlying type");
    return value > other;
  }
  constexpr bool operator<(base_type other) const
  {
    static_assert(base_comparison_enabled, "Cannot compare with underlying type");
    return value < other;
  }
  constexpr bool operator>=(base_type other) const
  {
    return *this > other || *this == other;
  }
  constexpr bool operator<=(base_type other) const
  {
    return *this < other || *this == other;
  }
#pragma endregion
#pragma region operations with self

  constexpr WrapperType operator+(WrapperType other) const
  {
    static_assert(add & CalcOptions::SELF, "Addition with same type not supported");
    return WrapperType(value + other.value);
  }

  /*
  * Safe clamped addition. This will not underflow and always result in max/min possible
  * value in cases where the result cannot fit
  *
  * This results in `this + other` operation.
  */
  constexpr WrapperType add_clamp(WrapperType other) const
  {
    static_assert(add & CalcOptions::SELF, "Addition with same type not supported");
    return WrapperType{ clamped_add(value, other.value) };
  }

  constexpr WrapperType& operator+=(WrapperType other)
  {
    static_assert(add & CalcOptions::SELF, "Addition with same type not supported");
    value += other.value;
    return static_cast<WrapperType&>(*this);
  }

  constexpr WrapperType& operator-=(WrapperType other)
  {
    static_assert(add & CalcOptions::SELF, "Substraction with same type not supported");
    value -= other.value;
    return static_cast<WrapperType&>(*this);
  }

  constexpr WrapperType& operator++()
  {
    static_assert(add & CalcOptions::SELF, "Increment not supported");
    ++value;
    return *this;
  }

  constexpr WrapperType& operator--()
  {
    static_assert(add & CalcOptions::SELF, "Decrement not supported");
    --value;
    return *this;
  }

  constexpr WrapperType operator++(int)
  {
    static_assert(add & CalcOptions::SELF, "Increment not supported");
    WrapperType res{ *this };
    ++value;
    return res;
  }

  constexpr WrapperType operator--(int)
  {
    static_assert(add & CalcOptions::SELF, "Decrement not supported");
    WrapperType res{ *this };
    --value;
    return res;
  }

  constexpr WrapperType operator-(WrapperType other) const
  {
    static_assert(add & CalcOptions::SELF, "Substraction with same type not supported");
    return WrapperType(value - other.value);
  }

  /*
  * Safe clamped substraction. This will not underflow and always result in max/min possible
  * value in cases where the result cannot fit.
  * 
  * This results in `this - other` operation.
  */
  constexpr WrapperType substract_clamp(WrapperType other) const
  {
    static_assert(add & CalcOptions::SELF, "Substraction with same type not supported");
    return WrapperType{ clamped_substract(value, other.value) };
  }

  constexpr WrapperType operator*(WrapperType other) const
  {
    static_assert(mult & CalcOptions::SELF, "Multiplication with same type not supported");
    return WrapperType(value * other.value);
  }

  constexpr WrapperType operator/(WrapperType other) const
  {
    static_assert(mult & CalcOptions::SELF, "Division with same type not supported");
    return WrapperType(value / other.value);
  }

#pragma endregion
#pragma region operations with base type

  static constexpr auto underlying_enabled_add = NumberIsh_underlying_enabled<add>();
  static constexpr auto underlying_enabled_mult = NumberIsh_underlying_enabled<mult>();
  using underlying_add_result_t = typename std::conditional < (add& CalcOptions::UNDERLYING_TO_SELF) != 0, WrapperType, base_type >::type;
  using underlying_mult_result_t = typename std::conditional < (mult& CalcOptions::UNDERLYING_TO_SELF) != 0, WrapperType, base_type >::type;

  // operator- really means value * (-1)
  constexpr underlying_mult_result_t operator-() const
  {
    static_assert(underlying_enabled_mult, "Operator - not supported");
    return underlying_mult_result_t(-value);
  }

  constexpr underlying_add_result_t operator+(base_type other) const
  {
    static_assert(underlying_enabled_add, "Addition with underlying type not supported");
    return underlying_add_result_t(value + other.value);
  }

  /*
  * Safe clamped addition. This will not underflow and always result in max/min possible
  * value in cases where the result cannot fit
  *
  * This results in `this + other` operation.
  */
  constexpr underlying_add_result_t add_clamp(base_type other) const
  {
    static_assert(underlying_enabled_add, "Addition with underlying type not supported");
    return underlying_add_result_t{ clamped_add(value, other.value) };
  }

  constexpr underlying_add_result_t operator-(base_type other) const
  {
    static_assert(underlying_enabled_add, "Substraction with underlying type not supported");
    return underlying_add_result_t(value - other.value);
  }

  /*
  * Safe clamped substraction. This will not underflow and always result in max/min possible
  * value in cases where the result cannot fit.
  *
  * This results in `this - other` operation.
  */
  constexpr underlying_add_result_t substract_clamp(base_type other) const
  {
    static_assert(underlying_enabled_add, "Substraction with underlying type not supported");
    return underlying_add_result_t{ clamped_substract(value, other.value) };
  }

  constexpr underlying_mult_result_t operator*(base_type other) const
  {
    static_assert(underlying_enabled_mult, "Multiplication with underlying type not supported");
    return underlying_mult_result_t(value * other.value);
  }

  constexpr underlying_mult_result_t operator/(base_type other) const
  {
    static_assert(underlying_enabled_mult, "Division with underlying type not supported");
    return underlying_mult_result_t(value / other.value);
  }
#pragma endregion
#pragma region static math helpers
  static constexpr WrapperType max_of(std::initializer_list<WrapperType> values)
  {
    WrapperType smallest{ std::numeric_limits<base_type>::min() };
    for (const auto& val : values)
    {
      if (val > smallest)
      {
        smallest = val;
      }
    }
    return smallest;
  }
  static constexpr WrapperType min_of(std::initializer_list<WrapperType> values)
  {
    WrapperType largest{ std::numeric_limits<base_type>::max() };
    for (const auto& val : values)
    {
      if (val < largest)
      {
        largest = val;
      }
    }
    return largest;
  }
#pragma endregion
#pragma region creation helpers
  static constexpr WrapperType max_value()
  { 
    return WrapperType{ max_base_value };
  };
  static constexpr WrapperType min_value()
  {
    return WrapperType{ min_base_value };
  };
  /*
  * Forces cast from any numeric type to this value. There are no checks what so ever.
  */
  template <typename TSource>
  static constexpr WrapperType forced_cast(TSource numericValue)
  {
    static_assert(std::is_arithmetic_v<TSource>, "forcedCast a numeric source type");
    return WrapperType{ static_cast<base_type>(numericValue) };
  }
#pragma endregion

#pragma region internal math helpers
private:
  static constexpr base_type clamped_add(base_type a, base_type b)
  {
    // overflow
    if (b > 0 && a > max_base_value - b)
    {
      return max_base_value;
    }
    // underflow
    else if (b < 0 && a < min_base_value - b)
    {
      return min_base_value;
    }
    else
    {
      return a + b;
    }
  }
  static constexpr base_type clamped_substract(base_type a, base_type b)
  {
    // overflow
    if (b < 0 && a > max_base_value + b)
    {
      return max_base_value;
    }
    // underflow
    else if (b > 0 && a < min_base_value + b)
    {
      return min_base_value;
    }
    else
    {
      return a - b;
    }
  }
#pragma endregion
};

//inline constexpr bool is_

}