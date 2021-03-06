//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 26.12.15.
//

/*****************************************************************************/

#ifndef _UNARY_ELEMENT_HPP_
#define _UNARY_ELEMENT_HPP_

/*****************************************************************************/

#include "element.hpp"

/*****************************************************************************/

class UnaryElement : public Element {

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	enum class Type {
		BUFFER, INVERTOR
	};

	/*-----------------------------------------------------------------*/

	UnaryElement( const Type _t, const Element * const _input );
	~UnaryElement() override = default;

	/*-----------------------------------------------------------------*/

	Type getType();

	/*-----------------------------------------------------------------*/

	bool evaluate() const override;

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	const Type m_type;

	const Element * const m_input;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline UnaryElement::Type UnaryElement::getType() {
	return m_type;
}

/*****************************************************************************/

#endif //_UNARY_ELEMENT_HPP_
