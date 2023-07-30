#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include "techsheet/structure.h"
#include "techsheet/std_cout_printing.h"

#include "techsheet/Ammo.h"

#include <iostream>

using namespace techsheet;

BOOST_AUTO_TEST_CASE( armor_damage_no_internal )
{
  // the test assumes that the damage value is not larger than the armor value in any segment
  constexpr int damage_val {5};

  const auto armor_init = ArmorHealth<byte>{ 
          9,
    10, 11,13,11 ,10,
        12,12,
        5,6,5 
    };
  const auto internal_init = InternalHealth<byte>{
          3,
    6, 8,11,8, 6,
         8,8 
    };
  const StructureManager m_init(armor_init, internal_init);

  for (int it = 0; it < static_cast<int>(Armor::NUM_SEGMENTS); it++)
  {
    auto m = m_init;
    const auto segment = static_cast<Armor>(it);
    const IncomingDamage inc_dmg(damage{damage_val}, segment);
    m.receiveDamage(inc_dmg);

    for (int it2 = 0; it2 < static_cast<int>(Armor::NUM_SEGMENTS); it2++)
    {
      const auto armor_pre = m_init.armorHealth.at(it2).max.value;
      const auto armor_after = m.armorHealth.at(it2).current.value;
      const auto armor_expected = it == it2 ? static_cast<int>(armor_pre) - static_cast<int>(damage_val) : static_cast<int>(armor_pre);
      BOOST_CHECK_EQUAL(armor_after, armor_expected);
    }

    for (int it2 = 0; it2 < static_cast<int>(Internal::NUM_SEGMENTS); it2++)
    {
      const auto internal_pre = m_init.armorHealth.at(it2).max.value;
      const auto internal_after = m.internalHealth.at(it2).current.value;
      const auto internal_expected = static_cast<int>(internal_pre);
      BOOST_CHECK_EQUAL(internal_pre, internal_expected);
    }
  }
}
