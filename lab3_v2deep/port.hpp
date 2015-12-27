//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 26.12.15.
//

/*****************************************************************************/

#ifndef _PORT_HPP_
#define _PORT_HPP_

/*****************************************************************************/

#include <string>

/*****************************************************************************/

class Port {

	/*-----------------------------------------------------------------*/

protected:

	/*-----------------------------------------------------------------*/

	Port( const std::string & _portName );

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	virtual ~Port() = default;

	/*-----------------------------------------------------------------*/

	Port ( const Port & _p ) = delete;
	Port & operator = ( const Port & _p ) = delete;

	/*-----------------------------------------------------------------*/

	virtual bool getValue() const = 0;

	const std::string & getName() const;

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	const std::string m_portName;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

inline const std::string & Port::getName() const {
	return m_portName;
}

/*****************************************************************************/

#endif //_PORT_HPP_
