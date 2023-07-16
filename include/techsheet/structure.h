#pragma once
#include "IncomingDamage.h"
#include "scalar_defs.h"
#include "structure_static.h"
#include "types.h"

#include <algorithm>
#include <array>
#include <optional>

namespace techsheet
{

struct SegmentHealth
{
  health max{ 0 };
  health current{ 0 };
  health staging{ 0 };


  void reset() { current = staging = max; }
  void init(health maxh) { current = staging = max = maxh; }

  // Applies damage down to zero, returns damage remaining if health has become zero
  IncomingDamage consumeDamage(IncomingDamage dmg)
  {
    auto& health = dmg.staging ? staging : current;
    damage dealt = damage::min_of({ dmg.dmg, damage(health.value) });
    health.value -= dealt.value;

    if (!dmg.staging)
    {
      staging = health;
    }

    return dmg.reduce(dealt);
  }

  void unstage()
  {
    staging = current;
  }

  constexpr bool destroyed() const
  {
    return current == 0;
  }

  constexpr void destroy(bool staged = false)
  {
    if (staged)
    {
      staging = health{ 0 };
    }
    else
    {
      current = staging = health{ 0 };
    }
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

  template<typename THealth>
  void setArmor(const ArmorHealth<THealth>& values)
  {
    for (byte i = 0; i < Armor_count; ++i)
    {
      armorHealth[i].init((health)values[i]);
    }
  }

  template<typename THealth>
  void setInternal(const InternalHealth<THealth>& values)
  {
    for (byte i = 0; i < Internal_count; ++i)
    {
      internalHealth[i].init((health)values[i]);
    }
  }

  void setInitialArmor(Armor position, health value)
  {
    (*this)[position].init(value);
  }

  /*
  * Forget any staged damage
  */
  void unstage()
  {
    const auto unstage = [](SegmentHealth& h) { h.unstage(); };
    std::for_each(armorHealth.begin(), armorHealth.end(), unstage);
    std::for_each(internalHealth.begin(), internalHealth.end(), unstage);
  }

  void reset()
  {
    const auto reset = [](SegmentHealth& h) { h.reset(); };
    std::for_each(armorHealth.begin(), armorHealth.end(), reset);
    std::for_each(internalHealth.begin(), internalHealth.end(), reset);
  }

  DamageResult receiveDamage(IncomingDamage dmg)
  {
    auto& armorStatus = armorHealth[to_underlying(dmg.target)];

    if (!armorStatus.destroyed())
    {
      dmg = armorStatus.consumeDamage(dmg);
    }

    DamageResult res;

    if (dmg.dmg == 0)
    {
      return res;
    }

    const auto handleNext = [&res, this](Internal tgt, IncomingDamage dmg)
    {
      auto nextSeg = nextSegment(tgt);
      if (!nextSeg.has_value())
      {
        res.mechDestroyed = true;
      }
      else
      {
        res.mergeIn(receiveDamage(dmg.retarget(nextSeg.value())));
      }
    };

    Internal targetSegment = toInternal(dmg.target);

    auto& internalStatus = internalHealth[to_underlying(targetSegment)];
    if (!internalStatus.destroyed())
    {
      dmg = internalStatus.consumeDamage(dmg);

      if (isFatalSegment(targetSegment) && internalStatus.destroyed())
      {
        res.mechDestroyed = true;
      }
      else if (dmg.dmg == 0)
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
  struct PrintDamage { const StructureManager& parent; };
  PrintDamage doPrintDamage() const { return{ *this }; }
  struct PrintStatusBig { const StructureManager& parent; };
  PrintStatusBig doPrintStatusBig() const { return{ *this }; }
};


static_assert(Armor::CT == static_cast<Armor>(Internal::CT), "Mismatch in structure defs");
static_assert(toInternal(Armor::CTR) == Internal::CT, "Mismatch in armor to internal conversion");
static_assert(toInternal(Armor::LTR) == Internal::LT, "Mismatch in armor to internal conversion");
static_assert(nextSegment(Internal::LA).value() == Internal::LT, "Mismatch in damage transfer logic");
static_assert(nextSegment(Internal::RT).value() == Internal::CT, "Mismatch in damage transfer logic");
}
