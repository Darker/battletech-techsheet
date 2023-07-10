#pragma once
#include "Ammo.h"
#include "structure_static.h"
#include "scalar_defs.h"

namespace techsheet
{

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
  damage explosion_damage{ 0 };
  // critical hit locations as d12 roll
  byte crit_min;
  byte crit_max;
  // damage status
  Status status = Status::FINE;
  Special spec_type = Special::NOT_SPECIAL;

#pragma region ammunition
  Ammo ammo_type = Ammo::NONE;
  ammo_count ammo{0};
  constexpr bool ammoExplodes() const
  {
    return ammo_type != Ammo::NONE && ammo_type != Ammo::PLASMA;
  }
#pragma endregion

#pragma region heatsink
  heat heat_removed{ 0 };
#pragma endregion

#pragma region jump_jet
  jump_power jump{ 0 };
#pragma endregion

};

}
