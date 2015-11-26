//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 25.11.15.
//

/*****************************************************************************/

#include "libs/controller.hpp"
#include "libs/messages.hpp"

#include "testslib.hpp"

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
