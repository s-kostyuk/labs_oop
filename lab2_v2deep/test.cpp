//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 25.11.15.
//

/*****************************************************************************/

#include "libs/controller.hpp"
#include "libs/messages.hpp"

#include "testslib.hpp"

/*****************************************************************************/

void CreateSampleRoute( Controller & _c ) {
	_c.addStation( "first station", 8 );
	_c.addStation( "second station", 3 );
	_c.addStation( "third station", 5 );

	_c.declareNewRoute( 10 );

	_c.addRouteItem( 10, "first station", { 11, 15 }, { 11, 30 } );
	_c.addRouteItem( 10, "second station", { 13, 10 }, { 13, 40 } );
	_c.addRouteItem( 10, "first station", { 14, 32 }, { 14, 50 } );
	_c.addRouteItem( 10, "third station", { 23, 15 }, { 00, 30, TimeHM::Day::NextDay } );

	_c.settleRoute( 10 );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_time_default_constructor ) {
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

DECLARE_OOP_TEST( test_create_correct_route ) {
	Controller c;

	CreateSampleRoute( c );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_route_with_unknown_station ) {
	Controller c;

	c.declareNewRoute( 10 );

	ASSERT_THROWS(
			c.addRouteItem( 10, "Chupakabra station", { 00, 00 }, {00, 01} ),
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

	c.addStation( "Depo", 20 );

	c.addRouteItem( 10, "Depo", { 12, 00 }, { 22, 00} );

	ASSERT_THROWS(
			c.addRouteItem( 10, "Depo", { 23, 00 }, { 01, 00, TimeHM::Day::NextDay } ),
			Messages::StationRepeatsSuccessively
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_route_with_wrong_item_order ) {
	Controller c;

	c.declareNewRoute( 10 );

	c.addStation( "Station 1", 5 );
	c.addStation( "Station 2", 7 );

	c.addRouteItem( 10, "Station 1", { 12, 00 }, { 13, 00} );

	ASSERT_THROWS(
			c.addRouteItem( 10, "Station 2", { 11, 00 }, { 11, 15 } ),
			Messages::WrongRoutePointsOrder
	);
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_create_route_with_wrong_item_time ) {
	Controller c;

	c.declareNewRoute( 10 );

	c.addStation( "Station 1", 5 );

	ASSERT_THROWS(
			c.addRouteItem( 10, "Station 1", { 12, 00 }, { 11, 00} ),
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

	CreateSampleRoute( c );

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
