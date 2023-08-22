#include <techsheet/Mech.h>
#include <string>
#include <stdexcept>


using namespace techsheet;

std::string stringifyComponent(const Mech& mech, const Component& c)
{
  std::string result = "UNKNOWN";
  if (c.isHeatsink())
  {
    result = "Heatsink";
  }
  else if (c.isAmmo())
  {
    result = std::string(Ammo_getName(c.ammoType)) + " ammo";
    if (c.ammo > 0)
    {
      result += " [" + std::to_string((int)c.ammo.value) + " shots]";
    }
  }
  else if (c.isWeapon)
  {
    const auto* w = mech.lookupWeapon(c.id);
    if (w->component == c.id)
    {
      result = w->name.view();
      if (w->isRear)
      {
        result += " (rear)";
      }
      if (w->usesAmmo())
      {
        result += " [" + std::string(Ammo_getName(w->ammoType)) + " ammo]";
      }
    }
    else
    {
      throw std::runtime_error("Invalid weapon for component.");
    }
  }
  else if (c.isSpecial())
  {
    switch (c.specType)
    {
    case SpecialComponent::ACTUATOR_END:
    {
      return isLegSegment(c.position) ? "Foot actuator" : "Hand actuator";
    }
    case SpecialComponent::ACTUATOR_BODY:
    {
      return isLegSegment(c.position) ? "Hip actuator" : "Shoulder actuator";
    }
    default:
    {
      return std::string{ SpecialComponent_getName(c.specType) };
    }
    }
  }
  else
  {
    return std::string{ "Unknown name: " } + std::string{ c.name };
  }
  return result;
}