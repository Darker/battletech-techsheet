#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

#include "techsheet/structure.h"
#include "techsheet/std_cout_printing.h"

#include "techsheet/Ammo.h"

#include <iostream>

using namespace techsheet;
using namespace boost::unit_test;

void test_damage_no_internal(const Armor& segment_dmgd)
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

  auto m = m_init;
  const IncomingDamage inc_dmg(damage{damage_val}, segment_dmgd);
  m.receiveDamage(inc_dmg);
  std::cout << "Testing damage " << inc_dmg << std::endl;

  for (const auto& armor_segment : Armor_values)
  {
    const bool is_damaged = armor_segment == segment_dmgd;

    const auto armor_pre = m_init[armor_segment].max.value;
    const auto armor_after = m[armor_segment].current.value;
    const auto armor_expected = is_damaged ? static_cast<int>(armor_pre) - static_cast<int>(damage_val) : static_cast<int>(armor_pre);
    BOOST_CHECK_EQUAL(armor_after, armor_expected);

    const auto internal_segment = toInternal(armor_segment);
    const auto internal_pre = m_init[internal_segment].max.value;
    const auto internal_after = m[internal_segment].current.value;
    const auto internal_expected = static_cast<int>(internal_pre);
    BOOST_CHECK_EQUAL(internal_after, internal_expected);
  }
}


void test_damage_no_overflow(const Armor& segment_dmgd)
{
  // the test assumes that the damage value may be larger than the armor value but not than the armor and internal values together in any segment
  constexpr int damage_val {10};

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

  auto m = m_init;
  const IncomingDamage inc_dmg(damage{damage_val}, segment_dmgd);
  m.receiveDamage(inc_dmg);
  std::cout << "Testing damage " << inc_dmg << std::endl;

  for (const auto& armor_segment : Armor_values)
  {
    const bool is_damaged = armor_segment == segment_dmgd;

    const auto armor_pre = m_init[armor_segment].max.value;
    const auto armor_after = m[armor_segment].current.value;
    const auto armor_expected = is_damaged ? std::max(static_cast<int>(armor_pre) - damage_val, 0) : static_cast<int>(armor_pre);
    BOOST_CHECK_EQUAL(armor_after, armor_expected);
    const auto dmg_internal = std::max(damage_val - static_cast<int>(armor_pre), 0);

    const auto internal_segment = toInternal(armor_segment);
    const auto internal_pre = m_init[internal_segment].max.value;
    const auto internal_after = m[internal_segment].current.value;
    const auto internal_expected = is_damaged ? static_cast<int>(internal_pre) - dmg_internal : static_cast<int>(internal_pre);
    BOOST_CHECK_EQUAL(internal_after, internal_expected);
  }
}

test_suite* init_unit_test_suite( int /*argc*/, char* /*argv*/[] )
{

  framework::master_test_suite().add(BOOST_PARAM_TEST_CASE(&test_damage_no_internal, std::begin(Armor_values), std::end(Armor_values)));

  framework::master_test_suite().add(BOOST_PARAM_TEST_CASE(&test_damage_no_overflow, std::begin(Armor_values), std::end(Armor_values)));

  return 0;
}
