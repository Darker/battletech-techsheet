#include "../include/techsheet/structure.h"
#include "../include/techsheet/std_cout_printing.h"

#include <iostream>

//using namespace techsheet;

void assert_true(bool cond, const char* message)
{
  if (!cond)
  {
    std::cout << message << "\n";
    exit(1);
  }
}

int main()
{
  using namespace techsheet;
  StructureManager m;

  std::cout << "Manager created\n";

  m.setArmor({ 
          9,
    10,11,13,11,10,
      12,12,
      5,6,5 });
  m.setInternal({ 3,6,8,11,8,6,8,8 });
  std::cout << "parts written\n";

  const auto doDamage = [&m](Armor part, damage dmg, bool rear = false)
  {
    const char* rear_txt = rear ? " (rear)" : "";
    std::cout << "Damage: " << (short)dmg.value << " to " << armorName(part) << rear_txt <<"\n";
    auto result = m.receiveDamage(part, dmg, rear);
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
}