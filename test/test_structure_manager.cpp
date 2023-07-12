#include "../include/techsheet/structure.h"
#include "../include/techsheet/std_cout_printing.h"

#include "../include/techsheet/Ammo.h"

#include <iostream>
// g++ -std=c++17 test_structure_manager.cpp -o test.exe
//using namespace techsheet;

static void assert_true(bool cond, const char* message)
{
  if (!cond)
  {
    std::cout << message << "\n";
    exit(1);
  }
}

int mainddd()
{
  using namespace techsheet;


  std::cout << Ammo_getName(Ammo::AC_10) << "\n";

  std::optional<Ammo> fromName = Ammo_getValue("AC_2");
  if (fromName.has_value())
  {
    std::cout << "AC_2 resolved to " << Ammo_getName(fromName.value()) << "\n";
  }
  else
  {
    std::cout << "Cannot resolve ammo name.\n";
  }


  StructureManager m;
  std::cout << "Manager created\n";

  m.setArmor(ArmorHealth<byte>{ 
          9,
    10, 11,13,11 ,10,
        12,12,
        5,6,5 
   });
  m.setInternal(InternalHealth<byte>{
          3,
    6, 8,11,8, 6,
         8,8 
   });
  std::cout << "parts written\n";

  const auto doDamage = [&m](Armor part, damage toDeal, bool rear = false)
  {
    IncomingDamage dmg{ toDeal, part, rear };
    const char* rear_txt = rear ? " (rear)" : "";
    std::cout << dmg << "\n";
    auto result = m.receiveDamage(dmg);
    std::cout << "Damage result: " << result << "\n";
    std::cout << m.printDamage << "\n";
  };

  doDamage(Armor::LA, damage(9));
  doDamage(Armor::LA, damage(4));
  doDamage(Armor::LA, damage(9));
  doDamage(Armor::LA, damage(1), true);
  doDamage(Armor::LT, damage(3), true);
  doDamage(Armor::LT, damage(1));
  doDamage(Armor::RTR, damage(7));
  doDamage(Armor::CTR, damage(7));
  doDamage(Armor::HEAD, damage(11));
  doDamage(Armor::HEAD, damage(1));
  return 0;
}