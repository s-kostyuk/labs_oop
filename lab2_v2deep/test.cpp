//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 25.11.15.
//

/*****************************************************************************/

#include "libs/controller.hpp"
#include "libs/messages.hpp"

#include "testslib.hpp"

#include <sstream>

/*****************************************************************************/

void CreateSampleRoute( Controller & _c, const RouteID _id ) {
	_c.addStation( "first station", 8 );
	_c.addStation( "second station", 3 );
	_c.addStation( "third station", 5 );

	_c.declareNewRoute( _id );

	_c.addRouteItem( _id, "first station", { 11, 15 }, { 11, 30 } );
	_c.addRouteItem( _id, "second station", { 13, 10 }, { 13, 40 } );
	_c.addRouteItem( _id, "first station", { 14, 32 }, { 14, 50 } );
	_c.addRouteItem( _id, "third station", { 23, 15 }, { 00, 30, TimeHM::Day::NextDay } );

	_c.settleRoute( _id );
}

/*****************************************************************************/

void CreateSampleSchedule( Controller & _c ) {
	// К-во платформ от балды

	_c.addStation( "Kharkiv-Pas.", 20 );
	_c.addStation( "Poltava-Kyivs'ka", 8 );
	_c.addStation( "Mirgorod", 7 );
	_c.addStation( "Darnytsia", 10 );
	_c.addStation( "Kyiv-Pas.", 20 );

	_c.declareNewRoute( 725 );

	_c.addRouteItem( 725, "Kharkiv-Pas.", { 07, 00 }, { 07, 23 } );
	_c.addRouteItem( 725, "Poltava-Kyivs'ka", { 8, 57 }, { 8, 59 } );
	_c.addRouteItem( 725, "Mirgorod", { 9, 50 }, {  9, 52 } );
	_c.addRouteItem( 725, "Darnytsia", { 11, 46 }, { 11, 48 } );
	_c.addRouteItem( 725, "Kyiv-Pas.", { 12, 01 }, { 13, 30 } );

	_c.settleRoute( 725 );

	assert( _c.findRoute( 725 )->GetDuration() == (4 * 60 + 38) );

	_c.declareNewRoute( 113 );

	_c.addStation( "Shepetivka-1", 8 );
	_c.addStation( "Korosten-Pz", 7 );
	_c.addStation( "Novohrad-Volyn-1", 10 );
	_c.addStation( "Zdolbuniv-Pas.", 10 );

	_c.addRouteItem( 113, "Kharkiv-Pas.", { 18, 00 }, { 19, 05 } );
	_c.addRouteItem( 113, "Poltava-Kyivs'ka", { 21, 30 }, { 21, 32 } );
	_c.addRouteItem( 113, "Kyiv-Pas.", { 00, 55, TimeHM::Day::NextDay }, { 01, 15, TimeHM::Day::NextDay } );
	_c.addRouteItem( 113, "Korosten-Pz", { 02, 58, TimeHM::Day::NextDay }, { 03, 00, TimeHM::Day::NextDay } );
	_c.addRouteItem( 113, "Novohrad-Volyn-1", { 03, 52, TimeHM::Day::NextDay }, { 03, 54, TimeHM::Day::NextDay } );
	_c.addRouteItem( 113, "Shepetivka-1", { 04, 35, TimeHM::Day::NextDay }, { 04, 37, TimeHM::Day::NextDay } );
	_c.addRouteItem( 113, "Zdolbuniv-Pas.", { 05, 27, TimeHM::Day::NextDay }, { 05, 57, TimeHM::Day::NextDay } );

	_c.settleRoute( 113 );

	_c.declareNewRoute( 723 );

	_c.addRouteItem( 723, "Kharkiv-Pas.", { 13, 16 }, { 13, 16 } );
	_c.addRouteItem( 723, "Poltava-Kyivs'ka", { 14, 51 }, { 14, 53 } );
	_c.addRouteItem( 723, "Mirgorod", { 15, 42 }, { 15, 44 } );
	_c.addRouteItem( 723, "Darnytsia", { 17, 38 }, { 17, 40 } );
	_c.addRouteItem( 723, "Kyiv-Pas.", { 17, 53 }, { 17, 53 } );

	_c.settleRoute( 723 );

	_c.declareNewRoute( 112 );

	_c.addStation( "L'viv", 18 );

	_c.addRouteItem( 112, "Kyiv-Pas.", { 02, 07 }, { 02, 35 } );
	_c.addRouteItem( 112, "L'viv", { 05, 07 }, { 05, 17 } );
	_c.addRouteItem( 112, "Poltava-Kyivs'ka", { 07, 56 }, {  8, 01 } );
	_c.addRouteItem( 112, "Kharkiv-Pas.", { 12, 21 }, { 12, 21 } );

	_c.settleRoute( 112 );

	_c.declareNewRoute( 128 );

	_c.addStation( "Smorodyne", 2 );
	_c.addStation( "Sumy", 8 );
	_c.addStation( "Pytivl", 5 );
	_c.addStation( "Konotop-Pas.", 3 );
	_c.addStation( "Bakhmach-Pas.", 6 );
	_c.addStation( "Nizhyn", 7 );
	_c.addStation( "Vorozhba-Pas.", 7 );

	_c.addRouteItem( 128, "Smorodyne", { 1, 27 }, { 1, 30 } );
	_c.addRouteItem( 128, "Sumy", { 2, 30 }, { 2, 40 } );
	_c.addRouteItem( 128, "Vorozhba-Pas.", { 3, 35 }, { 3, 57 } );
	_c.addRouteItem( 128, "Pytivl", { 4, 30 }, { 4, 32 } );
	_c.addRouteItem( 128, "Konotop-Pas.", { 5, 22 }, { 5, 27 } );
	_c.addRouteItem( 128, "Bakhmach-Pas.", { 5, 52 }, { 06, 00 } );
	_c.addRouteItem( 128, "Nizhyn", { 06, 55 }, { 07, 05 } );
	_c.addRouteItem( 128, "Kyiv-Pas.", { 8, 40 }, { 9, 18 } );

	_c.settleRoute( 128 );

	// Random
	_c.declareNewRoute( 511 );

	_c.addRouteItem( 511, "Smorodyne", { 16, 30 }, { 16, 30 } );
	_c.addRouteItem( 511, "Pytivl", { 17, 54 }, { 18, 00 } );
	_c.addRouteItem( 511, "Bakhmach-Pas.", { 19, 00 }, { 19, 20 } );

	_c.settleRoute( 511 );

	// Random
	_c.declareNewRoute( 652 );

	_c.addRouteItem( 652, "Pytivl", { 14, 54 }, { 15, 00 } );
	_c.addRouteItem( 652, "Smorodyne", { 16, 20 }, { 16, 40 } );
	_c.addRouteItem( 652, "Bakhmach-Pas.", { 19, 00 }, { 19, 20 } );

	_c.settleRoute( 652 );

	// Random
	_c.declareNewRoute( 775 );

	_c.addRouteItem( 775, "Konotop-Pas.", { 10, 54 }, { 11, 00 } );
	_c.addRouteItem( 775, "Sumy", { 13, 00 }, { 13, 20 } );
	_c.addRouteItem( 775, "Smorodyne", { 16, 20 }, { 16, 40 } );
	_c.addRouteItem( 775, "Kyiv-Pas.", { 19, 00 }, { 19, 20 } );

	_c.settleRoute( 775 );

	// Random
	_c.declareNewRoute( 20 );

	_c.addRouteItem( 20, "Nizhyn", { 17, 54 }, { 18, 00 } );
	_c.addRouteItem( 20, "Sumy", { 19, 00 }, { 19, 20 } );
	_c.addRouteItem( 20, "Kharkiv-Pas.", { 20, 20 }, { 20, 30 } );
	_c.addRouteItem( 20, "Kyiv-Pas.", { 23, 59 }, { 23, 59 } );

	_c.settleRoute( 20 );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_controller_default_constructor ) {
	Controller c;
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_add_station ) {
	Controller c;

	c.addStation( "Station 1", 4 );

	assert(
			*c.findStation( "Station 1" )
			==
			Station( "Station 1", 4 )
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_add_station_with_empty_name ) {
	Controller c;

	ASSERT_THROWS(
			c.addStation( "", 4 ),
	        Messages::StationNameIsEmpty
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_add_station_with_negative_n_of_platforms ) {
	Controller c;

	ASSERT_THROWS(
			c.addStation( "Station 1", -1 ),
			Messages::NegativePlatfromsOnStation
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_add_station_without_platforms ) {
	Controller c;

	ASSERT_THROWS(
			c.addStation( "Station 1", 0 ),
			Messages::StationWithoutPlatfroms
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_add_duplicate_stations ) {
	Controller c;

	c.addStation( "Station", 10 );

	ASSERT_THROWS(
			c.addStation( "Station", 10 ),
	        Messages::DuplicateStationNames
	);

	ASSERT_THROWS(
			c.addStation( "Station", 11 ),
			Messages::DuplicateStationNames
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_correct_route ) {
	Controller c;

	CreateSampleRoute( c, 10 );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_settle_empty_route ) {
	Controller c;

	c.declareNewRoute( 10 );

	ASSERT_THROWS(
			c.settleRoute( 10 ),
	        Messages::RouteIsEmpty
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_route_double_settled ) {
	Controller c;

	CreateSampleRoute( c, 10 );

	ASSERT_THROWS(
			c.settleRoute( 10 ),
			Messages::RouteAlreadySettled
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_double_creation_of_unfinished_route ) {
	Controller c;

	c.declareNewRoute( 10 );

	ASSERT_THROWS(
			c.declareNewRoute( 10 ),
	        Messages::UnsettledRouteExist
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_route_with_duplicate_id ) {
	Controller c;

	CreateSampleRoute( c, 10 );

	ASSERT_THROWS(
			c.declareNewRoute( 10 ),
	        Messages::DuplicateRouteID
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_route_with_unknown_station ) {
	Controller c;

	c.declareNewRoute( 10 );

	ASSERT_THROWS(
			c.addRouteItem( 10, "Chupakabra station", { 00, 00 }, { 00, 01 } ),
	        Messages::UnknownStation
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_route_with_negative_id ) {
	Controller c;

	ASSERT_THROWS(
			c.declareNewRoute( -10 ),
			Messages::NegativeID
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_route_with_succesively_repeated_station ) {
	Controller c;

	c.declareNewRoute( 10 );

	c.addStation( "Depot", 20 );

	c.addRouteItem( 10, "Depot", { 12, 00 }, { 22, 00 } );

	ASSERT_THROWS(
			c.addRouteItem( 10, "Depot", { 23, 00 }, { 01, 00, TimeHM::Day::NextDay } ),
			Messages::StationRepeatsSuccessively
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_route_with_wrong_item_order ) {
	Controller c;

	c.declareNewRoute( 10 );

	c.addStation( "Station 1", 5 );
	c.addStation( "Station 2", 7 );

	c.addRouteItem( 10, "Station 1", { 12, 00 }, { 13, 00 } );

	ASSERT_THROWS(
			c.addRouteItem( 10, "Station 2", { 11, 00 }, { 11, 15 } ),
			Messages::WrongRoutePointsOrder
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_route_with_invalid_time ) {
	Controller c;

	c.declareNewRoute( 10 );

	c.addStation( "Station 1", 5 );

	ASSERT_THROWS(
			c.addRouteItem( 10, "Station 1", { 312, 00 }, { 400, 00 } ),
			Messages::TimeIsInvalid
	);

	ASSERT_THROWS(
			c.addRouteItem( 10, "Station 1", { 12, 400 }, { 13, 00 } ),
			Messages::TimeIsInvalid
	);

	ASSERT_THROWS(
			c.addRouteItem( 10, "Station 1", { -1, 00 }, { 1, 00 } ),
			Messages::TimeIsInvalid
	);

	ASSERT_THROWS(
			c.addRouteItem( 10, "Station 1", { 00, -10 }, { 1, 20 } ),
			Messages::TimeIsInvalid
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_route_with_departute_preceed_arrive ) {
	Controller c;

	c.declareNewRoute( 10 );

	c.addStation( "Station 1", 5 );

	ASSERT_THROWS(
			c.addRouteItem( 10, "Station 1", { 12, 00 }, { 11, 00 } ),
			Messages::DeparturePreceedArrive
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_route_with_intersected_item_time ) {
	Controller c;

	c.declareNewRoute( 10 );

	c.addStation( "Station 1", 5 );
	c.addStation( "Station 2", 7 );

	c.addRouteItem( 10, "Station 1", { 12, 00 }, { 12, 15 } );

	ASSERT_THROWS(
			c.addRouteItem( 10, "Station 2", { 12, 05 }, { 12, 30 } ),
			Messages::RouteItemTimeIntersect
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_and_use_correct_route_with_train ) {
	Controller c;

	CreateSampleRoute( c, 10 );

	c.addTrain( 15, 200, 10 );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_add_train_without_route ) {
	Controller c;

	c.addTrain( 10, 200 );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_add_train_with_negative_id ) {
	Controller c;

	ASSERT_THROWS(
			c.addTrain( -1, 200 ),
			Messages::NegativeID
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_add_train_with_negative_n_of_seats ) {
	Controller c;

	ASSERT_THROWS(
			c.addTrain( 10, -1 ),
			Messages::NegativeNumberOfSeats
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_add_train_with_duplicate_id ) {
	Controller c;

	c.addTrain( 10, 200 );

	ASSERT_THROWS(
			c.addTrain( 10, 12 ),
	        Messages::DuplicateTrainIDs
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_train_on_unfinished_route ) {
	Controller c;

	c.declareNewRoute( 10 );

	ASSERT_THROWS(
			c.addTrain( 10, 200, 10 ),
			Messages::UsageOfUnfinishedRoute
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_train_on_unfinished_route_2 ) {
	Controller c;

	c.declareNewRoute( 10 );

	c.addStation( "Station", 7 );

	c.addRouteItem( 10, "Station", { 11, 15 }, { 11, 30 } );

	ASSERT_THROWS(
			c.addTrain( 10, 200, 10 ),
			Messages::UsageOfUnfinishedRoute
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_train_on_non_existent_route ) {
	Controller c;

	ASSERT_THROWS(
			c.addTrain( 10, 200, 10 ),
			Messages::RouteDoesntExist
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_train_set_correct_route ) {
	Controller c;

	CreateSampleRoute( c, 10 );

	c.declareNewRoute( 11 );

	c.addRouteItem( 11, "first station", { 12, 45 }, { 13, 10 } );
	c.addRouteItem( 11, "second station", { 15, 15 }, { 15, 30 } );

	c.settleRoute( 11 );

	c.addTrain( 10, 200, 10 );

	c.setTrainRoute( 10, 11 );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_train_set_correct_n_of_seats ) {
	Controller c;

	c.addTrain( 10, 200 );

	c.setTrainNOfSeats( 10, 250 );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_train_uncorrect_sets ) {
	Controller c;

	const TrainID trainId = 10;
	const RouteID routeId = 10;

	CreateSampleRoute( c, routeId );

	c.addTrain( trainId, 200 );

	c.setTrainNOfSeats( trainId, 250 );

	ASSERT_THROWS(
			c.setTrainNOfSeats( trainId, -1 ),
	        Messages::NegativeNumberOfSeats
	);

	ASSERT_THROWS(
			c.setTrainNOfSeats( 120, 210 ),
	        Messages::UnknownTrain
	);

	ASSERT_THROWS(
			c.setTrainNOfSeats( -1, 210 ),
			Messages::UnknownTrain
	);

	ASSERT_THROWS(
			c.setTrainRoute( -1, routeId ),
	        Messages::UnknownTrain
	);

	ASSERT_THROWS(
			c.setTrainRoute( trainId, 11 ),
			Messages::RouteDoesntExist
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_print_busiest_stations ) {
	Controller c;

	CreateSampleSchedule( c );

	std::stringstream ss;

	c.printBusiestStations( ss );

	assert( ss.str() == "\nKyiv-Pas.\t7\n"
			                    "Kharkiv-Pas.\t5\n"
			                    "Smorodyne\t4\n"
			                    "Poltava-Kyivs'ka\t4\n"
			                    "Bakhmach-Pas.\t3" );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_print_slowest_routes ) {
	Controller c;

	CreateSampleSchedule( c );

	std::stringstream ss;

	c.printSlowestRoutes( ss );

	assert( ss.str() == "\n113\tKharkiv-Pas.\tZdolbuniv-Pas.\t622\n"
			                    "112\tKyiv-Pas.\tKharkiv-Pas.\t586\n"
			                    "775\tKonotop-Pas.\tKyiv-Pas.\t480\n"
			                    "128\tSmorodyne\tKyiv-Pas.\t430\n"
			                    "20\tNizhyn\tKyiv-Pas.\t359" );
}

/*****************************************************************************/
