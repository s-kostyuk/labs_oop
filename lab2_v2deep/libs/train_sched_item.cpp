//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 23.11.15.
//

/*****************************************************************************/

#include "train_sched_item.hpp"
#include "messages.hpp"

#include <stdexcept>

/*****************************************************************************/

TrainSchedItem::TrainSchedItem( const Station & _arriveStation, const TimeHM & _arriveTime,
                                const TimeHM & _departureTime )
		: m_arriveStation( _arriveStation )
		, m_arriveTime    ( _arriveTime )
		, m_departureTime ( _departureTime )
{
	if( GetDepartTime() < GetArriveTime() )
		throw std::logic_error( Messages::DeparturePreceedArrive );
}

/*****************************************************************************/

bool TrainSchedItem::operator == ( const TrainSchedItem & _item ) const {
	return
		m_arriveTime == _item.m_arriveTime
		&&
        m_departureTime == _item.m_departureTime
		&&
		m_arriveStation == _item.m_arriveStation;
}

/*****************************************************************************/

bool TrainSchedItem::operator < ( const TrainSchedItem & _item ) const {
	if( m_arriveTime < _item.m_arriveTime )
		return true;

	else if( m_arriveTime == _item.m_arriveTime ) {

		if( m_departureTime < _item.m_arriveTime )
			return true;

		else if( m_departureTime == _item.m_departureTime )
			return m_arriveStation < _item.m_arriveStation;

	}

	return false;
}

/*****************************************************************************/

bool TrainSchedItem::IsOverlaps( const TrainSchedItem & _item1, const TrainSchedItem & _item2 ) {
	return TimeHM::IsOverlaps(
			{ _item1.GetArriveTime(), _item1.GetDepartTime() },
			{ _item2.GetArriveTime(), _item2.GetDepartTime() }
	);
}

/*****************************************************************************/
