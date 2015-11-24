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

	const char * const NegativeID = "ID of an object can't be negative";

	const char * const NegativeNumberOfSeats = "Number of seats can't be negative";

	const char * const WrongRoutePointsOrder = "List of route points must be sorted by arrive time";
	const char * const RouteItemWithWrongTime = "Train can't be simultaneously on different stations";
}

/*****************************************************************************/

#endif //MESSAGES_HPP