#pragma once
#include "Component.h"
#include "Weapon.h"

namespace techsheet
{

namespace pred
{

bool is_usable(const Component& c)
{
  return !c.isDestroyed();
}

bool is_heatsink(const Component& c)
{
  return c.heat_removed > 0;
}

bool is_pending_destruction(const Component& c)
{
  return c.status == Component::Status::LAST_TURN;
}

bool is_special_hit(const Component& c, Component::Special specialPlace)
{
  return c.specType == specialPlace;
}

bool is_viable_ammo(const Component& c, Ammo ammoType)
{
  return !c.isDestroyed() && c.ammoType == ammoType && c.ammo > 0;
}

}


}