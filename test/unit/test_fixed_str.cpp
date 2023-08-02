#include <techsheet/fixed_str.h>
#include <techsheet/std_cout_printing.h>
#include <techsheet/types.h>

#include <boost/test/unit_test.hpp>
#include <boost/test/parameterized_test.hpp>

#include <algorithm>
#include <iostream>

using namespace techsheet;
using namespace boost::unit_test;

namespace boost::test_tools::tt_detail
{

// teach Boost.Test how to print std::vector<T>
template <size_t str_max_size>
struct print_log_value<techsheet::fixed_str<str_max_size>>
{
  inline void operator()(::std::ostream& str, techsheet::fixed_str<str_max_size> const& string)
  {
    str << string.view();
  }
};
}

BOOST_AUTO_TEST_SUITE(test_fixed_str)

namespace techsheet::unit
{
BOOST_AUTO_TEST_CASE(test_add_str)
{
  fixed_str sshort{ "abc" };

  // adding more characters to sshort is not possible
  fixed_str<6> slong = sshort + "123";
  BOOST_CHECK_EQUAL(slong, "abc");
  BOOST_CHECK_EQUAL(slong, sshort.view());
  BOOST_CHECK_NE(slong, "abc123");

  slong = slong + "123";
  BOOST_CHECK_EQUAL(slong, "abc123");
  BOOST_CHECK_NE(slong, "abc");
}
BOOST_AUTO_TEST_CASE(test_find_in_str)
{
  fixed_str sshort{ "aabbcc" };
  BOOST_CHECK(sshort.startsWith("aab"));
  BOOST_CHECK(sshort.endsWith("bcc"));
  BOOST_CHECK(sshort.startsWith("aabbcc"));
  BOOST_CHECK(sshort.startsWith(sshort));
  BOOST_CHECK(sshort.endsWith("aabbcc"));
  BOOST_CHECK(sshort.endsWith(sshort));

  BOOST_CHECK(sshort.contains("abbc"));
  BOOST_CHECK(sshort.contains(sshort));
  BOOST_CHECK(!sshort.contains("ccc"));
  BOOST_CHECK(!sshort.contains("abc"));
}

BOOST_AUTO_TEST_CASE(test_create_str)
{
  fixed_str literal{ "aabbcc" };
  fixed_str<16> explicit_s = "aabbcc";
  fixed_str<32> copy_to_large = explicit_s;
  fixed_str<20> expanded = literal.expand<18>();
  fixed_str<3> cropped = literal.view();

  BOOST_CHECK_EQUAL(literal, explicit_s);
  BOOST_CHECK_EQUAL(literal, copy_to_large);
  BOOST_CHECK_EQUAL(literal, expanded);
  BOOST_CHECK_EQUAL(explicit_s, copy_to_large);
  BOOST_CHECK_EQUAL(explicit_s, expanded);

  BOOST_CHECK(literal.startsWith(cropped));
}
}

BOOST_AUTO_TEST_SUITE_END()
