//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 24.11.15.
//

/*****************************************************************************/

#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

/*****************************************************************************/

#include "station.hpp"
#include "route.hpp"
#include "train.hpp"

#include <vector>
#include <memory>
#include <utility>
#include <string>
#include <set>

/*****************************************************************************/

typedef int RouteID;
typedef std::string StationName;

/*****************************************************************************/

class Controller {

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	// Controller() = default;

	Controller( const Controller & ) = delete;
	Controller & operator = ( const Controller & ) = delete;

	// ~Controller() = default;

	/*-----------------------------------------------------------------*/

	void AddStation(
			const std::string & _name,
			int _nOfPlatforms
	);

	/*-----------------------------------------------------------------*/

	void DeclareRoute(
			const RouteID _id
	);

	bool TryAddRouteItem(
			const RouteID _id,
			const StationName & _arriveStation,
			const TimeHM & _arriveTime,
			const TimeHM & _departureTime
	);

	void SettleRoute(
			const RouteID _id
	);

	/*-----------------------------------------------------------------*/

	void AddTrain(
			const int _id,
			const int _nOfSeats
	);

	void AddTrain(
			const int _id,
			const int _nOfSeats,
			const int _currentRouteID
	);

	/*-----------------------------------------------------------------*/

	void SetTrainRoute(
			const int _trainId,
			const int _newRouteID
	);

	void SetTrainNOfSeats(
			const int _trainId,
			const int _newNOfSeats
	);

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	std::vector< std::unique_ptr< Station > > m_allStations;

	std::vector< std::unique_ptr<  Train  > > m_allTrains;

	std::set< RouteID, std::unique_ptr< Route > > m_allRoutes;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif //CONTROLLER_HPP
