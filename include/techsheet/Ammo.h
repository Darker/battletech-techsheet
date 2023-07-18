#pragma once
#include "template_defs.h"
#include "types.h"

#include <array>

namespace techsheet
{

enum class Ammo : byte
{
  NONE,
  AC_2,
  AC_5,
  AC_10,
  AC_20,
  LRIFLE,
  MRIFLE,
  SRIFLE,
  LB_10_X_AC,
  LRM_5,
  LRM_10,
  LRM_15,
  LRM_20,
  SRM_2,
  SRM_4,
  SRM_6,
  MG,
  RAIL_GUN,
  CHEM_LASER,
  CHEM_PPC,
  PLASMA,
  GAUSS,
  AMS,
  NO_AMMO_TYPES
};

constexpr std::array Ammo_names
{
  "NONE",
  "AC_2",
  "AC_5",
  "AC_10",
  "AC_20",
  "LRIFLE",
  "MRIFLE",
  "SRIFLE",
  "LB_10_X_AC",
  "LRM_5",
  "LRM_10",
  "LRM_15",
  "LRM_20",
  "SRM_2",
  "SRM_4",
  "SRM_6",
  "MG",
  "RAIL_GUN",
  "CHEM_LASER",
  "CHEM_PPC",
  "PLASMA",
  "GAUSS",
  "AMS"
};
static_assert(Ammo_names.size() == to_underlying(Ammo::NO_AMMO_TYPES), "If you add weapon, add it to the names too.");
constexpr auto Ammo_getName = enumNameLookup<Ammo, Ammo::NO_AMMO_TYPES, &Ammo_names>;
constexpr auto Ammo_getValue = enumValueLookup<Ammo, Ammo::NO_AMMO_TYPES, &Ammo_names>;
constexpr auto Ammo_getValueNoOpt = enumValueLookupNoOpt<Ammo, Ammo::NO_AMMO_TYPES, &Ammo_names>;

constexpr bool ammoExplodes(Ammo ammo_type)
{
  return ammo_type != Ammo::NONE && ammo_type != Ammo::PLASMA;
}

// few enum error checks
static_assert(Ammo_getValue("AC_10") == Ammo::AC_10, "Do not reorder ammo enum!");
static_assert(Ammo_getValue("SRM_4") == Ammo::SRM_4, "Do not reorder ammo enum!");
static_assert(Ammo_getValue("CHEM_LASER") == Ammo::CHEM_LASER, "Do not reorder ammo enum!");
}
