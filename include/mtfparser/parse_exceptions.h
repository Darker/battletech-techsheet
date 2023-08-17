#pragma once

#include <stdexcept>

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
* Parse exception that was caused by another exception thrown
* inside helper function or std lib
*/
class CausedParseException : public ParseException
{
  CausedParseException(const std::runtime_error& cause, std::size_t line)
    : ParseException(cause.what(), line)
  {}
};

}
