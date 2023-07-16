#pragma once
#include "NumberIsh.h"
#include "types.h"

namespace techsheet
{

struct range : NumberIsh<byte, range, CalcOptions::SELF, CalcOptions::NONE, CalcOption_all_to_self>
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

struct movement_points : NumberIsh<byte, movement_points, CalcOptions::SELF, CalcOptions::NONE, CalcOption_all_to_self>
{
  using SelfType::NumberIsh;
};

/*
* Mass is in tonnes
*/
struct mass : NumberIsh<unsigned int, mass, CalcOptions::SELF, CalcOptions::NONE, CalcOptions::SELF>
{
  using SelfType::NumberIsh;
};

constexpr mass operator""_tonnes(unsigned long long wgt)
{
  return mass{ static_cast<mass::base_type>(wgt) };
}

struct dice_roll : NumberIsh<byte, dice_roll, CalcOption_all_to_self, CalcOptions::NONE, CalcOption_all_to_self>
{
  using SelfType::NumberIsh;

  static constexpr dice_roll impossibleRoll();

  // Impossible is specifically 255, any other "impossible" value is an error
  constexpr bool isImpossible() const { return value == 255; }
};
inline constexpr dice_roll dice_roll::impossibleRoll() { return dice_roll{ 255 }; }


}
