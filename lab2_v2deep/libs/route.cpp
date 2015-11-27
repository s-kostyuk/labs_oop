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

	const Station & arriveStation = _it->GetArriveStation();

	m_items.push_back( std::move( _it ) );

	m_itemsByStation.insert( std::make_pair( & arriveStation, m_items.rbegin()->get() ) );
}

/*****************************************************************************/

void Route::CheckItem( UniqueRouteItem & _i ) const {
	auto pLastItem = m_items.rbegin();

	if( pLastItem == m_items.rend() )
		return;

	if( (*pLastItem)->GetArriveStation() == _i->GetArriveStation() )
		throw std::logic_error( Messages::StationRepeatsSuccessively );

	if( *_i < **pLastItem )
		throw std::logic_error( Messages::WrongRoutePointsOrder );

	if( TrainSchedItem::IsOverlaps( *_i, **pLastItem ) )
		throw std::logic_error( Messages::RouteItemTimeIntersect );

}

/*****************************************************************************/

TimeHM::TimeDiff Route::GetDuration() const {
	if( m_items.empty() )
		return TimeHM::TimeDiff( 0 );

	return TimeHM::GetDiff(
			m_items.rbegin()->get()->GetArriveTime(), m_items.begin()->get()->GetDepartTime()
	);
}

/*****************************************************************************/

bool Route::HasStation( const Station & _s ) const {
	auto it = m_itemsByStation.find( & _s );

	return it != m_itemsByStation.end();
}

/*****************************************************************************/

const TrainSchedItem * Route::TryGetNextItemByStation( const Station & _s, bool _fromScratch ) const {
	typedef std::multimap< const Station *, const TrainSchedItem * >::const_iterator ItemsByStationIter;
	static std::pair< ItemsByStationIter, ItemsByStationIter > itPair;

	static const Station * pPrevStation = nullptr;
	const Station * const pCurrStation = & _s;

	static ItemsByStationIter it;

	if( pPrevStation != pCurrStation || _fromScratch ) {
		itPair = m_itemsByStation.equal_range( pCurrStation );
		it = itPair.first;
	}
	else
		if( it != itPair.second )
			++it;

	pPrevStation = pCurrStation;

	return ( it == m_itemsByStation.end() ) ?
	       nullptr : it->second;
}

/*****************************************************************************/

std::pair< const Station *, const Station * > Route::GetOutermostStations() const {
	if( m_items.empty() )
		return std::pair< const Station *, const Station * >( nullptr, nullptr );

	return std::pair< const Station *, const Station * >(
			&( m_items.begin ()->get()->GetArriveStation() ),
			&( m_items.rbegin()->get()->GetArriveStation() )
	);
}

/*****************************************************************************/
