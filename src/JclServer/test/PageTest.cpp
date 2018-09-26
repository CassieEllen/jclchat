#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PulseTest

#include <boost/test/unit_test.hpp>

#include <JclServer/Page.hpp>

using namespace jcl;

BOOST_AUTO_TEST_SUITE(Page_test_suite)

BOOST_AUTO_TEST_CASE(Page_ctor)
{
    //Page();
}

#if 0
BOOST_AUTO_TEST_CASE(uncaughtException)
{
    throw "Catch me if you can!";
}
#endif

BOOST_AUTO_TEST_SUITE_END()