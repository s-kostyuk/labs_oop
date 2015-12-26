//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 26.12.15.
//

/*****************************************************************************/

#include "output_port.hpp"

#include "element.hpp"

/*****************************************************************************/

bool OutputPort::getValue() const {
	return ( m_pTarget ) ? m_pTarget->evaluate() : false;
}

/*****************************************************************************/
