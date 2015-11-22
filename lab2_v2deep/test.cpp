//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 22.11.15.
//

/*****************************************************************************/

#include "messages.hpp"
#include "testslib.hpp"
#include "time_hm.hpp"
#include "station.hpp"

#include <sstream>
#include <cassert>

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_valid_time ) {
	const int h = 10;
	const int m = 5;

	TimeHM testTime( h, m );

	assert( testTime.GetHour() == h && testTime.GetMinute() == m );

	TimeHM testTime2( 23, 59 );
	TimeHM testTime3( 0, 0 );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_invalid_time ) {
	ASSERT_THROWS(
	TimeHM testTime( 100, 5 )
	,	Messages::TimeIsInvalid
	);

	ASSERT_THROWS(
		TimeHM testTime( 24, 0 )
	,	Messages::TimeIsInvalid
	);

	ASSERT_THROWS(
		TimeHM testTime( -10, -10 )
	,	Messages::TimeIsInvalid
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_time_print ) {
	TimeHM testTime( 10, 05 );

	std::stringstream buf;

	buf << testTime;

	assert( buf.str() == "10:05" );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_time_print_midnight ) {
	TimeHM testTime( 0, 0 );

	std::stringstream buf;

	buf << testTime;

	assert( buf.str() == "0:00" );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_time_compations ) {
	assert( TimeHM( 10, 15 ) < TimeHM( 11, 15 ) );
	assert( TimeHM( 10, 14 ) < TimeHM( 10, 15 ) );

	assert( TimeHM( 11, 15 ) == TimeHM( 11, 15 ) );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_correct_station ) {
	const std::string sName = "Station 1";

	const int nOfPlatfroms = 8;

	Station testS( sName, nOfPlatfroms );

	assert( testS.GetName() == sName && testS.GetNOfPlatfroms() == nOfPlatfroms );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_station_with_empty_name ) {
	ASSERT_THROWS(
			Station testStation( "", 1 );
		,	Messages::StationNameIsEmpty
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_station_without_platforms ) {
	ASSERT_THROWS(
			Station testStation( "Station 1", 0 );
		,	Messages::StationWithoutPlatfroms
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_station_with_negative_platforms ) {
	ASSERT_THROWS(
			Station testStation( "Station 1", -1 );
		,	Messages::NegativePlatfromsOnStation
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_equal_stations ) {
	// Имя - уникальный идентификатор для станции.
	// Два объекта типа Station считаются идентичными, если их имена совпадают.

	assert( Station( "Station 1", 8 ) == Station( "Station 1", 9 ) );
	assert( !( Station( "Station 2", 8 ) == Station( "Station 1", 8 ) ) );
}

/*****************************************************************************/
