//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 22.11.15.
//

/*****************************************************************************/

// TODO: Переписать на тестирование через контролирующий класс

/*****************************************************************************/

#include "libs/messages.hpp"
#include "testslib.hpp"
#include "libs/time_hm.hpp"
#include "libs/station.hpp"
#include "libs/train.hpp"
#include "libs/train_sched_item.hpp"
#include "libs/route.hpp"

#include <sstream>
#include <cassert>
#include <memory>
#include <utility>

/*****************************************************************************/

DECLARE_OOP_TEST( test_time_default_constructor ) {
	TimeHM testTime;

	assert( testTime.GetHour() == 0 && testTime.GetMinute() == 0 );
}

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
	assert( TimeHM( 10, 15 ) <  TimeHM( 11, 15 ));
	assert( TimeHM( 10, 14 ) <  TimeHM( 10, 15 ));

	assert( TimeHM( 11, 15 ) == TimeHM( 11, 15 ));
	assert( TimeHM( 11, 15 ) <  TimeHM( 11, 15, TimeHM::Day::NextDay ));
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_time_convertation ) {
	assert(
			TimeHM( 11, 15 ).GetMinutesFromMidnight()
			==
			675
	);

	assert(
			TimeHM( 0, 15, TimeHM::Day::NextDay ).GetMinutesFromMidnight()
			==
			1455
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_time_diff ) {
	assert(
			TimeHM::GetDiff( TimeHM( 10, 15 ), TimeHM( 11, 15 ) )
			==
			60
	);

	assert(
			TimeHM::GetDiff( TimeHM( 11, 15 ), TimeHM( 10, 15 ) )
			==
			60
	);

	assert(
			TimeHM::GetDiff( TimeHM( 0, 0 ), TimeHM( 0, 0, TimeHM::Day::NextDay ) )
			==
			1440
	);

	assert(
			TimeHM::GetDiff( TimeHM( 23, 59 ), TimeHM( 00, 00, TimeHM::Day::NextDay ) )
			==
			1
	);

	assert(
			TimeHM::GetDiff( TimeHM( 23, 59 ), TimeHM( 00, 00 ) )
			==
			1439
	);
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

DECLARE_OOP_TEST( test_create_correct_train_sched_item ) {
	Station firstStation( "Station 1", 8 );

	TrainSchedItem testItem( firstStation, {11,15}, {13,10} );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_train_sched_item_with_wrong_time ) {
	Station firstStation( "Station 1", 8 );

	ASSERT_THROWS(
			TrainSchedItem testItem( firstStation, {18,15}, {13,10} );
		,	Messages::DeparturePreceedArrive
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_train_sched_item_arriving_next_day ) {
	Station firstStation( "Station 1", 8 );

	TrainSchedItem testItem( firstStation, {18,15}, {13,10, TimeHM::Day::NextDay } );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_correct_route ) {
	Route testRoute( 10 );

	Station firstStation( "Station 1", 8 );
	Station secondStation( "Station 2", 2 );
	Station thirdStation( "Station 3", 5 );

	testRoute.AddItem( std::make_unique< TrainSchedItem >( firstStation, TimeHM{11,15}, TimeHM{13,10} ) );
	testRoute.AddItem( std::make_unique< TrainSchedItem >( secondStation, TimeHM{15,15}, TimeHM{15,30} ) );
	testRoute.AddItem( std::make_unique< TrainSchedItem >( thirdStation, TimeHM{17,00}, TimeHM{18,10} ) );
}

/*****************************************************************************/

// TODO: Тест с использованием итераторов
/*
DECLARE_OOP_TEST( test_create_correct_route_and_check_with_iterators ) {

}
*/
/*****************************************************************************/

DECLARE_OOP_TEST( test_create_correct_train ) {
	Train( 10, 200 );

	// Train without current route
	Train( 10, 200, nullptr );
}

/*****************************************************************************/

// TODO: Сделать тест с конструктором маршрута
/*
DECLARE_OOP_TEST( test_create_correct_train_with_route ) {
	Train( 10, 200 );
}
*/

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_train_with_wrong_id ) {
	ASSERT_THROWS(
			Train testTrain( -10, 200 );
		,	Messages::NegativeID
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_train_with_wrong_seats_count ) {
	ASSERT_THROWS(
			Train testTrain( 10, -200 );
		,	Messages::NegativeNumberOfSeats
	);
}

/*****************************************************************************/
