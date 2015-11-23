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

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	class Iterator;

	Route() = delete;

	Route( const int _id );

	Route( const Route & ) = delete;
	Route & operator = ( const Route & ) = delete;

	~ Route() = default;

	/*-----------------------------------------------------------------*/

	Iterator begin();
	Iterator end();

	/*-----------------------------------------------------------------*/

	typedef std::unique_ptr< TrainSchedItem > UniqueRouteItem;

	void AddItem( UniqueRouteItem _it );

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	const int m_id;
	std::vector< UniqueRouteItem > m_items;

	/*-----------------------------------------------------------------*/

	void CheckItem( UniqueRouteItem & _i );

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif //ROUTE_HPP
