#include "string_tools.h"
#include "is_windows.h"
#include "emscripten_polyfill.h"
#include "string_descriptions.h"

#include <techsheet/Mech.h>
#include <techsheet/std_cout_printing.h>

#include <mtfparser/MtfParser.h>

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
        << stringifyComponent(mech, *mech.lookupComponent(opt.component))
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

void printComponentsCommand(Mech& mech, std::string command)
{
  Armor part;
  std::stringstream ss{ command };
  ss >> part;

  if (part == Armor::NUM_SEGMENTS)
  {
    throw std::runtime_error("Cannot parse part ID, use name of armor part.");
  }

  for (const Component& c : mech.componentsAt(toInternal(part)))
  {
    std::cout <<
      "  " << c.locations.doPrintAsRolls()
      << " -> "
      << stringifyComponent(mech, c)
      << "\n";
  }
}

int main(int argc, const char** argv)
{
  // windows related settings to allow unicode output to console
#if defined(IS_WINDOWS_BUILD) && defined(_MSC_VER)
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
      std::ifstream infile(argv[1]);
      mech = mtfparser::MtfParser::parse(infile);
      bool allFound = mech.autoSelectAllWeaponAmmo();
      if (!allFound)
      {
        std::cout << "Some weapons do not have ammo:\n";
        for (const Weapon& w : mech.weapons)
        {
          if (w.lacksAmmo())
          {
            const Component* wcmp = mech.lookupComponent(w.component);
            const auto pos = wcmp != nullptr ? wcmp->position : Internal::NUM_SEGMENTS;
            std::cout << "  " << w.name << " in " << pos << "\n";
          }
        }
      }
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
      else if (str::startswith(command, "cmps"))
      {
        printComponentsCommand(mech, command.substr(5));
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

