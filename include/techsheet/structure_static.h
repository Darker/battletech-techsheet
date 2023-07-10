#pragma once
#include "scalar_defs.h"
#include "template_defs.h"
#include "types.h"

#include <array>
#include <optional>

namespace techsheet
{
enum class Armor : byte
{
  HEAD,
  LA,
  LT,
  CT,
  RT,
  RA,
  LL,
  RL,
  // rear segments
  LTR,
  CTR,
  RTR,
  NUM_SEGMENTS
};

enum class Internal : byte
{
  HEAD,
  LA,
  LT,
  CT,
  RT,
  RA,
  LL,
  RL,
  NUM_SEGMENTS
};

constexpr auto ArmorAll = EnumValues<Armor, Armor::NUM_SEGMENTS>;
static constexpr auto Armor_count = to_underlying(Armor::NUM_SEGMENTS);
constexpr auto InternalAll = EnumValues<Armor, Armor::NUM_SEGMENTS>;
static constexpr auto Internal_count = to_underlying(Internal::NUM_SEGMENTS);

inline constexpr const char* armorName(Armor a)
{
  switch (a)
  {
  case Armor::HEAD: return "HEAD";
  case Armor::LA: return "LA";
  case Armor::LT: return "LT";
  case Armor::CT: return "CT";
  case Armor::RT: return "RT";
  case Armor::RA: return "RA";
  case Armor::LL: return "LL";
  case Armor::RL: return "RL";
  case Armor::LTR: return "LTR";
  case Armor::CTR: return "CTR";
  case Armor::RTR: return "RTR";
  case Armor::NUM_SEGMENTS: return "invalid-segment";
  }
  return "enum-error";
}

static constexpr Armor toRear(Armor segment)
{
  switch (segment)
  {
  case Armor::CT: return Armor::CTR;
  case Armor::RT: return Armor::RTR;
  case Armor::LT: return Armor::LTR;
  }
  return segment;
}

static constexpr Armor toArmor(Internal const segment, bool rear = false)
{
  if (segment == Internal::NUM_SEGMENTS)
  {
    return Armor::NUM_SEGMENTS;
  }

  const auto res = static_cast<Armor>(segment);
  return rear ? toRear(res) : res;
}

constexpr bool isRearSegment(Armor segment)
{
  return segment == Armor::CTR || segment == Armor::LTR || segment == Armor::RTR;
}

constexpr bool isTorsoSegment(Internal segment)
{
  return segment == Internal::CT || segment == Internal::LT || segment == Internal::RT;
}

constexpr bool isFatalSegment(Internal segment)
{
  return segment == Internal::CT || segment == Internal::HEAD;
}

static constexpr Internal toInternal(Armor const segment);
constexpr bool isTorsoSegment(Armor segment)
{
  return isTorsoSegment(toInternal(segment));
}

inline constexpr const char* internalName(Internal a)
{
  return armorName(toArmor(a));
}

inline constexpr const char* segmentName(Internal a)
{
  return internalName(a);
}

inline constexpr const char* segmentName(Armor a)
{
  return armorName(a);
}

static constexpr Internal toInternal(Armor const segment)
{
  // subtract from first rear entry to get 0
  constexpr byte armor_rear_start = static_cast<byte>(Armor::RL);
  // add to 0 to get first torso part
  constexpr byte torso_start = static_cast<byte>(Armor::LA);

  constexpr auto calc_offset = armor_rear_start - torso_start;

  if (segment == Armor::NUM_SEGMENTS)
  {
    return Internal::NUM_SEGMENTS;
  }
  if (segment > Armor::LL)
  {
    return static_cast<Internal>(static_cast<byte>(segment) - calc_offset);
  }
  else
  {
    return static_cast<Internal>(segment);
  }
}

static constexpr std::optional<Internal> nextSegment(Internal const segment)
{
  switch (segment)
  {
  case Internal::HEAD: [[fallthrough]];
  case Internal::CT: return std::nullopt;
  case Internal::RT: [[fallthrough]];
  case Internal::LT: return Internal::CT;
  case Internal::RL: return Internal::RT;
  case Internal::LL: return Internal::LT;
  case Internal::RA: return Internal::RT;
  case Internal::LA: return Internal::LT;
    // TODO: exception?
  case Internal::NUM_SEGMENTS: return std::nullopt;
  }
  return std::nullopt;
};

}
