#pragma once

#include <techsheet/Component.h>

#include <string_view>

#include <emscripten/val.h>



std::string_view statusToString(techsheet::Component::Status status)
{
  switch (status)
  {
  case techsheet::Component::Status::FINE:
    return "FINE";
  case techsheet::Component::Status::LAST_TURN:
    return "LAST_TURN";
  case techsheet::Component::Status::DESTROYED:
    return "DESTROYED";
  default:
    return "UNKNOWN";
  }
}

techsheet::Component::Status statusFromString(std::string_view statusStr)
{
  if (statusStr == "FINE")
  {
    return techsheet::Component::Status::FINE;
  }
  else if (statusStr == "LAST_TURN")
  {
    return techsheet::Component::Status::LAST_TURN;
  }
  else if (statusStr == "DESTROYED")
  {
    return techsheet::Component::Status::DESTROYED;
  }
  else
  {
    return techsheet::Component::Status::FINE; // Default value if not found
  }
}

struct ComponentHelper
{
  using Component = techsheet::Component;

  static emscripten::val getId(
    const Component& v)
  {
    return emscripten::val((int)v.id.value);
  }
  static emscripten::val getAmmoType(const Component& v)
  {
    return emscripten::val(std::string(techsheet::Ammo_getName(v.ammoType)));
  }
  static emscripten::val getName(const Component& v)
  {
    return emscripten::val(std::string(v.name.view()));
  }
  static emscripten::val getPosition(const Component& v)
  {
    return emscripten::val(std::string(techsheet::Internal_getName(v.position)));
  }
  static emscripten::val getStatus(const Component& v)
  {
    return emscripten::val(std::string(statusToString(v.status)));
  }
};