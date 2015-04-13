/**
   statki library tests
   defines 'main' for cpp unit test
**/

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>


#include "../src/statki.hpp"

using namespace boost;
using boost::unit_test::test_suite;

BOOST_AUTO_TEST_SUITE( statki_tests )

//BOOST_AUTO_TEST_CASE( TestGetNumber )
//{
//	BOOST_CHECK_EQUAL( getNumber(), 1234 );
//}

BOOST_AUTO_TEST_SUITE_END()
