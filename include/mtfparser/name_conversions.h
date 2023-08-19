#pragma once
#include <techsheet/component_static.h>
#include <techsheet/Component.h>
#include <techsheet/Weapon.h>
#include <techsheet/string_view_util.h>

#include <optional>
#include <stdexcept>
#include <string_view>

namespace mtfparser
{
constexpr std::optional<techsheet::SpecialComponent> specialFromName(std::string_view name)
{
  using namespace techsheet;
  if (name == "shoulder" || name == "hip")
  {
    return SpecialComponent::ACTUATOR_BODY;
  }
  else if (str::startswith(name, "upper ") && str::endswith(name, " actuator"))
  {
    return SpecialComponent::ACTUATOR_UP;
  }
  else if (str::startswith(name, "lower ") && str::endswith(name, " actuator"))
  {
    return SpecialComponent::ACTUATOR_LOW;
  }
  else if ((str::startswith(name, "foot ") || str::startswith(name, "hand ")) && str::endswith(name, " actuator"))
  {
    return SpecialComponent::ACTUATOR_END;
  }
  else if (name == "cockpit")
  {
    return SpecialComponent::COCKPIT;
  }
  else if (name == "life support")
  {
    return SpecialComponent::LIFE_SUPPORT;
  }
  else if (name == "sensors")
  {
    return SpecialComponent::SENSORS;
  }
  else if (name == "gyro")
  {
    return SpecialComponent::GYRO;
  }
  else if (name == "fusion engine")
  {
    return SpecialComponent::ENGINE;
  }
  return std::nullopt;
}

}
