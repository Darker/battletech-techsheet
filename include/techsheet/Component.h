#pragma once
#include "Structure.h"
#include "scalar_defs.h"

namespace techsheet
{


struct Component
{
  enum class Status
  {
    FINE,
    // this is the component's last round, after this it is gone
    // note that heatsinks already do not count when in this state
    LAST_TURN,
    // component is dead, Dave
    DESTROYED
  };

  Internal position;
  damage explosion_damage{ 0 };
  // critical hit locations as d12 roll
  byte crit_min;
  byte crit_max;
  // 
};

}
