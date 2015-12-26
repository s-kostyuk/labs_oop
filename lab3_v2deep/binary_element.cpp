//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 26.12.15.
//

/*****************************************************************************/

#include "binary_element.hpp"

#include <cassert>

/*****************************************************************************/

bool BinaryElement::evaluate() const {
	switch( m_type ) {

		case Type::AND:
			return m_input1->evaluate() && m_input2->evaluate();

		case Type::OR:
			return m_input1->evaluate() || m_input2->evaluate();

		case Type::XOR:
			return m_input1->evaluate() ^ m_input2->evaluate();

		default:
			assert( ! "Unknown element type" );
	}
}

/*****************************************************************************/
