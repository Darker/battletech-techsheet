#pragma once
#include "Ammo.h"
#include "compile_defs.h"
#include "component_static.h"
#include "CritRange.h"
#include "fixed_str.h"
#include "id_defs.h"
#include "structure_static.h"
#include "scalar_defs.h"

namespace techsheet
{

using component_name = fixed_str<MAX_LEN_COMPONENT_NAME>;

struct Component
{
  enum class Status : byte
  {
    FINE,
    // this is the component's last round, after this it is gone
    // note that heatsinks already do not count when in this state
    LAST_TURN,
    // component is dead, Dave
    DESTROYED
  };

  Internal position = Internal::NUM_SEGMENTS;
  component_id id{ 0 };
  component_name name{""};
  //component_name name;
  // critical hit locations as d12 roll
  CritRange locations;
  // damage status
  Status status = Status::FINE;
  SpecialComponent specType = SpecialComponent::NOT_SPECIAL;
  byte specialHits = 0;
  bool isWeapon = false;

  constexpr bool isDestroyed() const
  {
    return status == Status::DESTROYED;
  }
  constexpr bool isSpecial() const
  {
    return specType != SpecialComponent::NOT_SPECIAL && specType != SpecialComponent::NO_SPECIAL_TYPES;
  }
  constexpr bool isHealthy() const
  {
    return status == Status::FINE;
  }
  constexpr bool isValid() const
  {
    return position != Internal::NUM_SEGMENTS;
  }
  constexpr bool isHeatsink() const
  {
    return heatRemoved > 0;
  }
  constexpr bool isAmmo() const
  {
    return ammoType != Ammo::NONE;
  }
  constexpr bool isAmmo(Ammo type) const
  {
    return ammoType == type;
  }
  constexpr bool isJumpJet() const
  {
    return jump > 0;
  }

  void reset()
  {
    status = Status::FINE;
    ammo = maxAmmo;
    specialHits = 0;
  }

#pragma region ammunition
  Ammo ammoType = Ammo::NONE;
  ammo_count ammo{ 0 };
  ammo_count maxAmmo{ 0 };
  damage ammoDamage{ 0 };
  constexpr bool ammoExplodes() const
  {
    return techsheet::ammoExplodes(ammoType) && ammo > 0;
  }
  constexpr damage ammoExplosionDamage() const
  {
    return ammoDamage * ammo;
  }
#pragma endregion

#pragma region heatsink
  heat heatRemoved{ 0 };
#pragma endregion

#pragma region jump_jet
  jump_power jump{ 0 };
#pragma endregion

  static constexpr Component createInvalid();
};

inline constexpr Component Component::createInvalid()
{
  Component c;
  c.specType = SpecialComponent::NO_SPECIAL_TYPES;
  return c;
}

}
