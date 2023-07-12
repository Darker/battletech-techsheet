#pragma once
#include "NumberIsh.h"

namespace techsheet
{

template<typename impl_t>
using id_number_t = NumberIsh<uint16_t, impl_t, CalcOptions::NONE, CalcOptions::NONE, CalcOptions::NONE>;

struct component_id : id_number_t<component_id>
{
  using SelfType::NumberIsh;

  component_id next()
  {
    return component_id{ ++value };
  }
};


}
