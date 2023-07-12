#pragma once
#include "types.h"

namespace techsheet
{

struct CritRange
{
  byte min = 0;
  byte max = 0;

  constexpr bool isHit(byte roll) const
  {
    return roll >= min && roll <= max;
  }
};

}