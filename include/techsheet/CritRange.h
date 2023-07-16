#pragma once
#include "types.h"

namespace techsheet
{

struct CritRange
{
  constexpr CritRange(byte min_pos, byte max_pos)
    : min{ min_pos < max_pos ? min_pos : max_pos }
    , max{ max_pos > min_pos ? max_pos : min_pos }
  {}
  constexpr CritRange(byte pos)
    : min{ pos }
    , max{ pos }
  {}
  constexpr CritRange()
    : min{ 0 }
    , max{ 0 }
  {}


  byte min = 0;
  byte max = 0;

  constexpr byte slotSize() const
  {
    return max - min + 1;
  }
  constexpr bool isHit(byte roll) const
  {
    return roll >= min && roll <= max;
  }
  constexpr bool overlaps(CritRange other) const
  {
    return min <= other.max && max >= other.min;
  }
  // Inclusive means edges may be the same values (any range contains itself)
  constexpr bool containsIncl(CritRange other) const
  {
    return min <= other.min && max >= other.max;
  }
  constexpr bool nextTo(CritRange other) const
  {
    if (!overlaps(other))
    {
      return max + 1 == other.min || other.max + 1 == min;
    }
    return false;
  }
  constexpr CritRange offset(byte steps) const
  {
    return { static_cast<byte>(min + steps), static_cast<byte>(max + steps) };
  }
};

// overlap checks
static_assert((CritRange{ 1,4 }).overlaps({ 3, 5 }), "Range overlap error");
static_assert((CritRange{ 1,4 }).overlaps({ 1, 4 }), "Range overlap error");
static_assert((CritRange{ 1,4 }).overlaps({ 4, 8 }), "Range overlap error");
static_assert((CritRange{ 4,8 }).overlaps({ 5, 6 }), "Range overlap error");
static_assert(!(CritRange{ 1,2 }).overlaps({ 3, 4 }), "Range overlap error");
static_assert(!(CritRange{ 3,4 }).overlaps({ 1, 2 }), "Range overlap error");
// containsIncl
static_assert((CritRange{ 1 }).containsIncl({ 1 }), "Range containsIncl error");
static_assert((CritRange{ 1,2 }).containsIncl({ 2 }), "Range containsIncl error");
static_assert((CritRange{ 1,2 }).containsIncl({ 1 }), "Range containsIncl error");
static_assert(!(CritRange{ 1 }).containsIncl({ 1, 2 }), "Range containsIncl error");
static_assert(!(CritRange{ 2 }).containsIncl({ 1, 2 }), "Range containsIncl error");
static_assert(!(CritRange{ 1,4 }).containsIncl({ 3, 5 }), "Range containsIncl error");
static_assert((CritRange{ 1,4 }).containsIncl({ 1, 4 }), "Range containsIncl error");
static_assert(!(CritRange{ 1,4 }).containsIncl({ 4, 8 }), "Range containsIncl error");
static_assert((CritRange{ 4,8 }).containsIncl({ 5, 6 }), "Range containsIncl error");
static_assert(!(CritRange{ 1,2 }).containsIncl({ 3, 4 }), "Range containsIncl error");
static_assert(!(CritRange{ 3,4 }).containsIncl({ 1, 2 }), "Range containsIncl error");
// nextTo checks
static_assert((CritRange{ 2 }).nextTo({ 3 }), "Range nextTo error");
static_assert((CritRange{ 3 }).nextTo({ 2 }), "Range nextTo error");
static_assert((CritRange{ 1,4 }).nextTo({ 5 }), "Range nextTo error");
static_assert((CritRange{ 1,4 }).nextTo({ 5, 8 }), "Range nextTo error");
static_assert(!(CritRange{ 1,4 }).nextTo({ 6, 8 }), "Range nextTo error");
static_assert(!(CritRange{ 2 }).nextTo({ 2 }), "Range nextTo error");
static_assert(!(CritRange{ 0 }).nextTo({ 2 }), "Range nextTo error");

}
