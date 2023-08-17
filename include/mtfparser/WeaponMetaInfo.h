#pragma once
#include <techsheet/Weapon.h>

namespace mtfparser
{
constexpr std::size_t MAX_WEAPON_ALT_NAMES = 11;
struct WeaponMetaInfo
{
  techsheet::weapon_name internalName;
  techsheet::byte critSlots;
  std::array<std::string_view, MAX_WEAPON_ALT_NAMES> altNames;
};

}
