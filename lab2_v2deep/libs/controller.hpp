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

	void addRouteItem(
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
	const Route * findRoute( const RouteID _id );
	const Train * findTrain( const TrainID _id );

	/*-----------------------------------------------------------------*/

	bool IsRouteExists( const RouteID _id ) const;
	bool IsRouteSettled( const RouteID _id ) const;

	/*-----------------------------------------------------------------*/

	void setTrainRoute(
			const TrainID _train,
			RouteID _newRoute
	);

	void unsetTrainRoute( const TrainID _train );

	void setTrainNOfSeats(
			const TrainID _train,
			const int _newNOfSeats
	);

	/*-----------------------------------------------------------------*/

	void printBusiestStations( std::ostream & _o, const long _nOfStations = 5 );
	void printSlowestRoutes( std::ostream & _o, const long _nOfRoutes = 5 );
	void printMultipleConnectedStations( std::ostream & _o );
	void printNonConnectedStations( std::ostream & _o );
	void printOverloadedStations( std::ostream & _o );

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	typedef std::unordered_map< RouteID, std::unique_ptr< Route > > RoutesContainer;

	typedef std::vector< std::unique_ptr< Station > > StationsContainer;

	StationsContainer m_allStations;

	std::vector< std::unique_ptr<  Train  > > m_allTrains;

	RoutesContainer m_allRoutes;

	std::set< RouteID > m_unsettledRoutes;

	/*-----------------------------------------------------------------*/

	void CheckRouteReadyForSettle( const RouteID _id ) const;
	void CheckRouteReady( const RouteID _id ) const;

	/*-----------------------------------------------------------------*/

	Route * findRouteMutable( const RouteID _id );
	Train * findTrainMutable( const TrainID _id );

	Train & resolveTrainMustable( const TrainID _id );

	/*-----------------------------------------------------------------*/

	const Controller::RoutesContainer::const_iterator findTwoStationsInRoutes(
			const StationsContainer::iterator & _1st, const StationsContainer::iterator & _2nd,
			const std::unordered_map< int, std::unique_ptr< Route>>::const_iterator & _startRoute ) const;

	/*-----------------------------------------------------------------*/

	void addTrain(
			const TrainID _id,
			const int _nOfSeats,
			const ConstRoutePtr
	);

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline const Route * Controller::findRoute( const RouteID _id ) {
	return findRouteMutable( _id );
}

/*****************************************************************************/

inline const Train * Controller::findTrain( const TrainID _id ) {
	return findTrainMutable( _id );
}

/*****************************************************************************/

inline bool Controller::IsRouteExists( const RouteID _id ) const {
	return m_allRoutes.find( _id ) != m_allRoutes.end();
}

/*****************************************************************************/

inline bool Controller::IsRouteSettled( const RouteID _id ) const {
	return m_unsettledRoutes.find( _id ) == m_unsettledRoutes.end();
}

/*****************************************************************************/

#endif //CONTROLLER_HPP
