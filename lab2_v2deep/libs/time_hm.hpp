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
	typedef short Hour;
	typedef short Minute;
	typedef int   LongMinute;

	/*-----------------------------------------------------------------*/

	enum class Day {
		Today, NextDay
	};

	/*-----------------------------------------------------------------*/

	TimeHM();

	TimeHM( Hour _h, Minute _m, Day _timeDay = Day::Today );

	~TimeHM() = default;

	/*-----------------------------------------------------------------*/

	Hour   GetHour()   const { return m_hour;   }
	Minute GetMinute() const { return m_minute; }
	Day    GetDay()    const { return m_day;    }

	/*-----------------------------------------------------------------*/

	bool operator == ( const TimeHM & _t ) const;
	bool operator <  ( const TimeHM & _t ) const;

	/*-----------------------------------------------------------------*/

	LongMinute GetMinutesFromMidnight() const;
	static TimeDiff GetDiff( const TimeHM & _t1, const TimeHM & _t2 );

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	static const unsigned char MINUTES_IN_HOUR = 60;
	static const unsigned char HOURS_IN_DAY = 24;

	/*-----------------------------------------------------------------*/

	short m_hour;
	short m_minute;
	Day   m_day;

	/*-----------------------------------------------------------------*/

	bool IsValid();

	/*-----------------------------------------------------------------*/

	TimeDiff operator - ( const TimeHM & _t ) const;

	/*-----------------------------------------------------------------*/
};

/*****************************************************************************/

inline bool
TimeHM::IsValid() {
	return m_hour   >= 0 && m_hour   < HOURS_IN_DAY
	       &&
	       m_minute >= 0 && m_minute < MINUTES_IN_HOUR;
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
