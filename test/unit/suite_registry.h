#pragma once
#include <vector>
#include <functional>

namespace boost
{
namespace unit_test
{
class test_suite;
}
}

namespace techsheet
{
namespace unit
{
class Registry
{
public:
  static Registry& Instance();
  struct UnusedResult {};

  const std::vector<boost::unit_test::test_suite*>& all() const
  {
    return suites;
  }

  static UnusedResult add(std::function<boost::unit_test::test_suite*(void)> factory)
  {
    auto& inst = Instance();
    inst.suites.push_back(factory());
    return {};
  }
private:
  Registry()
  {
  }
  std::vector<boost::unit_test::test_suite*> suites;

};

}
}