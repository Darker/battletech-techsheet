#include <techsheet/WeaponComponent.h>

#include "WeaponMetaInfo.h"

#include <optional>

namespace mtfparser
{

class LookupFailure : public std::runtime_error
{
public:
  enum class Type
  {
    // Lookup by Megamek lookup name failed, this is likely as there are many and they change
    LOOKUP_NAME,
    // Lookup by internal name failed, this should not happen!
    INTERNAL_NAME,
    INVALID
  };
  enum class Target
  {
    // if this is set, type should be internal. This means internal name lookup failed
    WEAPONS,
    // if this is set, lookup in meta info failed
    WEAPON_META
  };

  static std::string makeMessage(Type tl, Target tg, std::string_view name)
  {
    return std::string("Failed to find ")
      + (tl == Type::LOOKUP_NAME ? "lookup" : "internal")
      + " name in "
      + (tg == Target::WEAPON_META ? "metadata" : "weapon stat")
      + "database: '" + std::string{ name } + "'";
  }

  static auto metaFailure(std::string_view name)
  {
    return LookupFailure(LookupFailure::Type::LOOKUP_NAME, LookupFailure::Target::WEAPON_META, name);
  }

  static auto weaponDbFailure(std::string_view name)
  {
    return LookupFailure(LookupFailure::Type::INTERNAL_NAME, LookupFailure::Target::WEAPONS, name);
  }

  LookupFailure(Type tl, Target tg, std::string_view name)
    : std::runtime_error(makeMessage(tl, tg, name))
    , lookupType{ tl }
    , lookupTarget{ tg }
    , lookupName{ name }
  {}

  Type lookupType;
  Target lookupTarget;
  std::string lookupName = "";
};

using WeaponComponent = techsheet::WeaponComponent;

WeaponComponent weaponComponentFromName(std::string_view name);

}