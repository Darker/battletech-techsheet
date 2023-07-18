#pragma once
#include "Component.h"
#include "component_filters.h"
#include "critical_hits.h"
#include "fixed_str.h"
#include "id_defs.h"
#include "structure.h"
#include "Weapon.h"

#include "iterators/filtered_collection.h"

#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

namespace techsheet
{

using mech_name = fixed_str<MAX_LEN_MECH_NAME>;

struct Mech
{
  mech_name name;
  StructureManager structure;
  heat currentHeat{ 0 };
  heat internalHeatSinks{ 0 };
  bool doubleHeatSinks = false;
  unsigned short engineRating = 0;
  mass wgt{ 0 };

  std::vector<Component> components;
  std::vector<Weapon> weapons;

  Component INVALID_COMPONENT = Component::createInvalid();
  Weapon INVALID_WEAPON{};

  void addComponent(Component c)
  {
    c.id = componentId.next();
    components.push_back(c);
  }

  void addComponent(Component c, Weapon w)
  {
    c.id = w.component = componentId.next();
    c.isWeapon = true;
    components.push_back(c);
    weapons.push_back(w);
  }

  void addComponent(std::pair<Component, std::optional<Weapon>> p)
  {
    if (p.second.has_value())
    {
      return addComponent(p.first, p.second.value());
    }
    else
    {
      return addComponent(p.first);
    }
  }

  Component& lookupComponent(component_id id)
  {
    for (auto& comp : components)
    {
      if (comp.id == id)
      {
        return comp;
      }
    }
    return INVALID_COMPONENT;
  }
  const Component& lookupComponent(component_id id) const
  {
    return std::as_const(const_cast<Mech*>(this)->lookupComponent(id));
  }
  const Weapon& lookupWeapon(component_id id) const
  {
    for (const auto& w : weapons)
    {
      if (w.component == id)
      {
        return w;
      }
    }
    return INVALID_WEAPON;
  }


  void init(InternalHealth<byte> ih, ArmorHealth<byte> ah)
  {
    structure.setArmor(ah);
    structure.setInternal(ih);
    init();
  }

  void init()
  {
    for (auto& comp : components)
    {
      comp.reset();
    }
  }

  byte engineHeatSinkCount() const
  {
    return static_cast<byte>(std::ceil(engineRating / 25.0f));
  }

#pragma region component filters
  auto workingComponents()
  {
    return make_filtered(components, &pred::is_usable);
  }

  auto validHeatsinks() const
  {
    return make_filtered(components, &pred::is_heatsink, &pred::is_usable);
  }

  auto validHeatsinks()
  {
    return make_filtered(components, &pred::is_heatsink, &pred::is_usable);
  }
  auto pendingComponents()
  {
    return make_filtered(components, &pred::is_pending_destruction);
  }
  auto componentsAt(Internal segment)
  {
    return make_filtered(components, segment, &pred::is_part);
  }
  auto componentsAt(Internal segment) const
  {
    return make_filtered(components, segment, &pred::is_part);
  }
  byte countSpecialHits(SpecialComponent part) const
  {
    byte count = 0;
    for (const auto& comp : make_filtered(components, part, &pred::is_special_hit))
    {
      count += comp.specialHits;
    }
    return count;
  }

  heat heatSinkCount() const
  {
    heat power = internalHeatSinks;
    for (const auto& comp : validHeatsinks())
    {
      power += comp.heat_removed;
    }
    return power;
  }

  heat heatSinkPower() const
  {
    heat power = heatSinkCount();
    return doubleHeatSinks ? heat::forced_cast(2 * power.value) : power;
  }
#pragma endregion

  DamageResult processDamage(IncomingDamage dmg)
  {
    if (!dmg.staging)
    {
      DamageResult result = structure.receiveDamage(dmg);

      if (result.partDestroyed)
      {
        // remove armor from destroyed parts
        for (const auto part : Internal_values)
        {
          if (structure[part].destroyed())
          {
            structure[toArmor(part)].destroy();
            structure[toArmor(part, true)].destroy();
          }
        }
        // destroy arms for side torsos
        if (structure[Internal::RT].destroyed())
        {
          structure[Armor::RA].destroy();
          structure[Internal::RA].destroy();
        }
        if (structure[Internal::LT].destroyed())
        {
          structure[Armor::LA].destroy();
          structure[Internal::LA].destroy();
        }
      }

      for (auto& c : workingComponents())
      {
        if (structure[c.position].destroyed())
        {
          c.status = Component::Status::LAST_TURN;
        }
      }
      return result;
    }
    return DamageResult{};
  }

  /*
  * Finds what component would be hit and if it is a special hit.
  * The critPos should directly be the dice number, starting at 1 ending at 6 or 12
  * \param execute should be set to false if you want the info but no effect on Mech'
  */
  CritRollResult receiveCrit(Internal segment, byte critPos, bool execute)
  {
    if (!crit::isValidRoll(segment, critPos))
    {
      return crit::INVALID_ROLL;
    }
    while (true)
    {
      byte viableTargets = 0;
      for (auto& comp : componentsAt(segment))
      {
        if (comp.isHealthy())
        {
          viableTargets++;
          if (comp.locations.isHit(critPos))
          {
            if (execute)
              comp.status = Component::Status::LAST_TURN;

            CritRollResult result;
            result.destroyedCmp = comp.id;
            if (comp.isSpecial())
            {
              result.specialHit = comp.specType;
              if (execute)
                comp.specialHits++;
            }
            return result;
          }
        }
      }
      // if viable targets were available and none were found, roll again
      if (viableTargets > 0)
      {
        return crit::ROLL_AGAIN;
      }
      // if no targets were found, the roll hits the next body part
      else
      {
        auto s = nextSegment(segment);
        if (s.has_value())
        {
          segment = s.value();
        }
        else
        {
          // Nothing can hit and no next segment? Something is wrong.
          return crit::INVALID_ROLL;
        }
      }
    }
  }
  
  std::vector<CritRollOption> getCritOptions(Internal segment) const
  {
    std::vector<CritRollOption> result;
    result.reserve(6);
    for (const auto& c : componentsAt(segment))
    {
      if(c.isHealthy())
        result.push_back({ c.locations, c.id });
    }
    return result;
  }

  /*
  * Marks any pending components as destroyed, to be used at the end of turn.
  * Returns the number of components destroyed
  */
  byte destroyPendingComponents()
  {
    byte destroyed = 0;
    for (auto& c : pendingComponents())
    {
      c.status = Component::Status::DESTROYED;
      ++destroyed;
    }
    return destroyed;
  }

  /*
  * Cools down the mech 
  */
  heat reduceHeat()
  {
    heat orig = currentHeat;
    currentHeat -= heatSinkPower();
    return orig - currentHeat;
  }
private:
  component_id componentId { 0 };
};

}
