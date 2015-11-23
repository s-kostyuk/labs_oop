//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 23.11.15.
//

/*****************************************************************************/

#include "route.hpp"
#include "messages.hpp"

#include <algorithm>

/*****************************************************************************/

// TODO: Выбрасывать исключение или проверять на правильность и возвращать результат?
void Route::CheckItemVector( RouteInitVector & _v ) {
	for( auto it = _v.begin() + 1; it != _v.end(); ++ it ) {
		if( **(it - 1) < **it )
			throw std::logic_error( Messages::WrongRoutePointsOrder );

		if( TrainSchedItem::IsOverlaps( **(it - 1), **it ) )
			throw std::logic_error( Messages::RouteItemWithWrongTime );

	}
}

/*****************************************************************************/

Route::Route( const int _id, Route::RouteInitVector & _v )
	: m_id( _id )
{
	if( _id < 0 )
		throw std::logic_error( Messages::NegativeID );

	CheckItemVector( _v );

	m_items = std::move( _v );
}

/*****************************************************************************/