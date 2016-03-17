//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 22.11.15.
//

#ifndef TIME_HM_HPP
#define TIME_HM_HPP

/*****************************************************************************/

#include <iostream>

/*****************************************************************************/

// TODO: Кандидат на замену функциями стандартной библиотеки

class TimeHM {

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	typedef int   TimeDiff;
	typedef char  Hour;
	typedef char  Minute;
	typedef short LongMinute;
	typedef short LongHour;
	typedef std::pair< TimeHM, TimeHM > TimeInterval;

	/*-----------------------------------------------------------------*/

	enum class Day {
		Today, NextDay
	};

	/*-----------------------------------------------------------------*/

	TimeHM();

	TimeHM( LongHour _h, LongMinute _m, Day _timeDay = Day::Today );

	~TimeHM() = default;

	/*-----------------------------------------------------------------*/

	LongHour   GetHour()   const { return m_hour;   }
	LongMinute GetMinute() const { return m_minute; }
	Day        GetDay()    const { return m_day;    }

	/*-----------------------------------------------------------------*/

	bool operator == ( const TimeHM & _t ) const;
	bool operator <  ( const TimeHM & _t ) const;

	/*-----------------------------------------------------------------*/

	LongMinute GetMinutesFromMidnight() const;
	static TimeDiff GetAbsDiff( const TimeHM & _t1, const TimeHM & _t2 );

	/*-----------------------------------------------------------------*/

	static bool IsOverlaps( const TimeInterval & _t1, const TimeInterval & _t2 );

	TimeInterval GetOverlapInterval( const TimeInterval & _t1, const TimeInterval & _t2 );

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	static const unsigned char MINUTES_IN_HOUR = 60;
	static const unsigned char HOURS_IN_DAY = 24;

	/*-----------------------------------------------------------------*/

	Hour   m_hour;
	Minute m_minute;
	Day    m_day;

	/*-----------------------------------------------------------------*/

	bool IsValid() const;
	bool IsValid( LongHour _h, LongMinute _m ) const;

	/*-----------------------------------------------------------------*/

	TimeDiff operator - ( const TimeHM & _t ) const;

	/*-----------------------------------------------------------------*/
};

/*****************************************************************************/

inline bool
TimeHM::IsValid( LongHour _h, LongMinute _m ) const {
	return _h >= 0 && _h < HOURS_IN_DAY
	       &&
	       _m >= 0 && _m < MINUTES_IN_HOUR;
}

/*****************************************************************************/

inline bool
TimeHM::IsValid() const {
	return IsValid( m_hour, m_minute );
}

/*****************************************************************************/

inline bool
TimeHM::operator == ( const TimeHM & _t ) const {
	return  m_day    == _t.GetDay()
	        &&
			m_hour   == _t.GetHour()
	        &&
			m_minute == _t.GetMinute();
}

/*****************************************************************************/

std::ostream & operator << ( std::ostream & _o, const TimeHM & _t );

/*****************************************************************************/

#endif //TIME_HM_HPP
