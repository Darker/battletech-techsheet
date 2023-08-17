#include "weapon_db.h"
#include "weapon_lookup.h"
#include "weapon_name_db.h"

#include <stdexcept>


using namespace techsheet;

namespace mtfparser
{

const Weapon& findWeapon(std::string_view name)
{
  for (const Weapon& w : Weapon_db)
  {
    if (name == w.name)
    {
      return w;
    }
  }
  throw LookupFailure::weaponDbFailure(name);
}

/*
* Finds weapon meta by internal name only
*/
const WeaponMetaInfo& findWeaponMeta(std::string_view name)
{
  for (const WeaponMetaInfo& w : Weapon_name_db)
  {
    if (name == w.internalName)
    {
      return w;
    }
  }
  throw LookupFailure(LookupFailure::Type::INTERNAL_NAME, LookupFailure::Target::WEAPON_META, name);
}

/*
* Looks into all alt names for the weapon and returns first match
*/
const WeaponMetaInfo& lookupWeaponMeta(std::string_view name)
{
  for (const WeaponMetaInfo& w : Weapon_name_db)
  {
    for (const auto& altName : w.altNames)
    {
      if (name == altName)
      {
        return w;
      }
    }
  }
  throw LookupFailure::metaFailure(name);
}

/*
* This function expects Megamek weapon name, not the internal name
*/
WeaponComponent weaponComponentFromName(std::string_view name)
{
  const WeaponMetaInfo& meta = lookupWeaponMeta(name);
  // deliberate copy here
  Weapon weapon = findWeapon(meta.internalName);
  Component cmp;
  cmp.locations = { 1, meta.critSlots };
  cmp.isWeapon = true;
  return { cmp, weapon };
}

}
