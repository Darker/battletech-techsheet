#pragma once
#include "scalar_defs.h"

namespace techsheet
{

struct RangeLimits
{
  constexpr RangeLimits()
    : penaltyRanges{ range{0}, range{0}, range{0}, range{0} }
  {}
  constexpr RangeLimits(range sht, range med, range lng)
    : penaltyRanges{sht, med, lng, range{0}}
  {}
  constexpr RangeLimits(range sht, range med, range lng, range min)
    : penaltyRanges{ sht, med, lng, range{0} }
    , minRange{ min }
  {}
  constexpr RangeLimits(range sht, range med, range lng, range extreme, range min)
    : penaltyRanges{ sht, med, lng, extreme }
    , minRange{ min }
  {}
  template <typename TArray>
  constexpr RangeLimits(const std::array<TArray, 4> ar)
    : penaltyRanges{ range::forced_cast(ar[0]), range::forced_cast(ar[1]), range::forced_cast(ar[2]), range::forced_cast(ar[3]) }
  {}

  constexpr RangeLimits(int sht, int med, int lng, int extreme, int min = 0)
    : penaltyRanges{ range::forced_cast(sht), range::forced_cast(med), range::forced_cast(lng), range::forced_cast(extreme) }
    , minRange{range::forced_cast(min)}
  {}

  enum class Type: byte
  {
    SHORT,
    MEDIUM,
    LONG,
    EXTREME
  };
  // short, med, long, extreme
  std::array<range, 4> penaltyRanges;
  range minRange{ 0 };

#pragma region named getters
  constexpr range& sht() { return penaltyRanges[0]; }
  constexpr range& med() { return penaltyRanges[1]; }
  constexpr range& mid() { return penaltyRanges[1]; }
  constexpr range& lng() { return penaltyRanges[2]; }
  constexpr range& ext() { return penaltyRanges[3]; }
  constexpr range& min() { return minRange; }
  constexpr const range& sht() const { return penaltyRanges[0]; }
  constexpr const range& med() const { return penaltyRanges[1]; }
  constexpr const range& mid() const { return penaltyRanges[1]; }
  constexpr const range& lng() const { return penaltyRanges[2]; }
  constexpr const range& ext() const { return penaltyRanges[3]; }
  constexpr const range& min() const { return minRange; }
#pragma endregion

  /*
  * Returns roll requirement of 255 for impossible rolls (too far)
  */
  constexpr dice_roll getPenalty(range distance, bool allowExtreme = false) const
  {
    if (minRange > 0 && minRange > distance)
    {
      return dice_roll::forced_cast((minRange - distance).value + 1);
    }

    for (byte i = 0; i < penaltyRanges.size(); ++i)
    {
      if (i == 3 && !allowExtreme)
      {
        return dice_roll::impossibleRoll();
      }
      else
      {
        // ???
        return dice_roll::impossibleRoll();
      }
      if (distance <= penaltyRanges[i])
      {
        return dice_roll::forced_cast(2 * i);
      }
    }
    // should not happen
    return dice_roll::impossibleRoll();
  }
};

}
