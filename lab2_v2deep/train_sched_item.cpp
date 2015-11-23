//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 23.11.15.
//

#include "train_sched_item.hpp"
#include "messages.hpp"

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
