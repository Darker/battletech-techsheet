#pragma once
#include <algorithm>
#include <string>

namespace str
{

static inline std::string tolower(std::string s)
{
  std::transform(s.begin(), s.end(), s.begin(),
    [](unsigned char c) { return std::tolower(c); } // correct
  );
  return s;
}

static inline bool endswith(std::string_view str, std::string_view needle)
{
  const auto pos = str.find(needle);
  if (pos != std::string::npos)
  {
    return pos + needle.size() == str.length();
  }
  return false;
}

static inline bool startswith(std::string_view str, std::string_view needle)
{
  return str.find(needle) == 0;
}

static inline bool contains(std::string_view str, std::string_view needle)
{
  return str.find(needle) != std::string::npos;
}

// trim from start (in place)
static inline void ltrim(std::string& s)
{
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch)
  {
    return !std::isspace(ch);
  }));
}

// trim from end (in place)
static inline void rtrim(std::string& s)
{
  s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch)
  {
    return !std::isspace(ch);
  }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string& s)
{
  rtrim(s);
  ltrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s)
{
  ltrim(s);
  return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s)
{
  rtrim(s);
  return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s)
{
  trim(s);
  return s;
}

}
