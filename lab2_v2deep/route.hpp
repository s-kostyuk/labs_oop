//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 23.11.15.
//

#ifndef ROUTE_HPP
#define ROUTE_HPP

/*****************************************************************************/

#include "train_sched_item.hpp"

#include <vector>
#include <memory>

/*****************************************************************************/

// TODO: Требует переработки

class Route {

	typedef std::vector< std::unique_ptr< TrainSchedItem > > RouteInitVector;

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	Route() = delete;

	Route( const int _id, RouteInitVector & _v );

	Route( const Route & ) = delete;
	Route & operator = ( const Route & ) = delete;

	~ Route() = default;

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	typedef std::unique_ptr< TrainSchedItem > UniqueItem;

	/*-----------------------------------------------------------------*/

	const int m_id;
	std::vector< UniqueItem > m_items;

	/*-----------------------------------------------------------------*/

	void CheckItemVector( RouteInitVector & _v );

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif //ROUTE_HPP
