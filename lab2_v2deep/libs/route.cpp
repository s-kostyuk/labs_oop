//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 23.11.15.
//

/*****************************************************************************/

#include "route.hpp"
#include "messages.hpp"

#include <algorithm>

/*****************************************************************************/

Route::Route( const int _id )
		: m_id( _id )
{
	if( _id < 0 )
		throw std::logic_error( Messages::NegativeID );
}

/*****************************************************************************/

void Route::AddItem( UniqueRouteItem _it ) {
	CheckItem( _it );

	m_usedStations.insert( & _it->GetArriveStation() );

	m_items.push_back( std::move( _it ) );
}

/*****************************************************************************/

void Route::CheckItem( UniqueRouteItem & _i ) {
	auto pLastItem = m_items.rbegin();

	if( pLastItem == m_items.rend() )
		return;

	if( (*pLastItem)->GetArriveStation() == _i->GetArriveStation() )
		throw std::logic_error( Messages::StationRepeatsSuccessively );

	if( *_i < **pLastItem )
		throw std::logic_error( Messages::WrongRoutePointsOrder );

	if( TrainSchedItem::IsOverlaps( *_i, **pLastItem ) )
		throw std::logic_error( Messages::RouteItemWithWrongTime );

}

/*****************************************************************************/

TimeHM::TimeDiff Route::GetDuration() {
	return TimeHM::GetDiff(
			m_items.rbegin()->get()->GetArriveTime(), m_items.begin()->get()->GetArriveTime()
	);
}

/*****************************************************************************/

bool Route::HasStation( const Station & _s ) {
	auto it = m_usedStations.find( & _s );

	return it != m_usedStations.end();
}

/*****************************************************************************/
