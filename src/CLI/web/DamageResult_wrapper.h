#pragma once

#include <techsheet/structure.h>
#include <techsheet/structure_static.h>

#include <emscripten/val.h>

struct DamageResult_wrapper
{
  static emscripten::val getCriticalSegment(const techsheet::DamageResult& v)
  {
    return emscripten::val(std::string(techsheet::Internal_getName(v.criticalSegment)));
  }
};