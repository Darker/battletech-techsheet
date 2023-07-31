#include "techsheet/structure.h"

#include <boost/test/included/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

#include <algorithm>
#include <iostream>

using namespace techsheet;
using namespace boost::unit_test;

template <typename T>
void test_subtract_clamp(const std::pair<T, T> operands)
{
  const T& minuend = operands.first;
  const T& subtrahend = operands.second;
  const int unclamped = static_cast<int>(minuend.value) - static_cast<int>(subtrahend.value);
  const auto result = minuend.substract_clamp(subtrahend);
  const int expected = std::clamp(unclamped, static_cast<int>(T::min_base_value), static_cast<int>(T::max_base_value));
  BOOST_CHECK_EQUAL(static_cast<int>(result.value), expected);
}

template <typename T>
void test_add_clamp(const std::pair<T, T> operands)
{
  const T& addend1 = operands.first;
  const T& addend2 = operands.second;
  const int unclamped = static_cast<int>(addend1.value) + static_cast<int>(addend2.value);
  const auto result = addend1.add_clamp(addend2);
  const int expected = std::clamp(unclamped, static_cast<int>(T::min_base_value), static_cast<int>(T::max_base_value));
  BOOST_CHECK_EQUAL(static_cast<int>(result.value), expected);
}

test_suite* init_unit_test_suite( int /*argc*/, char* /*argv*/[] )
{
  using param_t = health;
  const std::pair<param_t, param_t> params[] = {
    {health{5}, health{5}},
    {health{5}, health{6}},
    {health{5}, health{4}},
    {health{3}, health{255}}
  };

  framework::master_test_suite().add(BOOST_PARAM_TEST_CASE(&test_subtract_clamp<param_t>, params, params+4));

  return 0;
}
