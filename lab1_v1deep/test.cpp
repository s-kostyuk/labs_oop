//
// Created by srg on 21.09.15.
//

#include "libs/integerset.hpp"

#include "testslib.hpp"
#include <cstring>
#include <vector>
#include <algorithm>
#include <sstream>

std::string getIntegerSetAsString ( IntegerSet const & _s )
{
	std::stringstream ss;
	ss << _s;
	return ss.str();
}

DECLARE_OOP_TEST( integerset_test_default_constructor ) {
	IntegerSet testSet;
	assert( testSet.begin() == testSet.end() );
	assert( testSet.getSize() == 0 );
}

DECLARE_OOP_TEST( integerset_test_array_constructor ) {
	const int testArray[] = { 100, 245, 999 };
	const int testArraySize = sizeof( testArray ) / sizeof( *testArray );

	IntegerSet testSet( testArray, testArraySize );

	assert( testSet.getSize() == testArraySize );
	assert( testSet.hasKey( 100 ) && testSet.hasKey( 245 ) && testSet.hasKey( 999 ) );
}

DECLARE_OOP_TEST( integerset_test_array_constructor_error ) {
	const int testArray[] = { 10, 15, 25 };
	const int testArraySize = sizeof( testArray ) / sizeof( *testArray );

	try
	{
		IntegerSet testSet( testArray, -5 );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Invalid parameters" ) );
	}

	try
	{
		IntegerSet testSet( nullptr, testArraySize );
		assert( ! "Exception must have been thrown" );
	}
	catch ( std::exception & e )
	{
		assert( ! strcmp( e.what(), "Invalid parameters" ) );
	}

}

DECLARE_OOP_TEST( integerset_test_initializer_list_constructor ) {
	IntegerSet testSet{ 10, 15, 25 };

	assert( testSet.getSize() == 3 );
	assert( testSet.hasKey( 10 ) && testSet.hasKey( 15 ) && testSet.hasKey( 25 ) );
}

DECLARE_OOP_TEST( integerset_test_empty_output ) {
	IntegerSet testSet;

	assert( getIntegerSetAsString( testSet ) == "{  }" );
}

DECLARE_OOP_TEST( integerset_test_output ) {
	IntegerSet testSet{ 14, 17, 23, 24, 38, 52, 56, 57, 74 };

	assert( getIntegerSetAsString( testSet ) == "{ 14, 17, 23, 24, 38, 52, 56, 57, 74 }" );
}

DECLARE_OOP_TEST( integerset_test_clear ) {
	IntegerSet testSet{ 1523, 5252, 1025 };

	testSet.clear();

	assert( testSet.getSize() == 0 );

	assert( getIntegerSetAsString( testSet ) == "{  }" );
}

DECLARE_OOP_TEST( integerset_test_equal ) {
	const IntegerSet testSet1{ 10, 15, 25, 315, 909, 512 };
	const IntegerSet testSet2{ 10, 15, 25, 315, 909, 512 };
	const IntegerSet testSet3{ 512, 10, 315, 25, 909, 15 };

	assert(    testSet1 == testSet1
	        && testSet1 == testSet2
			&& testSet2 == testSet1
			&& testSet2 == testSet3
	);

	assert( !( testSet1 != testSet3 ) );
}

DECLARE_OOP_TEST( integerset_test_iterator ) {
	std::vector<int> testV{ 512, 10, 315, 25, 909, 15 };

	IntegerSet testSet( testV.data(), testV.size() );

	IntegerSet::Iterator setIt = testSet.begin();

	std::sort( testV.begin(), testV.end() );

	for( int x : testV ) {
		assert( x == *setIt );
		++ setIt;
	}
}

DECLARE_OOP_TEST( integerset_test_add_key ) {
	IntegerSet testSet{ 10, 15, 25, 315, 909, 512 };

	testSet += 2015;
	testSet += -5032;
	testSet += 0;

	assert( getIntegerSetAsString( testSet ) ==
	        "{ -5032, 0, 10, 15, 25, 315, 512, 909, 2015 }"
	);

	testSet.clear();

	testSet += 2015;

	assert( testSet.getSize() == 1 && *testSet.begin() == 2015 );
}

DECLARE_OOP_TEST( integerset_test_remove_key ) {
	IntegerSet testSet{ 10, 15, 25, 315, 909, 512 };

	testSet -= 909;
	testSet -= 15;
	testSet -= 10;

	assert( getIntegerSetAsString( testSet ) == "{ 25, 315, 512 }" );

	testSet -= -5000;

	assert( getIntegerSetAsString( testSet ) == "{ 25, 315, 512 }" );
}

DECLARE_OOP_TEST( integerset_test_remove_last_key ) {
	IntegerSet testSet{ 5 };

	testSet -= 5;

	assert( testSet.getSize() == 0 );
}

DECLARE_OOP_TEST( integerset_test_remove_all_keys ) {
	const int testArray[] = { 14, 17, 23, 24, 38, 52, 56, 57, 74, 75, 85, 91, 98, 100, 116, 128, 131, 186, 194,
	                          225, 232, 240, 266, 278, 290, 302, 309, 322, 328, 363, 366, 371, 386, 404, 407,
	                          447, 462, 463, 477, 479, 485, 487, 489 };
	const int testArraySize = sizeof( testArray ) / sizeof( *testArray );

	IntegerSet testSet( testArray, testArraySize );

	for( int i = 0; i < testArraySize; i++ ) {
		testSet -= testArray[ i ];
	}

	assert( testSet.getSize() == 0 );
	assert( getIntegerSetAsString( testSet ) == "{  }" );
}

DECLARE_OOP_TEST( integerset_test_union ) {
	const IntegerSet testSet1{ 14, 17, 23, 24, 38, 52, 56, 57, 74, 75, 85, 91, 98 };
	const IntegerSet testSet2{ 56, 57, 74, 75, 85, 91, 98, 100, 116, 128, 131 };

	const IntegerSet unionSet = testSet1 | testSet2;

	assert( getIntegerSetAsString( unionSet ) ==
	        "{ 14, 17, 23, 24, 38, 52, 56, 57, 74, 75, 85, 91, 98, 100, 116, 128, 131 }"
	);
}

DECLARE_OOP_TEST( integerset_test_intersection ) {
	const IntegerSet testSet1{ 14, 17, 23, 24, 38, 52, 56, 57, 74, 75, 85, 91, 98, 100, 116, 128, 131, 186, 194,
	                            225, 232, 240, 266, 278, 290, 302, 309, 322, 328, 363, 366, 371, 386, 404, 407,
	                            447, 462, 463, 477, 479, 485, 487, 489 };

	const IntegerSet testSet2{ 14, 17, 23, 24, 38, 52, 56, 57, 74, 75, 85, 91, 98, 100, 116, 128, 131, 186, 194,
	                            447, 462, 463, 477, 479, 485, 487, 489 };

	const IntegerSet testSet3 = testSet1 & testSet2;

	assert( testSet2 == testSet3 );
}

DECLARE_OOP_TEST( integerset_test_difference ) {
	IntegerSet testSet1{ 14, 17, 23, 24, 38, 52, 56, 57, 74, 75, 85, 91, 98, 100, 116, 128, 131, 186, 194,
	                           225, 232, 240, 266, 278, 290, 302, 309, 322, 328, 363, 366, 371, 386, 404, 407,
	                           447, 462, 463, 477, 479, 485, 487, 489 };

	const IntegerSet testSet2{ 14, 17, 23, 24, 38, 52, 56, 57, 74, 75, 85, 91, 98, 100, 116, 128, 131, 186, 194,
	                           447, 462, 463, 477, 479, 485, 487, 489 };

	const IntegerSet diff = testSet1 - testSet2;

	assert( getIntegerSetAsString( diff ) ==
	        "{ 225, 232, 240, 266, 278, 290, 302, 309, 322, 328, 363, 366, 371, 386, 404, 407 }"
	);
}
