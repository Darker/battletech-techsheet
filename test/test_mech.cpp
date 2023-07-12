#include "../include/techsheet/structure.h"
#include "../include/techsheet/std_cout_printing.h"

#include "../include/techsheet/Ammo.h"
#include "../include/techsheet/Mech.h"

#include <iostream>

int main()
{
  using namespace techsheet;
  Mech mech;
  mech.name = "ABCDE";

  std::cout << mech.name.c_str() << "\n";
  return 0;
}