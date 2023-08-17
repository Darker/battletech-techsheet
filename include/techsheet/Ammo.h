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
  AC_4,
  AC_8,
  AC_5,
  AC_10,
  AC_15,
  AC_20,
  LRIFLE,
  MRIFLE,
  SRIFLE,
  LB_10_X_AC,
  LRM_1,
  LRM_5,
  LRM_10,
  LRM_15,
  LRM_20,
  MRM_1,
  MRM_2,
  MRM_3,
  MRM_4,
  MRM_5,
  MRM_10,
  MRM_20,
  MRM_30,
  MRM_40,
  SRM_2,
  SRM_4,
  SRM_6,
  MG,
  MG_HEAVY,
  RAIL_GUN,
  CHEMICAL_LASER,
  CHEM_PPC,
  PLASMA,
  GAUSS,
  GAUSS_LIGHT,
  AMS,
  HAG_20,
  HAG_30,
  HAG_40,
  MAGSHOT,
  NO_AMMO_TYPES
};

constexpr std::array Ammo_names
{
  "NONE",
  "AC_2",
  "AC_5",
  "AC_4",
  "AC_8",
  "AC_10",
  "AC_15",
  "AC_20",
  "LRIFLE",
  "MRIFLE",
  "SRIFLE",
  "LB_10_X_AC",
  "LRM_1",
  "LRM_5",
  "LRM_10",
  "LRM_15",
  "LRM_20",
  "MRM_1",
  "MRM_2",
  "MRM_3",
  "MRM_4",
  "MRM_5",
  "MRM_10",
  "MRM_20",
  "MRM_30",
  "MRM_40",
  "SRM_2",
  "SRM_4",
  "SRM_6",
  "MG",
  "MG_HEAVY",
  "RAIL_GUN",
  "CHEMICAL_LASER",
  "CHEM_PPC",
  "PLASMA",
  "GAUSS",
  "GAUSS_LIGHT",
  "AMS",
  "HAG_20",
  "HAG_30",
  "HAG_40",
  "MAGSHOT"
};
static_assert(Ammo_names.size() == to_underlying(Ammo::NO_AMMO_TYPES), "If you add weapon, add it to the names too.");
constexpr auto Ammo_getName = enumNameLookup<Ammo, Ammo::NO_AMMO_TYPES, &Ammo_names>;
constexpr auto Ammo_getValue = enumValueLookup<Ammo, Ammo::NO_AMMO_TYPES, &Ammo_names>;
constexpr auto Ammo_getValueNoOpt = enumValueLookupNoOpt<Ammo, Ammo::NO_AMMO_TYPES, &Ammo_names>;

constexpr bool ammoExplodes(Ammo ammo_type)
{
  return ammo_type != Ammo::NONE && ammo_type != Ammo::PLASMA;
}

constexpr byte ammoClusterSize(Ammo ammo_type)
{
  switch (ammo_type)
  {
  case Ammo::LRM_5:
  case Ammo::LRM_10:
  case Ammo::LRM_15:
  case Ammo::LRM_20:
    return 5;
  case Ammo::SRM_2:
  case Ammo::SRM_4:
  case Ammo::SRM_6:
    return 2;
  default:
    return 1;
  }
}

// few enum error checks
static_assert(Ammo_getValue("AC_10") == Ammo::AC_10, "Do not reorder ammo enum!");
static_assert(Ammo_getValue("SRM_4") == Ammo::SRM_4, "Do not reorder ammo enum!");
static_assert(Ammo_getValue("CHEMICAL_LASER") == Ammo::CHEMICAL_LASER, "Do not reorder ammo enum!");
}
