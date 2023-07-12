#pragma once
#include "Component.h"
#include "component_filters.h"
#include "fixed_str.h"
#include "id_defs.h"
#include "structure.h"
#include "Weapon.h"

#include "iterators/filtered_collection.h"

#include <algorithm>
#include <vector>

namespace techsheet
{

using mech_name = fixed_str<MAD_LEN_MECH_NAME>;

struct Mech
{
  mech_name name;
  StructureManager structure;

  std::vector<Component> components;
  std::vector<Weapon> weapons;

  byte engine_hits = 0;
  byte gyro_hits = 0;
  byte sensor_hits = 0;
  byte life_support_hits = 0;
  byte cockpit_hits = 0;

  void addComponent(Component c)
  {
    c.id = componentId.next();
    components.push_back(c);
  }

  void addComponent(Component c, Weapon w)
  {
    c.id = w.component = componentId.next();
    components.push_back(c);
    weapons.push_back(w);
  }

  void init(InternalHealth<byte> ih, ArmorHealth<byte> ah)
  {
    structure.setArmor(ah);
    structure.setInternal(ih);
    for (auto& comp : components)
    {
      comp.reset();
    }
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
#pragma endregion

  DamageResult processDamage(IncomingDamage dmg)
  {
    if (!dmg.staging)
    {
      DamageResult result = structure.receiveDamage(dmg);
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

  void destroyPendingComponents()
  {
    for (auto& c : pendingComponents())
    {
      c.status = Component::Status::DESTROYED;
    }
  }
private:
  component_id componentId { 0 };
  heat sinkPower{ 0 };
};

}
