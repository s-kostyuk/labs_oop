//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 26.12.15.
//

/*****************************************************************************/

#include "binary_element.hpp"

#include "messages.hpp"

#include <stdexcept>
#include <cassert>

/*****************************************************************************/

BinaryElement::BinaryElement( const Type _t, const Element * const _input1, const Element * const _input2 )
		:   m_type( _t )
		,   m_input1( _input1 )
		,   m_input2( _input2 )
{

	// TODO: В конструкторе выбирать реализацию evaluate в соответсвии с типом

	if( ! m_input1 || ! m_input2 )
		throw std::logic_error( Messages::WrongPointerToInputElement );

}

/*****************************************************************************/

bool BinaryElement::evaluate() const {
	switch( m_type ) {

		case Type::AND:
			return m_input1->evaluate() && m_input2->evaluate();

		case Type::OR:
			return m_input1->evaluate() || m_input2->evaluate();

		case Type::XOR:
			return m_input1->evaluate() ^  m_input2->evaluate();

		default:
			assert( ! "Unknown element type" );

	}
}

/*****************************************************************************/
