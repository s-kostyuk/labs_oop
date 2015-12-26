//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 26.12.15.
//

/*****************************************************************************/

#include "input_port_element.hpp"

#include "input_port.hpp"

/*****************************************************************************/

bool InputPortElement::evaluate() const {
	return m_input.getValue();
}

/*****************************************************************************/
