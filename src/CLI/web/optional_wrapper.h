#pragma once
#ifdef __EMSCRIPTEN__
#include <optional>

#include <emscripten/emscripten.h>
#include <emscripten/bind.h>


template<typename OptionalType>
struct OptionalAccess
{
  static emscripten::val value(
    const OptionalType& v)
  {
    return emscripten::val(v.value());
  }

  static bool has_value(OptionalType& v)
  {
    return v.has_value();
  }
};

template<typename V>
emscripten::class_<std::optional<V>> register_optional(const char* name)
{
  typedef std::optional<V> OptionalType;

  return emscripten::class_<std::optional<V>>(name)
    .template constructor()
    .function("value", &OptionalAccess<OptionalType>::value)
    .function("has_value", &OptionalAccess<OptionalType>::has_value);
}

#endif