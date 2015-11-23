//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 23.11.15.
//

#include "train_sched_item.hpp"
#include "messages.hpp"
#include "station.hpp"

#include <stdexcept>

TrainSchedItem::TrainSchedItem( const Station & _arriveStation, const TimeHM & _arriveTime,
                                const TimeHM  & _departureTime )
		: m_arriveStation( _arriveStation )
		, m_arriveTime    ( _arriveTime )
		, m_departureTime ( _departureTime )
{
	if( GetDepartureTime() < GetArriveTime() )
		throw std::logic_error( Messages::DeparturePreceedArrive );
}

// TODO: Рассмотреть равенство по времени VS равенство по всем полям
bool TrainSchedItem::operator == ( const TrainSchedItem & _item ) const {
	return
		m_arriveTime == _item.m_arriveTime
		&&
        m_departureTime == _item.m_departureTime
		&&
	    m_arriveStation == _item.m_arriveStation;
}

// TODO: Рассмотреть сравнение по времени VS сравнение по всем полям
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