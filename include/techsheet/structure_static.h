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

constexpr auto Armor_values = EnumValues<Armor, Armor::NUM_SEGMENTS>;
static constexpr auto Armor_count = to_underlying(Armor::NUM_SEGMENTS);
constexpr auto Internal_values = EnumValues<Internal, Internal::NUM_SEGMENTS>;
static constexpr auto Internal_count = to_underlying(Internal::NUM_SEGMENTS);

constexpr std::array Armor_names{ "HEAD", "LA", "LT", "CT", "RT", "RA", "LL", "RL", "LTR", "CTR", "RTR" };
constexpr std::array Internal_names{ "HEAD", "LA", "LT", "CT", "RT", "RA", "LL", "RL" };

constexpr auto Armor_getName = enumNameLookup<Armor, Armor::NUM_SEGMENTS, &Armor_names>;
constexpr auto Armor_getValue = enumValueLookup<Armor, Armor::NUM_SEGMENTS, &Armor_names>;
constexpr auto Internal_getName = enumNameLookup<Internal, Internal::NUM_SEGMENTS, &Internal_names>;
constexpr auto Internal_getValue = enumValueLookup<Internal, Internal::NUM_SEGMENTS, &Internal_names>;

/*
* Hand made lookup for alternative segment shortcuts that still unambiguosly mean something
* in our segment definitions.
*/
constexpr std::string_view translateSegmentName(std::string_view externalName)
{
  if (externalName == "HD")
  {
    return "HEAD";
  }
  // "rear torso left"
  else if (externalName == "RTL")
  {
    return "LTR";
  }
  // "rear torso center"
  else if (externalName == "RTC")
  {
    return "CTR";
  }
  return externalName;
}

static constexpr Armor toRear(Armor segment)
{
  switch (segment)
  {
  case Armor::CT: return Armor::CTR;
  case Armor::RT: return Armor::RTR;
  case Armor::LT: return Armor::LTR;
  default: return segment;
  }
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

constexpr bool isHeadSegment(Armor segment)
{
  return segment == Armor::HEAD;
}

constexpr bool isHeadSegment(Internal segment)
{
  return segment == Internal::HEAD;
}

constexpr bool isLegSegment(Internal segment)
{
  return segment == Internal::LL ||
         segment == Internal::RL;
}

constexpr bool isLegSegment(Armor segment)
{
  return isLegSegment(toInternal(segment));
}

constexpr bool isArmSegment(Internal segment)
{
  return segment == Internal::LA ||
    segment == Internal::RA;
}

constexpr bool isArmSegment(Armor segment)
{
  return isArmSegment(toInternal(segment));
}

constexpr bool isLimbSegment(Internal segment)
{
  return isArmSegment(segment) || isLegSegment(segment);
}

constexpr bool isLimbSegment(Armor segment)
{
  return isLimbSegment(toInternal(segment));
}

constexpr bool isAppendageSegment(Internal segment)
{
  return isArmSegment(segment) || isLegSegment(segment) || segment == Internal::HEAD;
}

constexpr bool isAppendageSegment(Armor segment)
{
  return isAppendageSegment(toInternal(segment));
}

constexpr bool isSideTorso(Internal segment)
{
  return segment == Internal::LT || segment == Internal::RT;
}

constexpr bool hasRearArmor(Internal segment)
{
  return isSideTorso(segment) || segment == Internal::CT;
}

inline constexpr std::string_view segmentName(Internal a)
{
  return Internal_getName(a);
}

inline constexpr std::string_view segmentName(Armor a)
{
  return Armor_getName(a);
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
  if (segment > Armor::RL)
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
}


static constexpr byte segmentDistance(Internal a, Internal b)
{
  constexpr std::array dist_matrix{
    // HD,CT,RT,LT,RL,LL,RA,LA
    // HEAD
       0, 1, 2, 2, 3, 3 ,3, 3,
    // CT
       1, 0, 1, 1, 2, 2 ,2, 2,
    // RT
       2, 1, 0, 2, 1, 2 ,1, 2,
    // LT
       2, 1, 2, 0, 2, 1 ,2, 1,
    // RL
       3, 2, 1, 2, 0, 2, 2, 4,
    // LL
       3, 2, 2, 1, 2, 0, 4, 2,
    // RA
       3, 2, 1, 2, 2, 4, 0, 4,
    // LA
       3, 2, 2, 1, 4, 2, 4, 0
  };
  if (to_underlying(a) >= to_underlying(Internal::NUM_SEGMENTS))
  {
    return 0;
  }
  if (to_underlying(b) >= to_underlying(Internal::NUM_SEGMENTS))
  {
    return 0;
  }
  const auto res = dist_matrix[to_underlying(a) * to_underlying(Internal::NUM_SEGMENTS) + to_underlying(b)];
  return static_cast<byte>(res);
}

template<typename THealth, typename = std::enable_if_t<health::is_constructible_from<THealth>>>
using InternalHealth = std::array<THealth, Internal_count>;
template<typename THealth, typename = std::enable_if_t<health::is_constructible_from<THealth>>>
using ArmorHealth = std::array<THealth, Armor_count>;

// internal structure lookup
namespace struct_data
{
constexpr std::array internalStructureLookupData
{
  std::pair{mass{20}, InternalHealth<byte>{3, 3, 5, 6, 5, 3, 4, 4}},
  std::pair{mass{25}, InternalHealth<byte>{3, 4, 6, 8, 6, 4, 6, 6}},
  std::pair{mass{30}, InternalHealth<byte>{3, 5, 7, 10, 7, 5, 7, 7}},
  std::pair{mass{35}, InternalHealth<byte>{3, 6, 8, 11, 8, 6, 8, 8}},
  std::pair{mass{40}, InternalHealth<byte>{3, 6, 10, 12, 10, 6, 10, 10}},
  std::pair{mass{45}, InternalHealth<byte>{3, 7, 11, 14, 11, 7, 11, 11}},
  std::pair{mass{50}, InternalHealth<byte>{3, 8, 12, 16, 12, 8, 12, 12}},
  std::pair{mass{55}, InternalHealth<byte>{3, 9, 13, 18, 13, 9, 13, 13}},
  std::pair{mass{60}, InternalHealth<byte>{3, 10, 14, 20, 14, 10, 14, 14}},
  std::pair{mass{65}, InternalHealth<byte>{3, 10, 15, 21, 15, 10, 15, 15}},
  std::pair{mass{70}, InternalHealth<byte>{3, 11, 15, 22, 15, 11, 15, 15}},
  std::pair{mass{75}, InternalHealth<byte>{3, 12, 16, 23, 16, 12, 16, 16}},
  std::pair{mass{80}, InternalHealth<byte>{3, 13, 17, 25, 17, 13, 17, 17}},
  std::pair{mass{85}, InternalHealth<byte>{3, 14, 18, 27, 18, 14, 18, 18}},
  std::pair{mass{90}, InternalHealth<byte>{3, 15, 19, 29, 19, 15, 19, 19}},
  std::pair{mass{95}, InternalHealth<byte>{3, 16, 20, 30, 20, 16, 20, 20}},
  std::pair{mass{100}, InternalHealth<byte>{3, 17, 21, 31, 21, 17, 21, 21}},
};

}

constexpr InternalHealth<byte> defaultInternalHealth(mass mechMass)
{
  for (const auto& cfg : struct_data::internalStructureLookupData)
  {
    if (cfg.first >= mechMass)
    {
      return cfg.second;
    }
  }
  return struct_data::internalStructureLookupData.back().second;
}

namespace static_test
{

static_assert(toInternal(Armor::LA) == Internal::LA, "Error converting from armor to structure");
static_assert(toInternal(Armor::CTR) == Internal::CT, "Error converting from armor to structure");
static_assert(toInternal(Armor::HEAD) == Internal::HEAD, "Error converting from armor to structure");

static_assert(segmentDistance(Internal::LA, Internal::HEAD) == segmentDistance(Internal::HEAD, Internal::LA), "Segment distance error");
static_assert(segmentDistance(Internal::HEAD, Internal::RL) == 3, "Segment distance error");

}

}
