//
// Created by srg on 21.09.15.
//

#include "libs/integerset.hpp"

#include "testslib.hpp"
#include <cstring>
#include <vector>
#include <algorithm>

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

DECLARE_OOP_TEST( integerset_test_clear ) {
	IntegerSet testSet{ 1523, 5252, 1025 };

	testSet.clear();

	assert( testSet.getSize() == 0 );

	const IntegerSet emptySet;
	assert( testSet == emptySet );
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
	IntegerSet testSet1{ 10, 15, 25, 315, 909, 512 };

	testSet1 += 2015;
	testSet1 += -5032;
	testSet1 += 0;

	const IntegerSet testSet2{ 10, 15, 25, 315, 909, 512, 2015, -5032, 0 };

	assert( testSet1 == testSet2 );

	testSet1.clear();

	testSet1 += 2015;

	assert( testSet1.getSize() == 1 && *testSet1.begin() == 2015 );
}

DECLARE_OOP_TEST( integerset_test_remove_key ) {
	IntegerSet testSet1{ 10, 15, 25, 315, 909, 512 };

	testSet1 -= 909;
	testSet1 -= 15;
	testSet1 -= 10;

	const IntegerSet testSet2{ 25, 315, 512 };

	assert( testSet1 == testSet2 );

	testSet1 -= -5000;

	assert( testSet1 == testSet2 );
}



/*
#include <cstdlib>
#include <ctime>

int main() {
	srand( time( NULL ));

    IntegerSet testSet1({ 14, 17, 23, 24, 38, 52, 56, 57, 74, 75, 85, 91, 98, 100, 116, 128, 131, 186, 194, 225, 232,
                         240, 266, 278, 290, 302, 309, 322, 328, 363, 366, 371, 386, 404, 407, 447, 462, 463, 477,
                         479, 485, 487, 489 });

	IntegerSet testSet2({ 14, 17, 23, 24, 38, 52, 56, 57, 74, 75, 85, 91, 98, 100, 116, 128, 131, 186, 194, 225, 232,
	                     479, 485, 487, 489 });

	IntegerSet testSet3 = testSet1 & testSet2;

	assert( testSet2 == testSet3 );

    return 0;
}
*/