//
// Created by srg on 21.09.15.
//

#include "libs/integerset.hpp"

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
