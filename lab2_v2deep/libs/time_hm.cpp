//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 22.11.15.
//

/*****************************************************************************/

#include "time_hm.hpp"
#include "messages.hpp"

#include <iomanip>
#include <cassert>
#include <stdexcept>

/*****************************************************************************/

TimeHM::TimeHM()
		: m_hour( 0 ), m_minute( 0 ), m_day( Day::Today )
{ }

TimeHM::TimeHM( LongHour _h, LongMinute _m, Day _timeDay )
		: m_hour( _h ), m_minute( _m ), m_day( _timeDay )
{
	if( !IsValid( _h, _m ) )
		throw std::logic_error( Messages::TimeIsInvalid );
}

/*****************************************************************************/

bool TimeHM::operator < ( const TimeHM & _t ) const {
	if( m_day == Day::Today && _t.m_day == Day::NextDay )
		return true;

	else if( m_day == _t.m_day ) {

		if( GetHour() < _t.GetHour())
			return true;

		else if( GetHour() == _t.GetHour())
			return GetMinute() < _t.GetMinute();

	}

	return false;
}

/*****************************************************************************/

std::ostream & operator << ( std::ostream & _o, const TimeHM & _t ) {
	_o << _t.GetHour() << ":" << std::setfill( '0' ) <<  std::setw( 2 );
	_o << _t.GetMinute();

	return _o;
}

/*****************************************************************************/

TimeHM::LongMinute TimeHM::GetMinutesFromMidnight() const {
	return
			static_cast<LongMinute>(m_day) * HOURS_IN_DAY * MINUTES_IN_HOUR
			+
			m_hour * MINUTES_IN_HOUR
			+
			m_minute;
}

/*****************************************************************************/

TimeHM::TimeDiff TimeHM::operator - ( const TimeHM & _t ) const {
	assert( _t < *this );

	return GetMinutesFromMidnight() - _t.GetMinutesFromMidnight();
}

/*****************************************************************************/

TimeHM::TimeDiff TimeHM::GetAbsDiff( const TimeHM & _t1, const TimeHM & _t2 ) {
	return
			( _t1 < _t2 ) ?
			( _t2 - _t1 ) :
			( _t1 - _t2 );
}

/*****************************************************************************/

bool TimeHM::IsOverlaps( const TimeInterval & _t1, const TimeInterval & _t2 ) {
	return  _t1.first < _t2.second
	        &&
			_t2.first < _t1.second;
}

/*****************************************************************************/

TimeHM::TimeInterval TimeHM::GetOverlapInterval( const TimeInterval & _t1, const TimeInterval & _t2 ) {
	if( ! IsOverlaps( _t1, _t2 ) )
		return TimeInterval();

	std::pair< TimeHM, TimeHM > result;

	result.first  = ( _t1.first  < _t2.first  ) ? _t2.first  : _t1.first;
	result.second = ( _t2.second < _t1.second ) ? _t2.second : _t1.second;

	return std::move( result );
}

/*****************************************************************************/
