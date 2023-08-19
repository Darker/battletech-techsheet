#pragma once
#include "Ammo.h"
#include "compile_defs.h"
#include "fixed_str.h"
#include "id_defs.h"
#include "RangeLimits.h"
#include "scalar_defs.h"

namespace techsheet
{

using weapon_name = fixed_str<MAX_LEN_WEAPON_NAME>;

struct Weapon
{
  constexpr Weapon() = default;
  constexpr Weapon(weapon_name name, Ammo type, RangeLimits limits, heat h, damage perShot, heat hDmg = heat{0})
    : name{name}
    , ammoType{type}
    , ranges{limits}
    , heatCaused{h}
    , htDmg{hDmg}
    , perShot{ perShot }
  {}
  weapon_name name;
  component_id component{ 0 };
  Ammo ammoType = Ammo::NONE;
  component_id ammoBin{ 0 };
  RangeLimits ranges;
  heat heatCaused{ 0 };

  heat htDmg{ 0 };
  damage perShot{ 0 };
  // how many shots are there in cluster
  byte shotsPerCluster{ 1 };
  // how many individual shots are fired per action
  byte shots{ 1 };
  
  bool isRear = false;
  // when component is destroyed
  bool explodes = false;

  constexpr bool lacksAmmo() const
  {
    return ammoBin.isInvalid() && usesAmmo();
  }

  constexpr bool usesAmmo() const
  {
    return ammoType != Ammo::NONE;
  }

  constexpr damage totalDamage() const
  {
    return damage{ static_cast<byte>(perShot.value * shots) };
  }

  static constexpr Weapon fromType(Ammo type)
  {
    Weapon result;
    result.name = Ammo_getName(type);
    result.ammoType = type;
    switch (type)
    {
    case Ammo::LRM_10:
      result.ranges.minRange = range{ 6 };
      result.ranges.sht() = range{ 7 };
      result.ranges.mid() = range{ 14 };
      result.ranges.lng() = range{ 21 };
      result.heatCaused = heat{ 4 };
      break;
    default:break;
    }
    return result;
  }
};

}
