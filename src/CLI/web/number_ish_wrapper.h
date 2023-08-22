#pragma once
#ifdef __EMSCRIPTEN__
#include <techsheet/NumberIsh.h>

#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
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
emscripten::class_<NumberIshImp> register_number_ish(const char* name)
{
  using namespace emscripten;
  return class_<NumberIshImp>(name)
    .template constructor<typename NumberIshImp::base_type>()
    .property("value", &NumberIshHelper<NumberIshImp>::getValue)
    .property("isNumberIsh", &NumberIshHelper<NumberIshImp>::isNumberIsh)
    ;
}
#endif