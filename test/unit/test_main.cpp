//#define BOOST_TEST_MODULE "Techsheet core library tests"
#define BOOST_TEST_ALTERNATIVE_INIT_API
#include <boost/test/included/unit_test.hpp>

#include "suite_registry.h"

namespace techsheet
{
namespace unit
{
Registry& Registry::Instance()
{
  static Registry r;
  return r;
}
}
}
using namespace boost::unit_test;

bool init_unit_test()
{
  for (test_suite* s : techsheet::unit::Registry::Instance().all())
  {
    framework::master_test_suite().add(s);
  }

  return true;
}