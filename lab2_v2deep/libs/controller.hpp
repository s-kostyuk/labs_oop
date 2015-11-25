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
#include <unordered_map>

/*****************************************************************************/

typedef int RouteID;
typedef int TrainID;
typedef std::string StationName;

/*****************************************************************************/

class Controller {

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	Controller() = default;

	Controller( const Controller & ) = delete;
	Controller & operator = ( const Controller & ) = delete;

	~Controller() = default;

	/*-----------------------------------------------------------------*/

	void declareNewRoute( const RouteID _id );

	bool addRouteItem(
			const RouteID _id,
			const StationName & _arriveStation,
			const TimeHM & _arriveTime,
			const TimeHM & _departureTime
	);

	void settleRoute( const RouteID _id );

	/*-----------------------------------------------------------------*/

	void addStation(
			const StationName & _name,
			const int _nOfPlatforms
	);

	/*-----------------------------------------------------------------*/

	void addTrain(
			const TrainID _id,
			const int _nOfSeats
	);

	void addTrain(
			const TrainID _id,
			const int _nOfSeats,
			const RouteID _currentRoute
	);

	/*-----------------------------------------------------------------*/

	const Station * findStation( const StationName & _name );

	const Train * findTrain( const TrainID _id );

	const Route * findRoute( const RouteID _id );

	/*-----------------------------------------------------------------*/

	void setTrainRoute(
			const TrainID _train,
			RouteID _newRoute
	);

	void setTrainNOfSeats(
			const TrainID _train,
			const int _newNOfSeats
	);

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	std::vector< std::unique_ptr< Station > > m_allStations;

	std::vector< std::unique_ptr<  Train  > > m_allTrains;

	std::unordered_map< RouteID, std::unique_ptr< Route > > m_allRoutes;

	std::set< RouteID > m_unsettledRoutes;

	/*-----------------------------------------------------------------*/

	void addTrain(
			const TrainID _id,
			const int _nOfSeats,
			const RoutePtr
	);

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif //CONTROLLER_HPP
