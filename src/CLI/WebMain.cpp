#ifdef __EMSCRIPTEN__
#include <techsheet/Mech.h>

#include <mtfparser/MtfParser.h>
#include <mtfparser/parse_exceptions.h>

#include <iostream>
#include <sstream>

#include "web/optional_wrapper.h"
#include "web/number_ish_wrapper.h"

#include <emscripten/bind.h>
#include <emscripten/emscripten.h>

#ifdef __INTELLISENSE__
#define EMSCRIPTEN_KEEPALIVE
#endif

using namespace techsheet;
using namespace emscripten;

static Mech globalMech;


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

  EMSCRIPTEN_KEEPALIVE bool receiveDamage(const char* partName, int hits, bool staging = false)
  {
    const auto segment = Armor_getValue(partName);
    if (segment.has_value())
    {
      IncomingDamage d{ damage::forced_cast(hits), segment.value(), false, staging };
      if (staging)
      {
        globalMech.structure.receiveDamage(d);
      }
      else
      {
        globalMech.processDamage(d);
      }
      
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
      return true;
    }
    catch (const mtfparser::ParseException& e)
    {
      std::cout << "Parsing failed: " << e.what() << "\n";
      return false;
    }
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
    std::cout << "getHealthInternal(\"" << partName << ");\n";
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
  std::cout << "getHealthArmor(\"" << partName << ");\n";
  const auto segment = Armor_getValue(partName);
  if (segment.has_value())
  {
    return globalMech.structure[segment.value()];
  }
  return SegmentHealth();
}

EMSCRIPTEN_KEEPALIVE Weapon getWeapon()
{
  for (const Weapon& w : globalMech.weapons)
  {
    return w;
  }
  return {};
}

struct WeaponWrapper
{
  Weapon& w;
  Mech& parent;

  int getHeatCaused() const { return w.heatCaused.value; }
  void setHeatCaused(int value) const { w.heatCaused = heat::forced_cast(value); }
  damage totalDamage() const { return w.totalDamage(); }
};

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

};

struct ComponentHelper
{
  static emscripten::val getId(
    const Component& v)
  {
    return emscripten::val((int)v.id.value);
  }
};

template <typename NumberIshImp>
struct NumberIshHelper
{
  static emscripten::val getValue(const NumberIshImp& n)
  {
    return emscripten::val((int)n.value);
  }
  static emscripten::val isNumberIsh(const NumberIshImp&)
  {
    return emscripten::val(true);
  }
};

template<typename NumberIshImp>
class_<NumberIshImp> register_number_ish(const char* name)
{
  return class_<NumberIshImp>(name)
    .template constructor<typename NumberIshImp::base_type>()
    .property("value", &NumberIshHelper<NumberIshImp>::getValue)
    .property("isNumberIsh", &NumberIshHelper<NumberIshImp>::isNumberIsh)
    ;
}

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
  class_<Weapon>("Weapon")
    .constructor<>()
    .function("totalDamage", &Weapon::totalDamage)
    .property("heatCaused", &WeaponHelper::getHeatCaused, &WeaponHelper::setHeatCaused)
    .property("component", &WeaponHelper::getComponent)
    ;

  class_<Component>("Component")
    .constructor<>()
    .property("id", &ComponentHelper::getId)
    ;

  //class_<Component>("Mech")
  //  .constructor<>()
  //  ;

  class_<WeaponWrapper>("WeaponWrapper")
    .function("totalDamage", &Weapon::totalDamage)
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
    .function("offset", &CritRange::offset);

  register_number_ish<health>("health");
  register_number_ish<damage>("damage");

  //class_<IncomingDamage>("IncomingDamage")
  //  .constructor<damage, bool>()
  //  .function("reduce", &IncomingDamage::reduce)
  //  .property("dmg", &IncomingDamage::dmg)
  //  .property("staging", &IncomingDamage::staging);

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
    .function("damaged", &SegmentHealth::damaged);

  function("getInternalNames", &getInternalNames);
  function("getArmorNames", &getArmorNames);
  function("getHealthInternal", &getHealthInternal);
  function("getHealthArmor", &getHealthArmor);

  function("getWeapon", &getWeapon);
  register_optional<Component>("optional<Component>");
  register_vector<int>("vector<int>");
  register_vector<std::string>("vector<string>");
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