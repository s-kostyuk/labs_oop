/*
 * computation_time.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: betatester
 */

#include <time.h>

void FixComputationTime(double * _diffBetweenChecks = nullptr) {
	static clock_t lastTime = clock();

	if ( _diffBetweenChecks ) {
		clock_t timeNow = clock();
		double diffInSeconds = ( ( double ) ( timeNow - lastTime ) / ( double ) CLOCKS_PER_SEC );
		* _diffBetweenChecks = diffInSeconds;
	}

	lastTime = clock();
}
