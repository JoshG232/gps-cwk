#include <boost/test/unit_test.hpp>

#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Point_names_trimming_and_bugs )

const bool isFileName = false; // All GPX data in this suite is provided as strings.
const std::string defaultName = "Unnamed Position";

// Check that whitespace is trimmed from route-point names.
BOOST_AUTO_TEST_CASE( rtept_trimmedName )
{
    const std::string pt1 = "<rtept lat=\"1\" lon=\"1\"><name>      Point 1</name></rtept>";
    const std::string pt2 = "<rtept lat=\"2\" lon=\"2\"><name>Point 2   </name></rtept>";
    const std::string pt3 = "<rtept lat=\"3\" lon=\"3\"><name>   Point 3 </name></rtept>";
    const std::string gpxData = "<gpx><rte><name>My Route</name>" + pt1 + pt2 + pt3 + "</rte></gpx>";

    Route route = Route(gpxData, false);

    BOOST_CHECK_EQUAL( route.findNameOf(Position(1,1)), "Point 1" );
    BOOST_CHECK_EQUAL( route.findNameOf(Position(2,2)), "Point 2" );
    BOOST_CHECK_EQUAL( route.findNameOf(Position(3,3)), "Point 3" );
}

// Check that whitespace is trimmed from track-point names.
BOOST_AUTO_TEST_CASE( trkpt_trimmedName )
{
    const std::string pt1 = "<trkpt lat=\"1\" lon=\"1\"><name>      Point 1</name><time>5</time></trkpt>";
    const std::string pt2 = "<trkpt lat=\"2\" lon=\"2\"><name>Point 2   </name><time>10</time></trkpt>";
    const std::string pt3 = "<trkpt lat=\"3\" lon=\"3\"><name>   Point 3 </name><time>15</time></trkpt>";
    const std::string gpxData = "<gpx><trk><name>Nice Route</name>" + pt1 + pt2 + pt3 + "</trk></gpx>";

    Track track = Track(gpxData, false);

    BOOST_CHECK_EQUAL( track.findNameOf(Position(1,1)), "Point 1" );
    BOOST_CHECK_EQUAL( track.findNameOf(Position(2,2)), "Point 2" );
    BOOST_CHECK_EQUAL( track.findNameOf(Position(3,3)), "Point 3" );
}

// Check that route names aren't used as point names.
BOOST_AUTO_TEST_CASE( route_name_not_used_as_rtept_name )
{
    const std::string gpxData = "<gpx><rte><name>My Route</name><rtept lat=\"0\" lon=\"0\"></rtept></rte></gpx>";

    Route route = Route(gpxData, false);

    BOOST_CHECK_EQUAL( route.findNameOf(Position(0,0)), defaultName );
}

// Check that previous route-point names aren't used for subsequent missing point names.
BOOST_AUTO_TEST_CASE( previous_rtept_name_not_carried )
{
    const std::string pt1 = "<rtept lat=\"1\" lon=\"1\"><name>Point 1</name></rtept>";
    const std::string pt2 = "<rtept lat=\"2\" lon=\"2\"></rtept>";

    const std::string gpxData = "<gpx><rte><name>My Route</name>" + pt1 + pt2 + "</rte></gpx>";

    Route route = Route(gpxData, false);

    BOOST_CHECK_EQUAL( route.findNameOf(Position(2,2)), defaultName );
}

// Check that track names aren't used as point names.
BOOST_AUTO_TEST_CASE( track_name_not_used_as_trkpt_name )
{
    const std::string gpxData = "<gpx><trk><name>My Track</name><trkpt lat=\"0\" lon=\"0\"><time>5</time></trkpt></trk></gpx>";

    Track track = Track(gpxData, false);

    BOOST_CHECK_EQUAL( track.findNameOf(Position(0,0)), defaultName );
}

// Check that previous track-point names aren't used for subsequent missing point names.
BOOST_AUTO_TEST_CASE( previous_trkpt_name_not_carried )
{
    const std::string pt1 = "<trkpt lat=\"1\" lon=\"1\"><name>Point 1</name><time>5</time></trkpt>";
    const std::string pt2 = "<trkpt lat=\"2\" lon=\"2\"><time>10</time></trkpt>";

    const std::string gpxData = "<gpx><trk><name>My Track</name>" + pt1 + pt2 + "</trk></gpx>";

    Track track = Track(gpxData, false);

    BOOST_CHECK_EQUAL( track.findNameOf(Position(2,2)), defaultName );
}

BOOST_AUTO_TEST_SUITE_END()
