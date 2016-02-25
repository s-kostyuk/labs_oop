//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 26.12.15.
//

/*****************************************************************************/

#include "input_port_element.hpp"

#include "input_port.hpp"

/*****************************************************************************/

InputPortElement::InputPortElement( const InputPort & _input )
		:   m_input( _input )
{ }

/*****************************************************************************/

bool InputPortElement::evaluate() const {
	return m_input.getValue();
}

/*****************************************************************************/
