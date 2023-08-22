#pragma once
#include "CritRange.h"
#include "component_static.h"
#include "id_defs.h"
#include "types.h"

namespace techsheet
{

struct CritRollResult final
{
  component_id destroyedCmp{ 0 };
  SpecialComponent specialHit = SpecialComponent::NOT_SPECIAL;
  bool rollAgain = false;

  constexpr bool isValid() const
  {
    return specialHit != SpecialComponent::NO_SPECIAL_TYPES;
  }

  constexpr bool operator==(const CritRollResult& other) const
  {
    return destroyedCmp == other.destroyedCmp
      && specialHit == other.specialHit
      && rollAgain == other.rollAgain;
  }
  constexpr bool operator!=(const CritRollResult& other) const
  {
    return !(*this == other);
  }
};

struct CritRollOption final
{
  CritRange range;
  component_id component{ 0 };
  bool alreadyDestroyed = false;
};

namespace crit
{
constexpr CritRollResult ROLL_AGAIN{ component_id{0}, SpecialComponent::NOT_SPECIAL, true };
constexpr CritRollResult INVALID_ROLL{ component_id{0}, SpecialComponent::NO_SPECIAL_TYPES, true };

constexpr CritRange MAX_HEAD_LEG_RANGE{ 1, 6 };
constexpr CritRange MAX_BODY_RANGE{ 1, 12 };

constexpr CritRange rangeForSegment(Internal part)
{
  if (isHeadSegment(part) || isLegSegment(part))
  {
    return MAX_HEAD_LEG_RANGE;
  }
  else
  {
    return MAX_BODY_RANGE;
  }
}

constexpr bool isValidRoll(Internal part, byte dice)
{
  return rangeForSegment(part).isHit(dice);
}

static_assert(isValidRoll(Internal::HEAD, 6), "crit roll calculation error");
static_assert(!isValidRoll(Internal::HEAD, 0), "crit roll calculation error");
static_assert(!isValidRoll(Internal::HEAD, 7), "crit roll calculation error");
static_assert(isValidRoll(Internal::HEAD, 1), "crit roll calculation error");
static_assert(!isValidRoll(Internal::CT, 0), "crit roll calculation error");
static_assert(isValidRoll(Internal::CT, 10), "crit roll calculation error");
static_assert(isValidRoll(Internal::CT, 12), "crit roll calculation error");
static_assert(isValidRoll(Internal::CT, 1), "crit roll calculation error");
static_assert(!isValidRoll(Internal::CT, 13), "crit roll calculation error");
}

}
