#include <boost/test/unit_test.hpp>

#include "route.h"
#include "track.h"

using namespace GPS;

BOOST_AUTO_TEST_SUITE( Track_name )

/* For tracks, .name() should return the name of the track, which is taken from the content of
 * the <name> element (within the <trk> element) in the GPX data that the Track was
 * constructed from.  The name of a track is considered to exclude any blank space at
 * the start or end of that content.
 *
 * The main testing consideration is whether a name is present or absent in the GPX data.
 * A secondary consideration is to test that blank space is correctly dropped.
 *
 * We start by testing a typical input: a route containing a name with no surrounding
 * blank space.
 *
 * We next test for absent names.  There are two possibilites: the <name> element may be
 * missing, or the content of the element may be entirely blank space.  We also test the
 * edge case where the content consists of zero characters.
 *
 * Finally, we test that blank space before and after the name is dropped, including
 * the corner case where there is blank space at both the front and the back of the
 * same name.  We also test that blank space within the name is not dropped.
 */

const std::string defaultName = "Unnamed Route";
const bool isFileName = false; // All GPX data in this suite is provided as strings.

// Check the name of a GPX track containing a non-empty <name> element within <rte>.
BOOST_AUTO_TEST_CASE( typical_name_present )
{
   const std::string gpxData =
     "<gpx><trk><name>MyTrack</name><trkpt lat=\"0\" lon=\"0\"><time>5</time></trkpt></trk></gpx>";
   Track track = Track(gpxData, isFileName);

   BOOST_CHECK_EQUAL( track.name(), "MyTrack" );
}

// Check that the default name is returned for a GPX track without a <name> element.
BOOST_AUTO_TEST_CASE( name_element_absent )
{
   const std::string gpxData =
     "<gpx><trk><trkpt lat=\"0\" lon=\"0\"><time>5</time></trkpt></trk></gpx>";

   Track track = Track(gpxData, isFileName);
   BOOST_CHECK_EQUAL( track.name(), defaultName );
}

// Check that the default name is returned for a GPX track with a blank <name> element.
BOOST_AUTO_TEST_CASE( name_element_blank )
{
   const std::string gpxData =
     "<gpx><trk><name>     </name><trkpt lat=\"0\" lon=\"0\"><time>5</time></trkpt></trk></gpx>";

   Track track = Track(gpxData, isFileName);
   BOOST_CHECK_EQUAL( track.name(), defaultName );
}

// Check that the default name is returned for a GPX track with an empty <name> element.
BOOST_AUTO_TEST_CASE( name_element_empty )
{
   const std::string gpxData =
     "<gpx><trk><name></name><trkpt lat=\"0\" lon=\"0\"><time>5</time></trkpt></trk></gpx>";

   Track track = Track(gpxData, isFileName);
   BOOST_CHECK_EQUAL( track.name(), defaultName );
}

// Check that blank spaces are dropped from the front of a track name.
BOOST_AUTO_TEST_CASE( name_blanks_dropped_front )
{
   const std::string gpxData =
     "<gpx><trk><name>   Journey</name><trkpt lat=\"0\" lon=\"0\"><time>5</time></trkpt></trk></gpx>";
   Track track = Track(gpxData, isFileName);

   BOOST_CHECK_EQUAL( track.name(), "Journey" );
}

// Check that blank spaces are dropped from the back of a track name.
BOOST_AUTO_TEST_CASE( name_blanks_dropped_back )
{
   const std::string gpxData =
     "<gpx><trk><name>Voyage     </name><trkpt lat=\"0\" lon=\"0\"><time>5</time></trkpt></trk></gpx>";
   Track track = Track(gpxData, isFileName);

   BOOST_CHECK_EQUAL( track.name(), "Voyage" );
}

// Check that blank spaces are dropped from both the front and back.
BOOST_AUTO_TEST_CASE( name_blanks_dropped_front_and_back )
{
   const std::string gpxData =
     "<gpx><trk><name>  Travel </name><trkpt lat=\"0\" lon=\"0\"><time>5</time></trkpt></trk></gpx>";
   Track track = Track(gpxData, isFileName);

   BOOST_CHECK_EQUAL( track.name(), "Travel" );
}

// Check that blank spaces are not dropped from within a name.
BOOST_AUTO_TEST_CASE( name_internal_blanks_not_dropped )
{
   const std::string gpxData =
     "<gpx><trk><name>Nice Route</name><trkpt lat=\"0\" lon=\"0\"><time>5</time></trkpt></trk></gpx>";
   Track track = Track(gpxData, isFileName);

   BOOST_CHECK_EQUAL( track.name(), "Nice Route" );
}


BOOST_AUTO_TEST_SUITE_END()
