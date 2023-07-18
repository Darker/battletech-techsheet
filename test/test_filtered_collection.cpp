#include "../include/techsheet/iterators/filtered_collection.h"

#include <iostream>
#include <vector>
// g++ -std=c++17 test_structure_manager.cpp -o test.exe
using namespace techsheet;

static bool is_even(const int& i)
{
  return i % 2 == 0;
}

static bool is_odd(const int& i)
{
  return i % 2 == 1;
}

static bool is_divisible_by(const int& i, const int& divider)
{
  return i % divider == 0;
}

int maindsa()
{
  std::array<int, 4> tstv = { 1,2,3,4 };

  filtered_collection<decltype(tstv)> ftest( tstv, &is_even);

  for (auto& v : ftest)
  {
    std::cout << v << ", ";
    v = 2 * v;
  }
  std::cout << "\nmultiplied\n";
  for (const auto& v : tstv)
  {
    std::cout << v << ", ";
  }
  std::cout << "\nodd test\n";

  for (const auto& v : make_filtered(tstv, &is_odd))
  {
    std::cout << v << ", ";
  }

  std::cout << "\nrvalue test\n";

  for (const auto& v : make_filtered(std::array{1,2,3,4}, &is_odd))
  {
    std::cout << v << ", ";
  }
  std::cout << "\nparam test\n";

  for (const auto& v : make_filtered(std::array{ 5, 8, 9, 10, 125, 128 }, 5, &is_divisible_by))
  {
    std::cout << v << ", ";
  }

  return 0;
}