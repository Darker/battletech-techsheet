#pragma once
#include "scalar_defs.h"
#include "structure_static.h"

namespace techsheet
{

struct IncomingDamage
{
  IncomingDamage(damage dmg, Armor targetSegment, bool rearDamage = false, bool staging = false)
    : dmg(dmg)
    , target(rearDamage ? toRear(targetSegment) : targetSegment)
    , rear(isRearSegment(targetSegment) ? true : rearDamage)
    , staging(staging)
  {

  }

  damage dmg{ 0 };
  Armor target = Armor::NUM_SEGMENTS;
  bool rear = false;
  bool staging = false;

  IncomingDamage retarget(Armor newTarget) const
  {
    return { dmg, newTarget, rear, staging };
  }

  IncomingDamage retarget(Internal newTarget) const
  {
    return { dmg, toArmor(newTarget, rear), rear, staging };
  }

  IncomingDamage reduce(damage howMuch) const
  {
    return { dmg - howMuch, target, rear, staging };
  }
};

}