//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 22.11.15.
//

/*****************************************************************************/

#ifndef MESSAGES_HPP
#define MESSAGES_HPP

/*****************************************************************************/

namespace Messages {
	const char * const TimeIsInvalid = "Requested time is invalid";

	const char * const StationNameIsEmpty = "Station name is empty";
	const char * const StationWithoutPlatfroms = "Station must have at leas one platfrom";
	const char * const NegativePlatfromsOnStation = "Number of platforms can't be negative";

	const char * const DeparturePreceedArrive = "Departure time can't preceed arrive time";
}

/*****************************************************************************/

#endif //MESSAGES_HPP
