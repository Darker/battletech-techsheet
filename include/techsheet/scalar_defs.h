#pragma once
#include "NumberIsh.h"
#include "types.h"

namespace techsheet
{

struct range : NumberIsh<byte, range, CalcOptions::SELF>
{
  using SelfType::NumberIsh;
};

struct damage : NumberIsh<byte, damage, CalcOptions::SELF, CalcOptions::UNDERLYING_TO_SELF, CalcOption_all_to_self>
{
  using SelfType::NumberIsh;
};

struct heat : NumberIsh<byte, heat, CalcOptions::SELF>
{
  using SelfType::NumberIsh;
};

struct health : NumberIsh<byte, health, CalcOptions::SELF, CalcOptions::NONE, CalcOption_all_to_self>
{
  using SelfType::NumberIsh;
};

constexpr health no_health = health{ 0 };

}