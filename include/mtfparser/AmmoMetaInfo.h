#pragma once
#include <techsheet/Ammo.h>
#include <techsheet/scalar_defs.h>

namespace mtfparser
{
constexpr std::size_t MAX_AMMO_ALT_NAMES = 15;
struct AmmoMetaInfo
{
  techsheet::ammo_count shots;
  techsheet::Ammo type;
  // basically just needed for ammo explosion
  techsheet::damage perShot;
  std::array<std::string_view, MAX_AMMO_ALT_NAMES> names;
};

}
