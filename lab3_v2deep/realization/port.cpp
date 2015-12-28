//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 27.12.15.
//

/*****************************************************************************/

#include "port.hpp"

#include "messages.hpp"
#include <stdexcept>

/*****************************************************************************/

Port::Port( const std::string & _portName )
		:   m_portName( _portName )
{

	if( ! m_portName.length() )
		throw std::logic_error( Messages::WrongPortName );

}

/*****************************************************************************/
