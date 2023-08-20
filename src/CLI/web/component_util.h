#pragma once

#include <techsheet/Component.h>

#include <string_view>

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