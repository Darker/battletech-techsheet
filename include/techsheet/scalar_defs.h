#pragma once
#include "NumberIsh.h"
#include "types.h"

namespace techsheet
{

struct range : NumberIsh<byte, range, CalcOptions::SELF>
{
  using SelfType::NumberIsh;
};

struct ammo_count : NumberIsh<byte, ammo_count, CalcOptions::SELF, CalcOption_default_mult, CalcOption_all_to_self>
{
  using SelfType::NumberIsh;
};

struct jump_power : NumberIsh<byte, jump_power, CalcOptions::SELF, CalcOption_default_mult, CalcOption_all_to_self>
{
  using SelfType::NumberIsh;
};

struct damage : NumberIsh<byte, damage, CalcOptions::SELF, CalcOptions::UNDERLYING_TO_SELF, CalcOption_all_to_self>
{
  using SelfType::NumberIsh;

  constexpr damage operator*(ammo_count multiplier) const { return damage{ (byte) (value * multiplier.value) }; }
};

struct heat : NumberIsh<byte, heat, CalcOptions::SELF, CalcOption_default_mult, CalcOption_all_to_self>
{
  using SelfType::NumberIsh;
};

struct health : NumberIsh<byte, health, CalcOptions::SELF, CalcOptions::NONE, CalcOption_all_to_self>
{
  using SelfType::NumberIsh;
};

}