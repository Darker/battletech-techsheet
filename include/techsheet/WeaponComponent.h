#pragma once
#include "Weapon.h"
#include "Component.h"

#include <utility>
#include <optional>

namespace techsheet
{
// Component with an optionally assigned weapon
using WeaponComponent = std::pair<Component, std::optional<Weapon>>;

}
