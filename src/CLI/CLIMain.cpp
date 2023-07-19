#include "string_tools.h"
#include "is_windows.h"

#include <techsheet/Mech.h>
#include <techsheet/std_cout_printing.h>

#include <algorithm>
#include <array>
#include <cctype>
#include <fstream>
#include <locale>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

#ifdef IS_WINDOWS_BUILD
#include <Windows.h>
#endif

using namespace techsheet;

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

std::optional<SpecialComponent> specialFromName(std::string_view name)
{
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

std::pair<Component, std::optional<Weapon>> parseComponent(std::string name)
{
  name = str::tolower(name);

  Component result;
  result.locations = { 1 };
  if (str::contains(name, "laser"))
  {
    Weapon laser;
    laser.name = "LASER";
    if (str::contains(name, "large"))
    {
      result.locations.max++;

      laser.damagePerCluster = damage{ 8 };
      laser.heatCaused = heat{ 8 };
      laser.ranges = std::array{ 5, 10, 5, 20 };
      laser.name = fixed_str{ "L" } + laser.name;
    }
    else if (str::contains(name, "medium"))
    {
      laser.heatCaused = heat{ 3 };
      laser.damagePerCluster = damage{ 5 };
      laser.ranges = std::array{ 3, 6, 9, 12 };
      laser.name = fixed_str{ "M" } + laser.name;
    }
    else if (str::contains(name, "small"))
    {
      laser.heatCaused = heat{ 1 };
      laser.damagePerCluster = damage{ 3 };
      laser.ranges = std::array{ 1,2,3,4 };
      laser.name = fixed_str{ "S" } + laser.name;
    }
    if (str::contains(name, "heavy"))
    {
      if(!str::contains(name, "small"))
        result.locations.max++;
      laser.name = fixed_str{ "HV_" } + laser.name;
    }

    return { result, laser };
  }
  else if (str::contains(name, "flamer"))
  {
    Weapon flamer;
    flamer.name = "FLAMER";

    flamer.ranges = std::array{ 1, 2, 3, 4 };
    flamer.damagePerCluster = damage{ 2 };
    if (str::contains(name, "(r)"))
    {
      flamer.isRear = true;
    }

    return { result, flamer };
  }
  else if (name == "jump jet")
  {
    result.jump = jump_power{ 1 };
  }
  else if (name == "heat sink")
  {
    result.heat_removed = heat{ 1 };
  }
  else if (specialFromName(name).has_value())
  {
    result.specType = specialFromName(name).value();
  }
  else
  {
    throw std::runtime_error("Cannot identify component " + name);
  }
  return { result, std::nullopt };
}

std::string getline_stripped(std::ifstream& input, int& it)
{
  std::string ret;
  std::getline(input, ret);
  it++;
  if (ret.empty())
    return ret;
  ret.erase(std::remove(std::begin(ret), std::end(ret), '\r'), std::end(ret));
  return ret;
}

void loadMechData(Mech& srcMech, const char* filename)
{
  Mech mech = srcMech;

  int linenum = 0;
  std::ifstream infile(filename);
  const std::string version_read = getline_stripped(infile, linenum);
  // first line is version
  const std::string version_expected = "Version:1.0";
  if (version_read != version_expected)
  {
    throw std::runtime_error("Unexpected version first line: '" + version_read + "', expected: '" + version_expected + "' (" + std::to_string(version_read.size()) + " chars, expected " + std::to_string(version_expected.size()) + ").");
  }
  // next two lines are mech name
  mech.name = getline_stripped(infile, linenum) + "-" + getline_stripped(infile, linenum);

  while (!infile.eof())
  {
    const std::string line = getline_stripped(infile, linenum);
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
      while (!infile.eof())
      {
        const std::string weapon_data = getline_stripped(infile, linenum);
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
      while (!infile.eof())
      {
        const std::string component_data = getline_stripped(infile, linenum);
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
          throw std::runtime_error("Component " + component_data + " for " + valueName + " is at an invalid location.");
        }

        mech.addComponent(lineComp);
        
        skipLines = lineComp.first.locations.slotSize() - 1;
        position += lineComp.first.locations.slotSize();
      }
    }
  }

  srcMech = mech;
}

std::string stringifyComponent(const Mech& mech, const Component& c)
{
  if (c.isHeatsink())
  {
    return "Heatsink";
  }
  else if (c.isAmmo())
  {
    return std::string(Ammo_getName(c.ammoType)) + " ammo";
  }
  else if (c.isSpecial())
  {
    return std::string(SpecialComponent_getName(c.specType));
  }
  else if (c.isWeapon)
  {
    const auto& w = mech.lookupWeapon(c.id);
    if (w.component == c.id)
    {
      std::string result{ w.name.view() };
      if (w.isRear)
      {
        result += " (rear)";
      }
      return result;
    }
    else
    {
      throw std::runtime_error("Invalid weapon for component.");
    }
  }
  else
  {
    return "error";
  }
}

void receiveDamageCommand(Mech& mech, Armor part, damage dmg, bool rear = false)
{
  auto res = mech.processDamage({ dmg, part, rear, false });
  std::cout << res << "\n";

  if (res.criticalHit)
  {
    bool rollDone = false;
    const auto options = mech.getCritOptions(res.criticalSegment);

    std::cout << "Roll for critical to "<<res.criticalSegment<<": \n";
    for (const auto& opt : options)
    {
      std::cout << 
        "  " << opt.range.doPrintAsRolls()
        << " -> "
        << stringifyComponent(mech, mech.lookupComponent(opt.component))
        << "\n";
    }
    while (!rollDone)
    {
      std::cout << "Enter number on the dice: ";
      std::string line;
      std::getline(std::cin, line);
      auto dice = std::stoi(line);
      if (dice > 12 || dice < 1)
      {
        throw std::range_error("Dice roll must be from 1 to 12");
      }
      const auto result = mech.receiveCrit(res.criticalSegment, (byte)dice, true);
      if (result == crit::INVALID_ROLL)
      {
        throw std::runtime_error("Invalid roll");
      }
      else if (result == crit::ROLL_AGAIN)
      {
        std::cout << "Roll again...\n";
      }
      else
      {
        std::cout << "Component destroyed!\n";
        rollDone = true;
      }
    }

  }
}

void receiveDamageCommand(Mech& mech, std::string command)
{
  Armor part;
  unsigned short dmg = 0;
  bool rear = false;
  std::stringstream ss{ command };
  ss >> part >> dmg;

  if (part == Armor::NUM_SEGMENTS)
  {
    throw std::runtime_error("Cannot parse part ID, use name of armor part.");
  }

  std::string last = "";
  ss >> last;
  if (last == "rear" || last == "R")
  {
    rear = true;
  }
  receiveDamageCommand(mech, part, damage::forced_cast(dmg), rear);
}

int main(int argc, const char** argv)
{
  // windows related settings to allow unicode output to console
#ifdef IS_WINDOWS_BUILD
  // Set console code page to UTF-8 so console known how to interpret string data
  SetConsoleOutputCP(CP_UTF8);
  // Enable buffering to prevent VS from chopping up UTF-8 byte sequences
  setvbuf(stdout, nullptr, _IOFBF, 1000);
#endif

  Mech mech;
  if (argc > 1)
  {
    try
    {
      loadMechData(mech, argv[1]);
    }
    catch (const std::runtime_error& e)
    {
      std::cout << "Error parsing file: " << e.what() << "\n";
      return 3;
    }
  }
  std::cout << "write start to start game\n";
  std::cout << "Mech' name: " << mech.name.c_str() << "\n";
  std::string command;
  while (std::getline(std::cin, command))
  {
    //std::cout << "Command: " << command << "\n";
    try
    {
      if (command == "dmgstatus")
      {
        std::cout << mech.structure.doPrintDamage() << "\n";
      }
      else if (command == "heatsinks")
      {
        std::cout << (int)mech.heatSinkCount().value << "\n";
      }
      else if (command == "status")
      {
        std::cout << mech.structure.doPrintStatusBig() << "\n";
      }
      else if (command == "turn")
      {
        mech.destroyPendingComponents();
        mech.reduceHeat();
        std::cout << "Turn ended" << "\n";
      }
      else if (str::startswith(command, "dmg"))
      {
        receiveDamageCommand(mech, command.substr(4));
      }
      else if (command == "exit" || command == "")
      {
        std::cout << "Bye.\n";
        return 0;
      }
      else
      {
        std::cout << "Unknown command '" << command << "'.\n";
      }
    }
    catch (const std::runtime_error& e)
    {
      std::cout << "Command error: " << e.what() << "\n";
      return 2;
    }
  }
  return 0;
}
