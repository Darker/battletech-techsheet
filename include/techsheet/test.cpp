#include "NumberIsh.h"

#include <cmath>
#include <iostream>

using namespace techsheet;


struct fahrenheit;

struct celsius : NumberIsh<double, celsius, CalcOptions::SELF>
{
  using SelfType::NumberIsh;
  // here we use implicit operator, since the conversion is revesible
  // and always meaningful
  constexpr operator fahrenheit() const;
};

struct fahrenheit : NumberIsh<double, fahrenheit, CalcOptions::SELF>
{
  using SelfType::NumberIsh;

  constexpr operator celsius() const
  {
    return celsius((5 / 9.0) * (value - 32));
  }
};

constexpr celsius operator""_celsius(long double n)
{
  return celsius{ static_cast<double>(n) };
}
constexpr fahrenheit operator""_fahrenheit(long double n)
{
  return fahrenheit{ static_cast<double>(n) };
}

inline constexpr celsius::operator fahrenheit() const
{
  return fahrenheit(value * (5 / 9.0) + 32);
}

enum class Internal
{
  A,
  B,
  NUM_SEGMENTS
};

struct NextStructure
{
  Internal structure;

  constexpr operator bool() const
  {
    return structure != Internal::NUM_SEGMENTS;
  }
  constexpr operator Internal() const
  {
    return structure;
  }
};

int main()
{
  fahrenheit temp_fh{ 451 };
  celsius book_burn_temp = temp_fh;
  std::cout << "It is not actually true that paper catches fire at " << std::lround(book_burn_temp.value) << " degrees C\n";
  std::cout << "But it is still " << (double)(book_burn_temp - celsius(22)) << " degrees C above comfortable temperature.\n";
  std::cout << std::boolalpha;
  std::cout << "Is 451 deg F more than 300 def C? Answer: " << (((celsius)451.0_fahrenheit) > 300.0_celsius) << "\n";
}
