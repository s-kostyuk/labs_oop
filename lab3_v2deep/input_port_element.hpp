//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 26.12.15.
//

/*****************************************************************************/

#ifndef _INPUT_PORT_ELEMENT_HPP_
#define _INPUT_PORT_ELEMENT_HPP_

/*****************************************************************************/

#include "element.hpp"

/*****************************************************************************/

class InputPort;

/*****************************************************************************/

class InputPortElement : public Element {

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	InputPortElement( const InputPort & _input );

	~InputPortElement() override = default;

	/*-----------------------------------------------------------------*/

	bool evaluate() const override;

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	const InputPort & m_input;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif //_INPUT_PORT_ELEMENT_HPP_
