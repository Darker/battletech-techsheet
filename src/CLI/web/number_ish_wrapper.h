#pragma once
#ifdef __EMSCRIPTEN__
#include <techsheet/NumberIsh.h>

#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
//
//template <typename NumberIshDerived>
//struct NumberWrapper
//{
//  static emscripten::val value(
//    const NumberIshDerived& v)
//  {
//    return emscripten::val(v.value);
//  }
//};
//
//template<typename Derived>
//emscripten::class_<Derived> register_number_ish(const char* name)
//{
//  return emscripten::class_<Derived>(name)
//    .function("value", &NumberWrapper<Derived>::value);
//}

#endif