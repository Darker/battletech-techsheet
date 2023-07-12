#pragma once
#include "Ammo.h"
#include "compile_defs.h"
#include "critical_hits.h"
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

  enum Special : byte
  {
    NOT_SPECIAL,
    LIFE_SUPPORT,
    SENSORS,
    COCKPIT,
    GYRO,
    ENGINE,
    ACTUATOR_UP,
    ACTUATOR_LOW,
    ACTUATOR_END // hand/foot
  };

  Internal position;
  component_id id;
  component_name name;
  // critical hit locations as d12 roll
  CritRange locations;
  // damage status
  Status status = Status::FINE;
  Special specType = Special::NOT_SPECIAL;
  byte specialHits = 0;

  bool isDestroyed() const
  {
    return status == Status::DESTROYED;
  }

  void reset()
  {
    status = Status::FINE;
    ammo = max_ammo;
    specialHits = 0;
  }

#pragma region ammunition
  Ammo ammoType = Ammo::NONE;
  ammo_count ammo{ 0 };
  ammo_count max_ammo{ 0 };
  damage ammo_damage{ 0 };
  constexpr bool ammoExplodes() const
  {
    return techsheet::ammoExplodes(ammoType) && ammo > 0;
  }
  constexpr damage ammoExplosionDamage() const
  {
    return ammo_damage * ammo;
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
};

}
