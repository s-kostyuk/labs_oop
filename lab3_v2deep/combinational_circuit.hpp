//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 27.12.15.
//

/*****************************************************************************/

#ifndef _COMBINATIONAL_CIRCUIT_HPP_
#define _COMBINATIONAL_CIRCUIT_HPP_

/*****************************************************************************/

#include "element.hpp"
#include "port.hpp"

/*****************************************************************************/

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include <initializer_list>

/*****************************************************************************/

class CombinationalCircuit {

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	CombinationalCircuit(
			std::initializer_list< Port *  > _allPorts,
			std::initializer_list< Element * > _elements
	);

	~CombinationalCircuit() = default;

	/*-----------------------------------------------------------------*/

	void setValue( const std::string & _inputPortName, const bool _value );

	bool getValue( const std::string & _portName ) const;

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	typedef std::unordered_map< std::string, std::unique_ptr< Port > > PortContainer;

	PortContainer m_ports;

	std::vector< std::unique_ptr< Element > > m_elements;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif //_COMBINATIONAL_CIRCUIT_HPP_
