#include <techsheet/Mech.h>

#include <istream>

namespace mtfparser
{

struct MtfParser
{
  static techsheet::Mech parse(std::istream& input);
};

}

