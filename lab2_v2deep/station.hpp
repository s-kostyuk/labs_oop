//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 22.11.15.
//

/*****************************************************************************/

#ifndef STATION_HPP
#define STATION_HPP

/*****************************************************************************/

#include <string>

/*****************************************************************************/

class Station {

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	Station( const std::string & _name, const int _nOfPlatforms );

	Station( const Station & ) = delete;
	Station & operator = ( const Station & ) = delete;

	~Station() = default;

	/*-----------------------------------------------------------------*/

	const std::string & GetName() const { return m_name; };
	int GetNOfPlatfroms() const { return m_nOfPlatforms; };

	/*-----------------------------------------------------------------*/

	bool operator == ( const Station & _s ) const;
	bool operator == ( const char * const _name ) const;

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	const std::string m_name;
	int m_nOfPlatforms;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline bool
Station::operator == ( const Station & _s ) const {
	return _s.m_name == m_name;
}

inline bool
Station::operator == ( const char * const _name ) const {
	return _name == m_name;
}

/*****************************************************************************/

#endif //STATION_HPP
