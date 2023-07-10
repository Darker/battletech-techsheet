#pragma once
#include "structure.h"

#include <iostream>

std::ostream& operator <<(std::ostream& output, techsheet::DamageResult res)
{
  output << "DamageResult{ ";
  if (res.criticalHit)
  {
    output << "criticalHit=" << internalName(res.criticalSegment) << " ";
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

std::ostream& operator <<(std::ostream& output, techsheet::health h)
{
  output << (short)h.value;
  return output;
}

std::ostream& operator <<(std::ostream& output, techsheet::SegmentHealth health)
{
  output << health.current << "/" << health.max;
  return output;
}

std::ostream& operator <<(std::ostream& output, techsheet::StructureManager::PrintDamage print)
{
  const auto& m = print.parent;
  output << "BattleMech damage:\n";
  for (const auto segName : techsheet::ArmorAll)
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