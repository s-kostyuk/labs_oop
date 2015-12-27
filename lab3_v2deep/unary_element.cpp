//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 26.12.15.
//

/*****************************************************************************/

#include "unary_element.hpp"

#include "messages.hpp"

#include <stdexcept>
#include <assert.h>

/*****************************************************************************/

UnaryElement::UnaryElement( const Type _t, const Element * const _input )
		:   m_type( _t )
		,   m_input( _input )
{

	// TODO: В конструкторе выбирать реализацию evaluate в соответсвии с типом

	if( ! m_input )
		throw std::logic_error( Messages::WrongPointerToInputElement );

}

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
