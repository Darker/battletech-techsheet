#pragma once
#include "CritRange.h"
#include "fixed_str.h"
#include "structure.h"
#include "IncomingDamage.h"

#include <iomanip>
#include <iostream>

template <size_t str_max_size>
inline std::ostream& operator<<(std::ostream& output, const techsheet::fixed_str<str_max_size>& str)
{
  output << str.view();
  return output;
}

inline std::ostream& operator <<(std::ostream& output, techsheet::DamageResult res)
{
  output << "DamageResult{ ";
  if (res.criticalHit)
  {
    output << "criticalHit=" << techsheet::Internal_getName(res.criticalSegment) << " ";
  }
  if (res.partDestroyed)
  {
    output << "partDestroyed ";
  }
  if (res.mechDestroyed)
  {
    output << "mechDestroyed ";
  }
  output << " }";
  return output;
}

inline std::ostream& operator <<(std::ostream& output, techsheet::CritRange::PrintAsRolls r)
{
  output << std::setfill(' ') << std::setw(2) << (short)r.range.min
    << " to "
    << std::setfill(' ') << std::setw(2) << (short)r.range.max;
  return output;
}

inline std::ostream& operator <<(std::ostream& output, const techsheet::IncomingDamage& dmg)
{
  const char* rear_txt = dmg.rear ? " (rear)" : "";
  output << "Damage: " << (short)dmg.dmg.value << " to " << techsheet::Armor_getName(dmg.target) << rear_txt << "\n";
  return output;
}

inline std::ostream& operator <<(std::ostream& output, techsheet::health h)
{
  output << (short)h.value;
  return output;
}

inline std::ostream& operator <<(std::ostream& output, techsheet::SegmentHealth health)
{
  output << health.current << "/" << health.max;
  return output;
}

inline std::ostream& operator <<(std::ostream& output, techsheet::Armor segment)
{
  output << techsheet::Armor_getName(segment);
  return output;
}

inline std::ostream& operator <<(std::ostream& output, techsheet::Internal segment)
{
  output << techsheet::Internal_getName(segment);
  return output;
}

inline std::istream& operator>>(std::istream& input, techsheet::Internal& segment)
{
  std::string name;
  input >> name;
  const auto v = techsheet::Internal_getValue(name);
  if (v.has_value())
  {
    segment = v.value();
  }
  else
  {
    segment = techsheet::Internal::NUM_SEGMENTS;
  }

  return input;
}

inline std::istream& operator>>(std::istream& input, techsheet::Armor& segment)
{
  std::string name;
  input >> name;
  const auto v = techsheet::Armor_getValue(name);
  if (v.has_value())
  {
    segment = v.value();
  }
  else
  {
    segment = techsheet::Armor::NUM_SEGMENTS;
  }

  return input;
}

namespace print_helpers
{

struct HPStatus
{
  HPStatus(techsheet::Armor part, const techsheet::StructureManager& str)
    : partName{techsheet::segmentName(part)}
    , value{str[part].current}
    , maxValue{ str[part].max }
    , name{'A'}
  { }
  HPStatus(techsheet::Internal part, const techsheet::StructureManager& str)
    : partName{ techsheet::segmentName(part) }
    , value{ str[part].current }
    , maxValue{ str[part].max }
    , name{ 'S' }
  {}
  std::string partName;
  techsheet::health value;
  techsheet::health maxValue;
  char name = 'A';
};

}

inline std::ostream& operator <<(std::ostream& output, print_helpers::HPStatus print)
{
  output << print.name << ":" << std::setfill(' ') << std::setw(2) << print.value;
  output << " / " << std::setfill(' ') << std::setw(2) << print.maxValue;
  return output;
}

inline std::ostream& operator <<(std::ostream& output, techsheet::StructureManager::PrintStatusBig print)
{
  using namespace techsheet;

  const auto& m = print.parent;
  output << "BattleMech status:\n";

  const auto HARM = print_helpers::HPStatus(Armor::HEAD, m);
  const auto HSTR = print_helpers::HPStatus(Internal::HEAD, m);
  const auto CTA = print_helpers::HPStatus(Armor::CT, m);
  const auto CTS = print_helpers::HPStatus(Internal::CT, m);
  auto LA = print_helpers::HPStatus(Armor::LA, m);
  auto RA = print_helpers::HPStatus(Armor::RA, m);
  auto LT = print_helpers::HPStatus(Armor::LT, m);
  auto RT = print_helpers::HPStatus(Armor::RT, m);


  std::cout << u8"                ┌───────────┐  \n"
    << u8"                │ " << HARM << u8" |\n"
    << u8"                │ " << HSTR << u8" |\n";
  std::cout << u8"┌───────────┬───┴─────┬─────┴───┬───────────┐  \n";
  std::cout << u8"│ "<<LA<< u8" │" <<LT<<u8"│" << RT << u8"│ " << RA << u8" │  \n";

  LA = print_helpers::HPStatus(Internal::LA, m);
  RA = print_helpers::HPStatus(Internal::RA, m);
  LT = print_helpers::HPStatus(Internal::LT, m);
  RT = print_helpers::HPStatus(Internal::RT, m);
  std::cout << u8"│ " << LA << u8" │" << LT << u8"│" << RT << u8"│ " << RA << u8" │  \n";

  std::cout << u8"└───────────┼─────────┴─────────┼───────────┘  \n";
  std::cout << u8"            │     "<<CTA<<u8"     │ \n";
  std::cout << u8"            │     "<<CTS<<u8"     │ \n";
  std::cout << u8"          ┌─┴─────────┼─────────┴─┐\n";
  std::cout << u8"          │           │           │\n";
  auto LL = print_helpers::HPStatus(Armor::LL, m);
  auto RL = print_helpers::HPStatus(Armor::RL, m);
  std::cout << u8"          │ " << LL << u8" │ " << RL << u8" │\n";
  LL = print_helpers::HPStatus(Internal::LL, m);
  RL = print_helpers::HPStatus(Internal::RL, m);
  std::cout << u8"          │ " << LL << u8" │ " << RL << u8" │\n";
  std::cout << u8"          │          ┌┴┐          │\n";
  std::cout << u8"          └──────────┘ └──────────┘\n";
  return output;
}

inline std::ostream& operator <<(std::ostream& output, techsheet::StructureManager::PrintDamage print)
{
  const auto& m = print.parent;
  output << "BattleMech damage:\n";
  for (const auto segName : techsheet::Armor_values)
  {
    const auto& status = m[segName];
    if (status.damaged())
    {
      if (!status.destroyed())
      {
        std::cout << "  " << segmentName(segName) << " armor: " << status << "\n";
      }
      else
      {
        const auto intName = toInternal(segName);
        const auto& intStatus = m[intName];
        if (!intStatus.destroyed())
        {
          std::cout << "  " << segmentName(intName) << " health: " << intStatus << "\n";
        }
        else
        {
          std::cout << "  " << segmentName(intName) << " DESTROYED!\n";
        }
      }
    }
  }
  return output;
}