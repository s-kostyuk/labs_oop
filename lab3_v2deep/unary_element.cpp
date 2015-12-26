//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 26.12.15.
//

/*****************************************************************************/

#include "unary_element.hpp"

#include <assert.h>

/*****************************************************************************/

bool UnaryElement::evaluate() const {
	// TODO: Выбрать способ получения значения...

	//...через switch...
	switch( m_type ) {

		case Type::BUFFER:
			return m_input->evaluate();

		case Type::INVERTOR:
			return ! m_input->evaluate();

		default:
			assert( ! "Unknown element type" );

	}

	// ... или XOR
	//return m_input->evaluate() ^ ( bool )m_type;
}

/*****************************************************************************/
