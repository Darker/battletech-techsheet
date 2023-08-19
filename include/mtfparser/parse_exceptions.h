#pragma once

#include <techsheet/CritRange.h>
#include <techsheet/structure_static.h>

#include <stdexcept>
#include <string>


namespace mtfparser
{

class ParseException : public std::runtime_error
{
public:
  ParseException(const std::string& what, std::size_t line)
    : std::runtime_error(what)
    , line{ line }
  {}
  ParseException(const char* what, std::size_t line)
    : std::runtime_error(what)
    , line{ line }
  {}

  std::size_t line{ 0 };
};

/*
* Component crit location error
*/
class CritLocationError : public ParseException
{
public:
  std::string component;
  std::string part;
protected:
  CritLocationError(
    const std::string& cmpName,
    const std::string& partName,
    const std::string& msg,
    std::size_t line
  )
    : ParseException(msg, line)
    , component{cmpName}
    , part{partName}
  {}
};

static std::string critRange2String(techsheet::CritRange r)
{
  return std::string{ "<" } + std::to_string((int)r.min) + ", " + std::to_string((int)r.max) + ">";
}

class CritLocationOutOfBounds : public CritLocationError
{
private:
  static std::string makeMessage(
    const std::string& cmpName,
    const std::string& partName,
    techsheet::CritRange range
  )
  {
    return "Component '" 
      + cmpName
      + "' with crit slots " 
      + critRange2String(range)
      + " cannot fit into '" 
      + partName
      + "'";
  }
public:
  CritLocationOutOfBounds(
    const std::string& cmpName,
    const std::string& partName,
    techsheet::CritRange range,
    std::size_t line
  )
    : CritLocationError(cmpName, partName, makeMessage(cmpName, partName, range), line)
    , range{range}
  {}

  techsheet::CritRange range;
};

class CritLocationOverlap : public CritLocationError
{
private:
  static std::string makeMessage(
    const std::string& cmpName,
    const std::string& overlapName,
    const std::string& partName,
    techsheet::CritRange range)
  {
    return "Component '"
      + cmpName
      + "' with crit slots "
      + critRange2String(range)
      + " in '"
      + partName
      + "' overlaps with '"
      + overlapName
      + "'";
  }
public:
  CritLocationOverlap(
    const std::string& cmpName,
    const std::string& overlapName,
    const std::string& partName,
    techsheet::CritRange range,
    std::size_t line
  )
    : CritLocationError(cmpName, partName, makeMessage(cmpName, overlapName, partName, range), line)
    , overlap{overlapName}
    , range{ range }
  {}

  std::string overlap;
  techsheet::CritRange range;
};

/*
* Parse exception that was caused by another exception thrown
* inside helper function or std lib
*/
class CausedParseException : public ParseException
{
  CausedParseException(const std::runtime_error& cause, std::size_t line)
    : ParseException(std::string{"Parsing failed due to error: "} + cause.what(), line)
  {}
};

}
