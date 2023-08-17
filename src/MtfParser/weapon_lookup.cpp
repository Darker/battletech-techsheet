#include "ammo_db.h"
#include "weapon_db.h"
#include "weapon_lookup.h"
#include "weapon_name_db.h"

#include <techsheet/string_view_util.h>

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

const WeaponMetaInfo* lookupWeaponMetaPtr(std::string_view name)
{
  for (const WeaponMetaInfo& w : Weapon_name_db)
  {
    for (const auto& altName : w.altNames)
    {
      if (name == altName)
      {
        return &w;
      }
    }
  }
  return nullptr;
}

/*
* Looks into all alt names for the weapon and returns first match
*/
const WeaponMetaInfo& lookupWeaponMeta(std::string_view name)
{
  const WeaponMetaInfo* entry = lookupWeaponMetaPtr(name);
  if (entry == nullptr)
  {
    throw LookupFailure::metaFailure(name);
  }
  else
  {
    return *entry;
  }
}

const AmmoMetaInfo& lookupAmmo(std::string_view name)
{
  for (const AmmoMetaInfo& a : Ammo_db)
  {
    for (const auto& altName : a.names)
    {
      if (name == altName)
      {
        return a;
      }
    }
  }
  throw LookupFailure::ammoFailure(name);
}

/*
* This function expects Megamek weapon name, not the internal name
*/
WeaponComponent weaponComponentFromName(std::string_view name)
{
  std::string_view origName = name;
  bool rearWeapon = false;
  if (str::endswith(name, " (r)"))
  {
    rearWeapon = true;
    name = name.substr(0, name.length() - 4);
  }

  const WeaponMetaInfo* meta = lookupWeaponMetaPtr(name);

  if (meta != nullptr)
  {
    // deliberate copy here
    Weapon weapon = findWeapon(meta->internalName);
    Component cmp;
    cmp.locations = { 1, meta->critSlots };
    cmp.isWeapon = true;
    cmp.name = weapon.name;
    return { cmp, weapon };
  }
  else if (rearWeapon)
  {
    throw LookupFailure::metaFailure(origName);
  }
  else
  {
    const AmmoMetaInfo& ammo = lookupAmmo(name);
    Component cmp;
    cmp.locations = { 1, 1 };
    cmp.ammoType = ammo.type;
    cmp.ammo = cmp.maxAmmo = ammo.shots;
    cmp.ammoDamage = ammo.perShot;
    return { cmp, std::nullopt };
  }
}

}
