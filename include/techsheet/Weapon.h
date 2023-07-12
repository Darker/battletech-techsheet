#pragma once
#include "Ammo.h"
#include "compile_defs.h"
#include "fixed_str.h"
#include "id_defs.h"
#include "scalar_defs.h"

namespace techsheet
{

using weapon_name = fixed_str<MAX_LEN_WEAPON_NAME>;

struct Weapon
{
  weapon_name name;
  component_id component;
  Ammo ammoType = Ammo::NONE;
  range rmin{ 0 };
  range rsht{ 0 };
  range rmid{ 0 };
  range rlon{ 0 };
  heat ht{ 0 };

  heat ht_dmg{ 0 };
  byte clusters{ 1 };
  byte shotsPerCluster{ 1 };
  
  bool isRear = false;
  bool explodes = false;

  static constexpr Weapon fromType(Ammo type)
  {
    Weapon result;
    result.name = Ammo_getName(type);
    switch (type)
    {
    case Ammo::LRM_5:

    }
    return result;
  }
};

}
