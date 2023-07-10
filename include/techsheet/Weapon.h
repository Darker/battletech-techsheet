#pragma once
#include "compile_defs.h"
#include "fixed_str.h"
#include "scalar_defs.h"

namespace techsheet
{

using weapon_name = fixed_str<MAX_LEN_WEAPON_NAME>;

struct Weapon
{
  weapon_name name;
  range rmin{0};
  range rsht;
  range rmid;
  range rlon;
  heat ht;

  heat ht_dmg{0};
  byte clusters{1};
  
  bool is_rear = false;
};

}
