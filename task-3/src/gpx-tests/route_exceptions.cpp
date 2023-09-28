#include <boost/test/unit_test.hpp>

#include <fstream>
#include <stdexcept>

#include "logs.h"
#include "types.h"
#include "route.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Route_Exceptions )

// Check that the Route constructor throws an invalid_argument exception when called with an non-existant file.
BOOST_AUTO_TEST_CASE( nonexistantFile )
{
    const bool isFileName = true;

    std::string fileName = LogFiles::GPXRoutesDir + "NonexistantFile.gpx";
    std::ifstream nullHandle = std::ifstream(fileName);

    // Ensure the file really doesn't exist, otherwise the test won't be valid.
    BOOST_REQUIRE(! nullHandle.good());

    BOOST_REQUIRE_THROW( Route(fileName, isFileName), std::invalid_argument);
    try
    {
        Route(fileName, isFileName);
    }
    catch (std::invalid_argument e)
    {
        BOOST_CHECK_EQUAL( e.what() , "Error opening source file '" + fileName + "'.");
    }
}

// Check that no excepetion is thrown for a valid file input.
BOOST_AUTO_TEST_CASE( acceptsFileInput )
{
    const std::string fileName = LogFiles::GPXRoutesDir + "ABCD.gpx";
    const bool isFileName = true;

    BOOST_CHECK_NO_THROW(Route(fileName, isFileName));
}

// Check that no exception is thrown for a valid GPX string input.
BOOST_AUTO_TEST_CASE( acceptsStringInput )
{
    const std::string source = "<gpx><rte><rtept lat=\"0\" lon=\"0\"><ele>1</ele></rtept></rte></gpx>";
    const bool isFileName = false;

    BOOST_CHECK_NO_THROW(Route(source, isFileName));
}

// An exception is thrown if the 'gpx' element is missing.
BOOST_AUTO_TEST_CASE( missing_gpx_element )
{
    const std::string source = "<rte><rtept lat=\"0\" lon=\"0\"><ele>1</ele></rtept></rte>";
    const bool isFileName = false;

    BOOST_REQUIRE_THROW( Route(source,isFileName) , std::domain_error);
    try
    {
        Route(source, isFileName);
    }
    catch (std::domain_error e)
    {
        BOOST_CHECK_EQUAL( e.what() , "Missing 'gpx' element.");
    }
}

// An exception is thrown if the 'rte' element is missing.
BOOST_AUTO_TEST_CASE( missing_rte_element )
{
    const std::string source = "<gpx><rtept lat=\"0\" lon=\"0\"><ele>1</ele></rtept></gpx>";
    const bool isFileName = false;

    BOOST_REQUIRE_THROW( Route(source,isFileName) , std::domain_error);
    try
    {
        Route(source, isFileName);
    }
    catch (std::domain_error e)
    {
        BOOST_CHECK_EQUAL( e.what() , "Missing 'rte' element.");
    }
}

// An exception is thrown if the 'rtept' element is missing.
BOOST_AUTO_TEST_CASE( missing_rtept_element )
{
    const std::string source = "<gpx><rte></rte></gpx>";
    const bool isFileName = false;

    BOOST_REQUIRE_THROW( Route(source,isFileName) , std::domain_error);
    try
    {
        Route(source, isFileName);
    }
    catch (std::domain_error e)
    {
        BOOST_CHECK_EQUAL( e.what() , "Missing 'rtept' element.");
    }
}

// An exception is thrown if a 'lat' attribute is missing.
BOOST_AUTO_TEST_CASE( missing_lat_attribute )
{
    const std::string source = "<gpx><rte><rtept lon=\"0\"><ele>1</ele></rtept></rte></gpx>";
    const bool isFileName = false;

    BOOST_REQUIRE_THROW( Route(source,isFileName) , std::domain_error);
    try
    {
        Route(source, isFileName);
    }
    catch (std::domain_error e)
    {
        BOOST_CHECK_EQUAL( e.what() , "Missing 'lat' attribute.");
    }
}

// An exception is thrown if a 'lon' attribute is missing.
BOOST_AUTO_TEST_CASE( missing_lon_attribute )
{
    const std::string source = "<gpx><rte><rtept lat=\"0\"><ele>1</ele></rtept></rte></gpx>";
    const bool isFileName = false;

    BOOST_REQUIRE_THROW( Route(source,isFileName) , std::domain_error);
    try
    {
        Route(source, isFileName);
    }
    catch (std::domain_error e)
    {
        BOOST_CHECK_EQUAL( e.what() , "Missing 'lon' attribute.");
    }
}

BOOST_AUTO_TEST_SUITE_END()
