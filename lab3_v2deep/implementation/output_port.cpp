//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 26.12.15.
//

/*****************************************************************************/

#include "output_port.hpp"

#include "element.hpp"

/*****************************************************************************/

OutputPort::OutputPort( const std::string & _portName )
		:   Port( _portName )
		,   m_pTarget( nullptr )
{ }

/*****************************************************************************/

bool OutputPort::getValue() const {
	return ( m_pTarget ) ? m_pTarget->evaluate() : false;
}

/*****************************************************************************/
