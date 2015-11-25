//
// Created by betatester on 25.11.15.
//

/*****************************************************************************/

#include "libs/controller.hpp"
#include "libs/messages.hpp"

#include "testslib.hpp"

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
			Messages::StationWithoutPlatfroms
	);
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
