#pragma once
#include "Component.h"
#include "CritRange.h"
#include "id_defs.h"
#include "types.h"

namespace techsheet
{

struct CritRollResult final
{
  component_id destroyedCmp{ 0 };
  Component::Special specialHit = Component::Special::NOT_SPECIAL;
  bool rollAgain = false;
};

namespace crit
{
constexpr CritRollResult ROLL_AGAIN{ component_id{0}, Component::Special::NOT_SPECIAL, true };
constexpr CritRollResult INVALID_ROLL{ component_id{0}, Component::Special::INVALID_COMPONENT, true };

constexpr CritRange MAX_HEAD_LEG_RANGE{ 1, 6 };
constexpr CritRange MAX_BODY_RANGE{ 1, 12 };

constexpr bool isValidRoll(Internal part, byte dice)
{
  if (isHeadSegment(part) || isLegSegment(part))
  {
    return MAX_HEAD_LEG_RANGE.isHit(dice);
  }
  else
  {
    return MAX_BODY_RANGE.isHit(dice);
  }
}

}

}
