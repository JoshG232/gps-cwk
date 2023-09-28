#include <boost/test/unit_test.hpp>

#include <fstream>
#include <stdexcept>

#include "logs.h"
#include "types.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Track_Exceptions )

// Check that the Track constructor throws an invalid_argument exception when called with an non-existant file.
BOOST_AUTO_TEST_CASE( nonexistantFile )
{
    const bool isFileName = true;

    std::string fileName = LogFiles::GPXTracksDir + "NonexistantFile.gpx";
    std::ifstream nullHandle = std::ifstream(fileName);

    // Ensure the file really doesn't exist, otherwise the test won't be valid.
    BOOST_REQUIRE(! nullHandle.good());

    BOOST_REQUIRE_THROW( Track(fileName, isFileName), std::invalid_argument);
    try
    {
        Track(fileName, isFileName);
    }
    catch (std::invalid_argument e)
    {
        BOOST_CHECK_EQUAL( e.what() , "Error opening source file '" + fileName + "'.");
    }
}

// Check that no excepetion is thrown for a valid file input.
BOOST_AUTO_TEST_CASE( acceptsFileInput )
{
    const std::string fileName = LogFiles::GPXTracksDir + "A1B3C.gpx";
    const bool isFileName = true;

    BOOST_CHECK_NO_THROW(Track(fileName, isFileName));
}

// Check that no exception is thrown for a valid GPX string input.
BOOST_AUTO_TEST_CASE( acceptsStringInput )
{
    const std::string source = "<gpx><trk><trkpt lat=\"0\" lon=\"0\"><ele>1</ele><time>5</time></trkpt></trk></gpx>";
    const bool isFileName = false;

    BOOST_CHECK_NO_THROW(Track(source, isFileName));
}

// An exception is thrown if the 'gpx' element is missing.
BOOST_AUTO_TEST_CASE( missing_gpx_element )
{
    const std::string source = "<trk><trkpt lat=\"0\" lon=\"0\"><ele>1</ele><time>5</time></trkpt></trk>";
    const bool isFileName = false;

    BOOST_REQUIRE_THROW( Track(source,isFileName) , std::domain_error);
    try
    {
        GPS::Track(source, isFileName);
    }
    catch (std::domain_error e)
    {
        BOOST_CHECK_EQUAL( e.what() , "Missing 'gpx' element.");
    }
}

// An exception is thrown if the 'trk' element is missing.
BOOST_AUTO_TEST_CASE( missing_rte_element )
{
    const std::string source = "<gpx><trkpt lat=\"0\" lon=\"0\"><ele>1</ele><time>5</time></trkpt></gpx>";
    const bool isFileName = false;

    BOOST_REQUIRE_THROW( Track(source,isFileName) , std::domain_error);
    try
    {
        GPS::Track(source, isFileName);
    }
    catch (std::domain_error e)
    {
        BOOST_CHECK_EQUAL( e.what() , "Missing 'trk' element.");
    }
}

// An exception is thrown if the 'trkpt' element is missing.
BOOST_AUTO_TEST_CASE( missing_rtept_element )
{
    const std::string source = "<gpx><trk></trk></gpx>";
    const bool isFileName = false;

    BOOST_REQUIRE_THROW( Track(source,isFileName) , std::domain_error);
    try
    {
        GPS::Track(source, isFileName);
    }
    catch (std::domain_error e)
    {
        BOOST_CHECK_EQUAL( e.what() , "Missing 'trkpt' element.");
    }
}

// An exception is thrown if a 'lat' attribute is missing.
BOOST_AUTO_TEST_CASE( missing_lat_attribute )
{
    const std::string source = "<gpx><trk><trkpt lon=\"0\"><ele>1</ele><time>5</time></trkpt></trk></gpx>";
    const bool isFileName = false;

    BOOST_REQUIRE_THROW( Track(source,isFileName) , std::domain_error);
    try
    {
        GPS::Track(source, isFileName);
    }
    catch (std::domain_error e)
    {
        BOOST_CHECK_EQUAL( e.what() , "Missing 'lat' attribute.");
    }
}

// An exception is thrown if a 'lon' attribute is missing.
BOOST_AUTO_TEST_CASE( missing_lon_attribute )
{
    const std::string source = "<gpx><trk><trkpt lat=\"0\"><ele>1</ele><time>5</time></trkpt></trk></gpx>";
    const bool isFileName = false;

    BOOST_REQUIRE_THROW( Track(source,isFileName) , std::domain_error);
    try
    {
        GPS::Track(source, isFileName);
    }
    catch (std::domain_error e)
    {
        BOOST_CHECK_EQUAL( e.what() , "Missing 'lon' attribute.");
    }
}

// An exception is thrown if a 'time' element is missing.
BOOST_AUTO_TEST_CASE( missing_time_element )
{
    const std::string source = "<gpx><trk><trkpt lat=\"0\" lon=\"0\"><ele>1</ele></trkpt></trk></gpx>";
    const bool isFileName = false;

    BOOST_REQUIRE_THROW( Track(source,isFileName) , std::domain_error);
    try
    {
        GPS::Track(source, isFileName);
    }
    catch (std::domain_error e)
    {
        BOOST_CHECK_EQUAL( e.what() , "Missing 'time' element.");
    }
}

BOOST_AUTO_TEST_SUITE_END()

