#ifdef __EMSCRIPTEN__
#include <techsheet/Mech.h>

#include <mtfparser/MtfParser.h>
#include <mtfparser/parse_exceptions.h>

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "web/DamageResult_wrapper.h"
#include "web/optional_wrapper.h"
#include "web/number_ish_wrapper.h"
#include "web/component_util.h"
#include "string_descriptions.h"

#include <emscripten/bind.h>
#include <emscripten/emscripten.h>

#ifdef __INTELLISENSE__
#define EMSCRIPTEN_KEEPALIVE
#endif

using namespace techsheet;
using namespace emscripten;

static Mech globalMech;

class NotImplementedError : public std::runtime_error
{
public:
  NotImplementedError(std::string_view name) 
    : std::runtime_error(std::string("Not implemented: ") + std::string{ name })
  {}
};


extern "C"
{
  EMSCRIPTEN_KEEPALIVE bool initStructureInternal(const char* partName, int hp)
  {
    //std::cout << "initStructureInternal(\"" << partName << "\", " << hp << ");\n";

    const auto segment = Internal_getValue(partName);
    if (segment.has_value())
    {
      globalMech.structure[segment.value()].init(health::forced_cast(hp));
      return true;
    }
    return false;    
  }
  EMSCRIPTEN_KEEPALIVE int getStructureInternal(const char* partName)
  {
    //std::cout << "getStructureInternal(\"" << partName << ");\n";
    const auto segment = Internal_getValue(partName);
    if (segment.has_value())
    {
      return globalMech.structure[segment.value()].current.value;
    }
    return -1;
  }
  EMSCRIPTEN_KEEPALIVE int getStructureArmor(const char* partName)
  {
    //std::cout << "getStructureArmor(\"" << partName << ");\n";
    const auto segment = Armor_getValue(partName);
    if (segment.has_value())
    {
      return globalMech.structure[segment.value()].current.value;
    }
    return -1;
  }
  EMSCRIPTEN_KEEPALIVE bool initStructureArmor(const char* partName, int hp)
  {
    //std::cout << "initStructureArmor(\"" << partName << "\", " << hp << ");\n";

    const auto segment = Armor_getValue(partName);
    if (segment.has_value())
    {
      globalMech.structure[segment.value()].init(health::forced_cast(hp));
      return true;
    }
    return false;
  }

  EMSCRIPTEN_KEEPALIVE void unstageDamage()
  {
    globalMech.structure.unstage();
  }

  EMSCRIPTEN_KEEPALIVE bool parseMech(const char* mechData)
  {
    std::istringstream iss(mechData);
    try
    {
      Mech tmp = mtfparser::MtfParser::parse(iss);
      globalMech = tmp;
      globalMech.autoSelectAllWeaponAmmo();
      return true;
    }
    catch (const mtfparser::ParseException& e)
    {
      std::cout << "Parsing failed: " << e.what() << "\n";
      return false;
    }
  }

  EMSCRIPTEN_KEEPALIVE int getTotalJumpPower()
  {
    return globalMech.totalJumpPower().value;
  }

  EMSCRIPTEN_KEEPALIVE void endTurn()
  {
    globalMech.destroyPendingComponents();
    globalMech.reduceHeat();
  }
}

EMSCRIPTEN_KEEPALIVE std::vector<std::string> getInternalNames()
{
  std::vector<std::string> result{ Internal_names.cbegin(), Internal_names.cend() };
  return result;
}
EMSCRIPTEN_KEEPALIVE std::vector<std::string> getArmorNames()
{
  std::vector<std::string> result{ Armor_names.cbegin(), Armor_names.cend() };
  return result;
}

EMSCRIPTEN_KEEPALIVE SegmentHealth getHealthInternal(emscripten::val v)
{
  if (v.isString())
  {
    const auto partName = v.as<std::string>();
    //std::cout << "getHealthInternal(\"" << partName << ");\n";
    const auto segment = Internal_getValue(partName);
    if (segment.has_value())
    {
      return globalMech.structure[segment.value()];
    }
  }

  return SegmentHealth();
}

EMSCRIPTEN_KEEPALIVE SegmentHealth getHealthArmor(const std::string partName)
{
  //std::cout << "getHealthArmor(\"" << partName << ");\n";
  const auto segment = Armor_getValue(partName);
  if (segment.has_value())
  {
    return globalMech.structure[segment.value()];
  }
  return SegmentHealth();
}

DamageResult receiveDamage(std::string partName, int hits, bool staging = false)
{
  const auto segment = Armor_getValue(partName);
  if (segment.has_value())
  {
    IncomingDamage d{ damage::forced_cast(hits), segment.value(), false, staging };
    if (staging)
    {
      return globalMech.structure.receiveDamage(d);
    }
    else
    {
      return globalMech.processDamage(d);
    }
  }
  return {};
}

std::vector<CritRollOption> getCritOptions(std::string partName)
{
  const auto segment = Internal_getValue(partName);
  if (segment.has_value())
  {
    return globalMech.getCritOptions(segment.value());
  }
  return {};
}

EMSCRIPTEN_KEEPALIVE std::vector<int> getComponents()
{
  std::vector<int> ids;

  for (const auto& c : globalMech.components)
  {
    ids.push_back(c.id.value);
  }
  return ids;
}

EMSCRIPTEN_KEEPALIVE std::vector<int> getWeapons()
{
  std::vector<int> ids;

  for (const auto& c : globalMech.weapons)
  {
    ids.push_back(c.component.value);
  }
  return ids;
}

EMSCRIPTEN_KEEPALIVE std::optional<Component> getComponent(int id)
{
  for (const auto& c : globalMech.components)
  {
    if (id == c.id.value)
    {
      return c;
    }
  }
  return std::nullopt;
}

//std::string describeComponent(int id)
//{
//  for (const auto& c : globalMech.components)
//  {
//    if (id == c.id.value)
//    {
//      return c;
//    }
//  }
//  return std::nullopt;
//}

std::string describeLiveComponent(const Component& c)
{
  return stringifyComponent(globalMech, c);
}

EMSCRIPTEN_KEEPALIVE std::optional<Weapon> getWeapon(int id)
{
  for (const auto& c : globalMech.weapons)
  {
    if (id == c.component.value)
    {
      return c;
    }
  }
  return std::nullopt;
}

struct CritRollResultSimple
{
  int component = 0;
  bool rollAgain = false;
  bool invalid = false;

  CritRollResultSimple() {}
  CritRollResultSimple(bool rollAgainParam, int componentParam, bool invalid = false)
    : component(componentParam), rollAgain(rollAgainParam), invalid{invalid}
  {}

  CritRollResultSimple(const CritRollResult& r)
    : component(r.destroyedCmp.value), rollAgain(r.rollAgain)
  {}
};

CritRollResultSimple receiveCrit(std::string partName, byte critPos, bool execute)
{
  const auto segment = Internal_getValue(partName);
  if (segment.has_value())
  {
    return globalMech.receiveCrit(segment.value(), critPos, execute);
  }
  return { 0, false, true };
}

bool fireWeapon(int id)
{
  const auto weapon = getWeapon(id);
  if (weapon.has_value())
  {
    throw NotImplementedError("fireWeapon()");
    return true;
  }
  return false;
}

struct WeaponHelper
{
  static emscripten::val getHeatCaused(
    const Weapon& v)
  {
    return emscripten::val((int)v.heatCaused.value);
  }
  static void setHeatCaused(
    Weapon& v, int value)
  {
    v.heatCaused = heat::forced_cast(value);
  }
  static emscripten::val getComponent(
    const Weapon& v)
  {
    return emscripten::val((int)v.component.value);
  }
  static emscripten::val getName(const Weapon& v)
  {
    return emscripten::val(std::string(v.name.view()));
  }
};



// my_number_value.h
struct my_number_value
{
  constexpr explicit my_number_value(int x) : x{ x } {}
  int x;
};
struct my_number_value_helper
{
  static emscripten::val getValue(
    const my_number_value& v)
  {
    return emscripten::val(v.x);
  }
};

EMSCRIPTEN_KEEPALIVE my_number_value getNumber()
{
  return my_number_value{ 42 };
}

EMSCRIPTEN_KEEPALIVE val my_number_value_to_val(const my_number_value& value)
{
  return val(value.x);
}

// Conversion from val to my_number_value
EMSCRIPTEN_KEEPALIVE my_number_value val_to_my_number_value(const val& v)
{
  return my_number_value(v.as<int>());
}

//namespace emscripten::internal
//{
//template<>
//struct BindingType<my_number_value>
//{
//  typedef int WireType;
//  constexpr static WireType toWireType(const my_number_value& v)
//  {
//    return v.x;
//  }
//  static my_number_value fromWireType(WireType v)
//  {
//    return my_number_value{ v };
//  }
//};
//}


#ifndef __INTELLISENSE__
EMSCRIPTEN_BINDINGS(techsheetweb)
{
  register_number_ish<ammo_count>("ammo_count");
  register_number_ish<heat>("heat");
  register_number_ish<health>("health");
  register_number_ish<damage>("damage");
  register_number_ish<range>("range");
  register_number_ish<component_id>("component_id");

  class_<Weapon>("Weapon")
    .constructor<>()
    .function("totalDamage", &Weapon::totalDamage)
    .property("heatCaused", &WeaponHelper::getHeatCaused, &WeaponHelper::setHeatCaused)
    .property("component", &WeaponHelper::getComponent)
    .property("ammoBin", &Weapon::ammoBin)
    .property("name", &WeaponHelper::getName)
    .property("ranges", &Weapon::ranges)
    .property("usesAmmo", &Weapon::usesAmmo)
    .property("lacksAmmo", &Weapon::lacksAmmo)
    .property("fired", &Weapon::fired)
    ;

  class_<DamageResult>("DamageResult")
    .constructor<>()
    .property("criticalHit", &DamageResult::criticalHit)
    .property("criticalSegment", &DamageResult_wrapper::getCriticalSegment)
    .property("mechDestroyed", &DamageResult::mechDestroyed)
    .property("partDestroyed", &DamageResult::partDestroyed)
    .property("psrRequired", &DamageResult::psrRequired)
    ;

  enum_<RangeLimits::Type>("RangeType")
    .value("SHORT", RangeLimits::Type::SHORT)
    .value("MEDIUM", RangeLimits::Type::MEDIUM)
    .value("LONG", RangeLimits::Type::LONG)
    .value("EXTREME", RangeLimits::Type::EXTREME)
    ;

  class_<RangeLimits>("RangeLimits")
    .constructor<>()
    .constructor<int, int, int, int, int>()
    .function("sht", select_overload<range& ()>(&RangeLimits::sht))
    .function("med", select_overload<range& ()>(&RangeLimits::med))
    .function("mid", select_overload<range& ()>(&RangeLimits::mid))
    .function("lng", select_overload<range& ()>(&RangeLimits::lng))
    .function("ext", select_overload<range& ()>(&RangeLimits::ext))
    .function("min", select_overload<range& ()>(&RangeLimits::min))
    .function("sht", select_overload<const range& () const>(&RangeLimits::sht))
    .function("med", select_overload<const range& () const>(&RangeLimits::med))
    .function("mid", select_overload<const range& () const>(&RangeLimits::mid))
    .function("lng", select_overload<const range& () const>(&RangeLimits::lng))
    .function("ext", select_overload<const range& () const>(&RangeLimits::ext))
    .function("min", select_overload<const range& () const>(&RangeLimits::min))
    ;

  enum_<Component::Status>("Component_Status")
    .value("FINE", Component::Status::FINE)
    .value("LAST_TURN", Component::Status::LAST_TURN)
    .value("DESTROYED", Component::Status::DESTROYED)
    ;

  class_<Component>("Component")
    .constructor<>()
    .property("position", &ComponentHelper::getPosition)
    .function("isDestroyed", &Component::isDestroyed)
    .function("isSpecial", &Component::isSpecial)
    .function("isHealthy", &Component::isHealthy)
    .function("isUsable", &Component::isUsable)
    .function("isValid", &Component::isValid)
    .function("isHeatsink", &Component::isHeatsink)
    .function("isAmmo", select_overload<bool() const>(&Component::isAmmo))
    .function("isAmmo", select_overload<bool(Ammo) const>(&Component::isAmmo))
    .function("isJumpJet", &Component::isJumpJet)
    .function("reset", &Component::reset)
    .property("name", &ComponentHelper::getName)
    .property("description", &describeLiveComponent)
    .property("status", &ComponentHelper::getStatus)
    .property("id", &ComponentHelper::getId)
    .property("ammoType", &ComponentHelper::getAmmoType)
    .property("ammo", &Component::ammo)
    .property("maxAmmo", &Component::maxAmmo)
    .property("ammoDamage", &Component::ammoDamage)
    .property("isWeapon", &Component::isWeapon)
    .function("ammoExplodes", &Component::ammoExplodes)
    .function("ammoExplosionDamage", &Component::ammoExplosionDamage)
    .property("heatRemoved", &Component::heatRemoved)
    .property("jump", &Component::jump)
    ;

  class_<CritRange>("CritRange")
    .constructor<byte, byte>()
    .constructor<byte>()
    .constructor<>()
    .property("min", &CritRange::min)
    .property("max", &CritRange::max)
    .function("slotSize", &CritRange::slotSize)
    .function("isHit", &CritRange::isHit)
    .function("overlaps", &CritRange::overlaps)
    .function("containsIncl", &CritRange::containsIncl)
    .function("nextTo", &CritRange::nextTo)
    .function("offset", &CritRange::offset)
    ;

  class_<CritRollOption>("CritRollOption")
    .constructor<>()
    .property("range", &CritRollOption::range)
    .property("component", &CritRollOption::component)
    .property("alreadyDestroyed", &CritRollOption::alreadyDestroyed)
    ;

  class_<CritRollResultSimple>("CritRollResultSimple")
    .constructor<>()
    .constructor<bool, int>()
    .property("component", &CritRollResultSimple::component)
    .property("rollAgain", &CritRollResultSimple::rollAgain)
    .property("invalid", &CritRollResultSimple::invalid)
    ;

  class_<SegmentHealth>("SegmentHealth")
    .constructor<>()
    .property("max", &SegmentHealth::max)
    .property("current", &SegmentHealth::current)
    .property("staging", &SegmentHealth::staging)
    .function("reset", &SegmentHealth::reset)
    .function("init", &SegmentHealth::init)
    .function("consumeDamage", &SegmentHealth::consumeDamage)
    .function("unstage", &SegmentHealth::unstage)
    .function("destroyed", &SegmentHealth::destroyed)
    .function("destroy", &SegmentHealth::destroy)
    .function("damaged", &SegmentHealth::damaged)
    ;

  function("getInternalNames", &getInternalNames);
  function("getArmorNames", &getArmorNames);
  function("getHealthInternal", &getHealthInternal);
  function("getHealthArmor", &getHealthArmor);
  function("receiveDamage", &receiveDamage);
  function("getComponents", &getComponents);
  function("getComponent", &getComponent);
  function("getWeapons", &getWeapons);
  function("getWeapon", &getWeapon);
  function("fireWeapon", &fireWeapon);
  function("getCritOptions", &getCritOptions);
  function("receiveCrit", &receiveCrit);

  register_optional<Component>("optional<Component>");
  register_optional<Weapon>("optional<Weapon>");
  register_vector<int>("vector<int>");
  register_vector<std::string>("vector<string>");
  register_vector<CritRollOption>("vector<CritRollOption>");
  register_map<int, std::string>("map<int, string>");

  //register_opaque<my_number_value>("my_number_value")
  //  .constructor<int>()
  //  .conversion(&my_number_value_to_val, &val_to_my_number_value);
  //class_<my_number_value>("my_number_value")
  //  .property("x", &my_number_value_helper::getValue)
  //  ;
  function("getNumber", &getNumber);
}
#endif
#endif