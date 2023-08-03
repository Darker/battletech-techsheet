#pragma once
#include "NumberIsh.h"
#include "types.h"

namespace techsheet
{

constexpr auto FLAGS_ADD_SELF_CMP_ALL = NumberIshOpts::defaults().compareUnderlying(true).addSelf(true);

struct range : NumberIsh<byte, range, FLAGS_ADD_SELF_CMP_ALL>
{
  using SelfType::NumberIsh;
};

struct ammo_count : NumberIsh<byte, ammo_count, FLAGS_ADD_SELF_CMP_ALL>
{
  using SelfType::NumberIsh;
};

struct jump_power : NumberIsh<byte, jump_power, FLAGS_ADD_SELF_CMP_ALL>
{
  using SelfType::NumberIsh;
};

struct damage : NumberIsh<byte, damage, FLAGS_ADD_SELF_CMP_ALL>
{
  using SelfType::NumberIsh;

  constexpr damage operator*(ammo_count multiplier) const { return damage{ (byte) (value * multiplier.value) }; }
};

struct heat : NumberIsh<byte, heat, FLAGS_ADD_SELF_CMP_ALL>
{
  using SelfType::NumberIsh;
};

struct health : NumberIsh<byte, health, FLAGS_ADD_SELF_CMP_ALL>
{
  using SelfType::NumberIsh;
};

struct movement_points : NumberIsh<byte, movement_points, FLAGS_ADD_SELF_CMP_ALL>
{
  using SelfType::NumberIsh;
};

/*
* Mass is in tonnes
*/
struct mass : NumberIsh<unsigned int, mass, NumberIshOpts::defaults().addSelf(true).compareUnderlying(true)>
{
  using SelfType::NumberIsh;
};

constexpr mass operator""_tonnes(unsigned long long wgt)
{
  return mass{ static_cast<mass::base_type>(wgt) };
}


struct dice_roll : NumberIsh<byte, dice_roll, NumberIshOpts::none().addEitherToSelf(true).compareEither(true) >
{
  using SelfType::NumberIsh;

  static constexpr dice_roll impossibleRoll();

  // Impossible is specifically 255, any other "impossible" value is an error
  constexpr bool isImpossible() const { return value == 255; }
};
inline constexpr dice_roll dice_roll::impossibleRoll() { return dice_roll{ 255 }; }


}
