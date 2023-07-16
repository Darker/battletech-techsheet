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
  weapon_name name;
  component_id component{ 0 };
  Ammo ammoType = Ammo::NONE;
  RangeLimits ranges;
  heat heatCaused{ 0 };

  heat htDmg{ 0 };
  damage damagePerCluster{ 0 };
  byte clusters{ 1 };
  byte shotsPerCluster{ 1 };
  
  bool isRear = false;
  // when component is destroyed
  bool explodes = false;

  constexpr damage totalDamage() const
  {
    return damage{ static_cast<byte>(damagePerCluster.value * clusters) };
  }

  static constexpr Weapon fromType(Ammo type)
  {
    Weapon result;
    result.name = Ammo_getName(type);
    result.ammoType = type;
    switch (type)
    {
    case Ammo::LRM_10:
      result.ranges.minRange = range{6};
      result.ranges.sht() = range{ 7 };
      result.ranges.mid() = range{ 14 };
      result.ranges.lng() = range{ 21 };
      result.heatCaused = heat{ 4 };
      break;
    }
    return result;
  }
};

}
