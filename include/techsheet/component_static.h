#pragma once
#include "template_defs.h"
#include "types.h"

#include <array>

namespace techsheet
{
enum class SpecialComponent : byte
{
  NOT_SPECIAL,
  LIFE_SUPPORT,
  SENSORS,
  COCKPIT,
  GYRO,
  ENGINE,
  ACTUATOR_BODY, // shoulder/hip
  ACTUATOR_UP,
  ACTUATOR_LOW, // knee/elbow
  ACTUATOR_END, // hand/foot
  NO_SPECIAL_TYPES
};
static constexpr std::array SpecialComponent_names =
{ "NOT_SPECIAL", "LIFE_SUPPORT", "SENSORS", "COCKPIT",
  "GYRO", "ENGINE", "ACTUATOR_BODY", "ACTUATOR_UP", "ACTUATOR_LOW",
  "ACTUATOR_END"
};

static_assert(
  SpecialComponent_names.size() == to_underlying(SpecialComponent::NO_SPECIAL_TYPES),
  "If you add special component, add it to the names too."
);
constexpr auto SpecialComponent_getName 
  = enumNameLookup<SpecialComponent, SpecialComponent::NO_SPECIAL_TYPES, &SpecialComponent_names>;
constexpr auto SpecialComponent_getValue
  = enumValueLookup<SpecialComponent, SpecialComponent::NO_SPECIAL_TYPES, &SpecialComponent_names>;
constexpr auto SpecialComponent_getValueNoOpt
  = enumValueLookupNoOpt<SpecialComponent, SpecialComponent::NO_SPECIAL_TYPES, &SpecialComponent_names>;

}
