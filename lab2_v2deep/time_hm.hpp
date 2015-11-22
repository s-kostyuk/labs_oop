//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 22.11.15.
//

#ifndef TIME_HM_HPP
#define TIME_HM_HPP

/*****************************************************************************/

#include <iostream>

/*****************************************************************************/

class TimeHM {

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	TimeHM() = delete;

	TimeHM( short _h, short _m );

	~TimeHM() = default;

	/*-----------------------------------------------------------------*/

	short GetHour()   const { return m_hour;   }
	short GetMinute() const { return m_minute; }

	/*-----------------------------------------------------------------*/

	bool operator == ( const TimeHM & _t ) const;
	bool operator <  ( const TimeHM & _t ) const;

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	short m_hour;
	short m_minute;

	/*-----------------------------------------------------------------*/

	bool IsValid();
};

/*****************************************************************************/

inline bool
TimeHM::IsValid() {
	return m_hour   >= 0 && m_hour   <  24
	       &&
	       m_minute >= 0 && m_minute <= 60;
}

/*****************************************************************************/

inline bool
TimeHM::operator == ( const TimeHM & _t ) const {
	return m_hour   == _t.GetHour()
	       &&
	       m_minute == _t.GetMinute();
}

/*****************************************************************************/

std::ostream & operator << ( std::ostream & _o, const TimeHM & _t );

/*****************************************************************************/

#endif //TIME_HM_HPP
