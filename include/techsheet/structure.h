#pragma once
#include "scalar_defs.h"
#include "structure_static.h"
#include "types.h"

#include <array>
#include <optional>

namespace techsheet
{

struct SegmentHealth
{
  health max{0};
  health current{0};

  void reset() { current = max; }
  void init(health maxh) { current = max = maxh; }

  // Applies damage down to zero, returns damage remaining if health has become zero
  damage consumeDamage(damage dmg)
  {
    damage dealt = damage::min_of({ dmg, damage(current.value) });
    current.value -= dealt.value;
    return dmg - dealt;
  }

  constexpr bool destroyed() const
  {
    return current == 0;
  }

  constexpr bool damaged() const
  {
    return current < max;
  }
};

struct DamageResult
{
  bool criticalHit = false;
  Internal criticalSegment = Internal::NUM_SEGMENTS;
  bool mechDestroyed = false;
  bool partDestroyed = false;

  void mergeIn(DamageResult other)
  {
    if (!criticalHit && other.criticalHit)
    {
      criticalHit = true;
      criticalSegment = other.criticalSegment;
    }
    mechDestroyed = mechDestroyed || other.mechDestroyed;
    partDestroyed = partDestroyed || other.partDestroyed;
  }
};

struct StructureManager
{
  std::array<SegmentHealth, Armor_count> armorHealth;
  std::array<SegmentHealth, Internal_count> internalHealth;

  void setArmor(const std::array<byte, Armor_count>& values)
  {
    for (byte i = 0; i < Armor_count; ++i)
    {
      armorHealth[i].init((health)values[i]);
    }
  }

  void setInternal(const std::array<byte, Armor_count>& values)
  {
    for (byte i = 0; i < Internal_count; ++i)
    {
      internalHealth[i].init((health)values[i]);
    }
  }

  DamageResult receiveDamage(Armor segment, damage dmg, bool rear = false)
  {
    // TODO: warning? Rear should be always damaged from the rear
    rear = rear || isRearSegment(segment);
    if (rear)
    {
      segment = toRear(segment);
    }

    auto& armorStatus = armorHealth[to_underlying(segment)];

    if (!armorStatus.destroyed())
    {
      dmg = armorStatus.consumeDamage(dmg);
    }

    DamageResult res;

    if (dmg == 0)
    {
      return res;
    }

    const auto handleNext = [rear, &res, this](Internal tgt, damage dmg)
    {
      auto nextSeg = nextSegment(tgt);
      if (!nextSeg.has_value())
      {
        res.mechDestroyed = true;
      }
      else
      {
        res.mergeIn(receiveDamage(toArmor(nextSeg.value(), rear), dmg, rear));
      }
    };

    Internal targetSegment = toInternal(segment);

    auto& internalStatus = internalHealth[to_underlying(targetSegment)];
    if (!internalStatus.destroyed())
    {
      dmg = internalStatus.consumeDamage(dmg);

      if (isFatalSegment(targetSegment) && internalStatus.destroyed())
      {
        res.mechDestroyed = true;
      }
      else if (dmg == 0)
      {
        res.criticalHit = true;
        res.criticalSegment = targetSegment;
      }
      else
      {
        res.partDestroyed = true;
        handleNext(targetSegment, dmg);
      }
    }
    else
    {
      handleNext(targetSegment, dmg);
    }
    return res;
  }

  const SegmentHealth& operator[](Internal segment) const
  {
    return internalHealth[static_cast<size_t>(segment)];
  }
  SegmentHealth& operator[](Internal segment)
  {
    return internalHealth[static_cast<size_t>(segment)];
  }
  const SegmentHealth& operator[](Armor segment) const
  {
    return armorHealth[static_cast<size_t>(segment)];
  }
  SegmentHealth& operator[](Armor segment)
  {
    return armorHealth[static_cast<size_t>(segment)];
  }

  // used for pretty print operators as a template/overload flag
  struct PrintDamage { StructureManager& parent; };
  PrintDamage printDamage{ *this };
};


static_assert(Armor::CT == static_cast<Armor>(Internal::CT), "Mismatch in structure defs");
static_assert(toInternal(Armor::CTR) == Internal::CT, "Mismatch in armor to internal conversion");
static_assert(toInternal(Armor::LTR) == Internal::LT, "Mismatch in armor to internal conversion");
static_assert(nextSegment(Internal::LA).value() == Internal::LT, "Mismatch in damage transfer logic");
static_assert(nextSegment(Internal::RT).value() == Internal::CT, "Mismatch in damage transfer logic");
}
