//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 24.11.15.
//

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include <algorithm>

/*****************************************************************************/

const Station * Controller::findStation( const StationName & _name ) {
	auto it = std::find_if
	(
			m_allStations.begin(),
			m_allStations.end(),
	        [ & ]( std::unique_ptr< Station > & _ptr ) {
		        return _ptr->GetName() == _name;
	        }
	);

	// TODO: Выглядит совсем не красиво
	return ( it == m_allStations.end() ) ?
	       nullptr : it->get();
}

/*****************************************************************************/

void Controller::addStation( const StationName & _name, const int _nOfPlatforms ) {
	if( findStation( _name ) )
		throw std::logic_error( Messages::DuplicateStationNames );

	m_allStations.push_back(
			std::make_unique< Station >(
					_name, _nOfPlatforms
			)
	);
}

/*****************************************************************************/

Route * Controller::findRouteMutable( const RouteID _id ) {
	auto it = m_allRoutes.find( _id );

	// TODO: Выглядит совсем не красиво
	return ( it == m_allRoutes.end() ) ?
	       nullptr : it->second.get();
}

/*****************************************************************************/

void Controller::declareNewRoute( const RouteID _id ) {
	if( IsRouteExists( _id ) ) {
		if( ! IsRouteSettled( _id ) )
			throw std::logic_error( Messages::UnfinishedRouteExist );

		else
			throw std::logic_error( Messages::DuplicateRouteID );
	}

	m_allRoutes.insert(
			std::make_pair(
					_id, std::make_unique< Route >( _id )
			)
	);

	m_unsettledRoutes.insert( _id );
}

/*****************************************************************************/

void Controller::addRouteItem(
		const RouteID _id,
		const StationName & _arriveStation,
		const TimeHM & _arriveTime,
		const TimeHM & _departureTime
)
{
	CheckRouteReadyForSettle( _id );

	Route * pRoute = findRouteMutable( _id );

	const Station * const pStation = findStation( _arriveStation );

	if( ! pStation )
		throw std::logic_error( Messages::UnknownStation );

	pRoute->AddItem(
			std::make_unique< TrainSchedItem > (
					*pStation,
			        _arriveTime,
			        _departureTime
			)
	);
}

/*****************************************************************************/

void Controller::CheckRouteReadyForSettle( const RouteID _id ) {
	if( IsRouteSettled( _id ) ) {
		if( IsRouteExists( _id ) )
			throw std::logic_error( Messages::RouteAlreadySettled );

		else
			throw std::logic_error( Messages::RouteDoesntExist );
	}
}

/*****************************************************************************/

void Controller::settleRoute( const RouteID _id ) {
	CheckRouteReadyForSettle( _id );

	if( findRoute( _id )->empty() )
		throw std::logic_error( Messages::RouteIsEmpty );

	m_unsettledRoutes.erase( _id );
}

/*****************************************************************************/

void Controller::CheckRouteReady( const RouteID _id ) {
	if( ! IsRouteSettled( _id ) )
		throw std::logic_error( Messages::UsageOfUnfinishedRoute );

	if( ! IsRouteExists( _id ) )
		throw std::logic_error( Messages::UsageOfUnknownRoute );
}

/*****************************************************************************/

Train * Controller::findTrainMutable( const TrainID _id ) {
	auto it = std::find_if
			(
					m_allTrains.begin(),
					m_allTrains.end(),
					[ & ]( std::unique_ptr< Train > & _ptr ) {
						return _ptr->GetID() == _id;
					}
			);

	// TODO: Выглядит совсем не красиво. Кроме того, дублируется в findStation
	return ( it == m_allTrains.end() ) ?
	       nullptr : it->get();
}

/*****************************************************************************/

void Controller::addTrain( const TrainID _id, const int _nOfSeats, const ConstRoutePtr _p ) {
	if( findTrain( _id ) )
		throw std::logic_error( Messages::DuplicateTrainIDs );

	m_allTrains.push_back(
			std::make_unique< Train >( _id, _nOfSeats, _p )
	);
}

/*****************************************************************************/

void Controller::addTrain( const TrainID _id, const int _nOfSeats ) {
	addTrain( _id, _nOfSeats, nullptr );
}

/*****************************************************************************/

void Controller::addTrain( const TrainID _id, const int _nOfSeats, const RouteID _currentRoute ) {
	CheckRouteReady( _currentRoute );

	addTrain( _id, _nOfSeats, findRouteMutable( _currentRoute ) );
}

/*****************************************************************************/

void Controller::setTrainRoute( const TrainID _train, RouteID _newRoute ) {
	Train * const pTrain = findTrainMutable( _train );

	CheckRouteReady( _newRoute );

	pTrain->SetCurrentRoute( findRoute( _newRoute ) );
}

/*****************************************************************************/

void Controller::setTrainNOfSeats( const TrainID _train, const int _newNOfSeats ) {
	Train * const pTrain = findTrainMutable( _train );

	pTrain->SetNOfSeats( _newNOfSeats );
}

/*****************************************************************************/
