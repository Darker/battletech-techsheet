#include "techsheet/structure.h"
#include "techsheet/std_cout_printing.h"

#include <boost/test/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

#include "suite_registry.h"

#include <algorithm>
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
  const auto damaged_structure = toInternal(segment_dmgd);
  m.receiveDamage(inc_dmg);
  std::cout << "Testing damage " << inc_dmg << std::endl;

  for (const auto& armor_segment : Armor_values)
  {
    const bool is_damaged = armor_segment == segment_dmgd;

    const damage received{ is_damaged ? (byte)damage_val : (byte)0 };

    const auto armor_pre = m_init[armor_segment].max;
    const auto armor_after = m[armor_segment].current;

    const auto armor_expected = armor_pre.substract_clamp(health{ received.value });

    BOOST_CHECK_EQUAL(armor_after.value, armor_expected.value);

    const auto internal_segment = toInternal(armor_segment);
    // if this internal segment WAS damaged, but not from this armor segment skip the check
    if (damaged_structure == internal_segment && armor_segment != segment_dmgd)
    {
      continue;
    }

    const auto received_internal = received.substract_clamp(damage{ armor_pre.value });

    const auto internal_pre = m_init[internal_segment].max;
    const auto internal_after = m[internal_segment].current;

    const auto internal_expected = internal_pre.substract_clamp(health{ received_internal.value });

    BOOST_CHECK_EQUAL(internal_after.value, internal_expected.value);
  }
}

static const auto nothing = unit::Registry::add([]()
{
  test_suite* ts1 = BOOST_TEST_SUITE("test_structure_manager");
  ts1->add(BOOST_PARAM_TEST_CASE(&test_damage_no_internal, std::begin(Armor_values), std::end(Armor_values)));
  ts1->add(BOOST_PARAM_TEST_CASE(&test_damage_no_overflow, std::begin(Armor_values), std::end(Armor_values)));
  return ts1;
});

