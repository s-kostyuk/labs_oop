//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 22.11.15.
//

#include "station.hpp"
#include "messages.hpp"

#include <stdexcept>

/*****************************************************************************/

Station::Station( const std::string & _name, const int _nOfPlatforms )
	: m_name( _name ), m_nOfPlatforms( _nOfPlatforms )
{
	if( m_name.empty() )
		throw std::logic_error( Messages::StationNameIsEmpty );

	if( _nOfPlatforms < 0  )
		throw std::logic_error( Messages::NegativePlatfromsOnStation );

	if( _nOfPlatforms == 0 )
		throw std::logic_error( Messages::StationWithoutPlatfroms );
}

/*****************************************************************************/

bool Station::operator == ( const Station & _s ) const {
	return m_name == _s.m_name;
}

bool Station::operator < ( const Station & _s ) const {
	return m_name < _s.m_name;
}

/*****************************************************************************/