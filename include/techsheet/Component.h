#pragma once
#include "Ammo.h"
#include "compile_defs.h"
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

  enum class Special : byte
  {
    NOT_SPECIAL,
    INVALID_COMPONENT, // used to indicate errors when creating or looking up cmps
    LIFE_SUPPORT,
    SENSORS,
    COCKPIT,
    GYRO,
    ENGINE,
    ACTUATOR_BODY, // shoulder/hip
    ACTUATOR_UP, 
    ACTUATOR_LOW, // knee/elbow
    ACTUATOR_END // hand/foot
  };

  Internal position = Internal::NUM_SEGMENTS;
  component_id id{ 0 };
  //component_name name;
  // critical hit locations as d12 roll
  CritRange locations;
  // damage status
  Status status = Status::FINE;
  Special specType = Special::NOT_SPECIAL;
  byte specialHits = 0;

  constexpr bool isDestroyed() const
  {
    return status == Status::DESTROYED;
  }
  constexpr bool isSpecial() const
  {
    return specType != Special::NOT_SPECIAL && specType != Special::INVALID_COMPONENT;
  }
  constexpr bool isHealthy()
  {
    return status == Status::FINE;
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
  heat heat_removed{ 0 };
#pragma endregion

#pragma region jump_jet
  jump_power jump{ 0 };
#pragma endregion

  struct CritOption
  {
    CritRange range;
    Internal segment = Internal::NUM_SEGMENTS;
    component_id target;
  };

  static constexpr Component createInvalid();
};

inline constexpr Component Component::createInvalid()
{
  Component c;
  c.specType = Special::INVALID_COMPONENT;
  return c;
}

}
