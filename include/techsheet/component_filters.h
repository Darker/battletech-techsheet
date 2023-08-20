#pragma once
#include "Component.h"
#include "Weapon.h"

namespace techsheet
{

namespace pred
{

constexpr bool is_usable(const Component& c)
{
  return !c.isDestroyed();
}

constexpr bool is_heatsink(const Component& c)
{
  return c.heatRemoved > 0;
}

constexpr bool is_pending_destruction(const Component& c)
{
  return c.status == Component::Status::LAST_TURN;
}

constexpr bool is_special_hit(const Component& c, const SpecialComponent& specialPlace)
{
  return c.specType == specialPlace;
}

constexpr bool is_part(const Component& c, const Internal& bodyPart)
{
  return c.position == bodyPart;
}

constexpr bool is_viable_ammo(const Component& c, const Ammo& ammoType)
{
  return !c.isDestroyed() && c.ammoType == ammoType && c.ammo > 0;
}

}


}