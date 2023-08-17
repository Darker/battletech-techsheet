#include "MtfParser.h"
#include "name_conversions.h"
#include "parse_exceptions.h"
#include "weapon_lookup.h"

#include <techsheet/string_view_util.h>

#include <istream>
#include <string>

using namespace techsheet;

namespace mtfparser
{

constexpr std::array Internal_full_names{ "head", "left arm", "left torso", "center torso", "right torso", "right arm", "left leg", "right leg" };
constexpr auto Internal_getValueFromFull = enumValueLookup<Internal, Internal::NUM_SEGMENTS, &Internal_full_names>;

template <typename t_strong_num>
t_strong_num parse_num(const std::string& str)
{
  int value = std::stoi(str);
  if (value > t_strong_num::max_base_value)
  {
    throw std::range_error("Value " + str + " out of range, max is " + std::to_string((int)t_strong_num::max_base_value));
  }
  return t_strong_num::forced_cast(value);
}


std::pair<Component, std::optional<Weapon>> parseComponent(std::string name)
{
  name = str::tolower(name);

  Component result;
  result.locations = { 1 };
  if (name == "jump jet")
  {
    result.jump = jump_power{ 1 };
    result.name = "JUMP_JET";
  }
  else if (name == "heat sink")
  {
    result.heat_removed = heat{ 1 };
    result.name = "HEATSINK";
  }
  else if (specialFromName(name).has_value())
  {
    result.specType = specialFromName(name).value();
    result.name = "SPECIAL";
  }
  // everything else is a weapon
  else
  {
    return weaponComponentFromName(name);
  }
  return { result, std::nullopt };
}

std::string getline_stripped(std::istream& input, int& it)
{
  std::string ret;
  std::getline(input, ret);
  it++;
  if (ret.empty())
    return ret;
  ret.erase(std::remove(std::begin(ret), std::end(ret), '\r'), std::end(ret));
  return ret;
}

techsheet::Mech MtfParser::parse(std::istream& input)
{
  Mech mech;

  int linenum = 0;

  const std::string version_read = getline_stripped(input, linenum);
  // first line is version
  const std::string version_expected = "Version:1.0";
  if (version_read != version_expected)
  {
    throw std::runtime_error("Unexpected version first line: '" + version_read + "', expected: '" + version_expected + "' (" + std::to_string(version_read.size()) + " chars, expected " + std::to_string(version_expected.size()) + ").");
  }
  // next two lines are mech name
  mech.name = getline_stripped(input, linenum) + "-" + getline_stripped(input, linenum);

  while (!input.eof())
  {
    const std::string line = getline_stripped(input, linenum);
    if (line.empty())
      continue;

    const auto commaPos = line.find(":");
    if (commaPos == std::string::npos)
    {
      throw std::runtime_error("Cannot parse expression '" + line + "' at line " + std::to_string(linenum));
    }

    const auto valueName = str::tolower(line.substr(0, commaPos));
    //const auto valueName = line.substr(0, commaPos);
    const auto valueStr = line.substr(commaPos + 1);
    if (valueName == "mass")
    {
      mech.wgt = mass{ static_cast<mass::base_type>(std::stoi(valueStr)) };
      mech.structure.setInternal(defaultInternalHealth(mech.wgt));
    }
    else if (valueName == "engine")
    {
      std::string strCount = valueStr;
      if (valueStr.find(" ") != std::string::npos)
      {
        strCount = strCount.substr(0, valueStr.find(" "));
      }
      else
      {
        throw std::runtime_error("Cannot parse engine rating.");
      }

      mech.engineRating = static_cast<unsigned short>(std::stoi(strCount));
    }
    else if (valueName == "heat sinks")
    {
      std::string strCount = valueStr;
      if (valueStr.find(" ") != std::string::npos)
      {
        strCount = strCount.substr(0, valueStr.find(" "));
      }

      if (mech.engineRating < 10)
      {
        throw std::runtime_error("Invalid engine rating: " + std::to_string(mech.engineRating));
      }

      if (str::endswith(str::tolower(valueStr), "double"))
      {
        mech.doubleHeatSinks = true;
      }

      mech.internalHeatSinks = heat::forced_cast(mech.engineHeatSinkCount());
    }
    else if (str::endswith(valueName, " armor"))
    {
      std::string armorName = line.substr(0, line.find(" "));
      const auto knownArmorName = translateSegmentName(armorName);

      const auto armorId = Armor_getValue(knownArmorName);
      if (armorId.has_value())
      {
        mech.structure[armorId.value()].init(parse_num<health>(valueStr));
      }
      else
      {
        throw std::runtime_error("Cannot parse armor name: " + armorName);
      }
    }
    else if (valueName == "weapons")
    {
      while (!input.eof())
      {
        const std::string weapon_data = getline_stripped(input, linenum);
        if (str::trim_copy(weapon_data).empty())
          break;
      }
    }
    else if (Internal_getValueFromFull(valueName).has_value())
    {
      Internal targetPart = Internal_getValueFromFull(valueName).value();
      byte skipLines = 0;
      byte position = 0;
      // load all components
      while (!input.eof())
      {
        const std::string component_data = getline_stripped(input, linenum);
        if (str::trim_copy(component_data).empty())
          break;
        if (skipLines > 0)
        {
          --skipLines;
          continue;
        }
        if (component_data == "-Empty-")
        {
          ++position;
          continue;
        }
        auto lineComp = parseComponent(component_data);
        lineComp.first.locations = lineComp.first.locations.offset(position);
        lineComp.first.position = targetPart;

        if (!crit::rangeForSegment(targetPart).containsIncl(lineComp.first.locations))
        {
          throw CritLocationOutOfBounds(component_data, valueName, lineComp.first.locations, linenum);
        }

        // verify there is no overlap
        for (const auto& existingComp: mech.componentsAt(targetPart))
        {
          if (lineComp.first.locations.overlaps(existingComp.locations))
          {
            throw CritLocationOverlap(component_data, std::string{ existingComp.name }, valueName, lineComp.first.locations, linenum);
          }
        }

        mech.addComponent(lineComp);
        
        skipLines = lineComp.first.locations.slotSize() - 1;
        position += lineComp.first.locations.slotSize();
      }
    }
  }
  return mech;
}

}

