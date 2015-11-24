//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 24.11.15.
//

/*****************************************************************************/

#include "controller.hpp"
#include "messages.hpp"

#include <algorithm>
#include <stdexcept>

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

	return it->get();
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

void Controller::declareNewRoute( const RouteID _id ) {
	if( m_allRoutes.find( _id ) != m_allRoutes.end() ) {
		if( m_unsettledRoutes.find( _id ) != m_unsettledRoutes.end() )
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

void Controller::settleRoute( const RouteID _id ) {
	if( m_unsettledRoutes.find( _id ) == m_unsettledRoutes.end() ) {
		if( m_allRoutes.find( _id ) != m_allRoutes.end() )
			throw std::logic_error( Messages::RouteAlreadySettled );

		else
			throw std::logic_error( Messages::RouteDoesntExist );
	}

}

/*****************************************************************************/

const Train * Controller::findTrain( const TrainID _id ) {
	auto it = std::find_if
			(
					m_allTrains.begin(),
					m_allTrains.end(),
					[ & ]( std::unique_ptr< Train > & _ptr ) {
						return _ptr->GetID() == _id;
					}
			);

	return it->get();
}

/*****************************************************************************/
/*
void Controller::addTrain( const TrainID _id, const int _nOfSeats, const RouteID _currentRoute ) {
	if( findTrain( _id ) )
		throw std::logic_error( Messages::DuplicateStationNames );

	m_allStations.push_back(
			std::make_unique< Train >(
					_id, _nOfSeats, _currentRoute
			)
	);
}
*/
/*****************************************************************************/
/*
void Controller::addTrain( const TrainID _id, const int _nOfSeats ) {
	addTrain( _id, _nOfSeats, nullptr );
}
*/
/*****************************************************************************/

