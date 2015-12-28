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

/*****************************************************************************/

class CombinationalCircuit {

	/*-----------------------------------------------------------------*/

public:

	/*-----------------------------------------------------------------*/

	CombinationalCircuit();

	~CombinationalCircuit() = default;

	/*-----------------------------------------------------------------*/

	void addPort( std::unique_ptr< Port > _p );
	void addElement( std::unique_ptr< Element > _e );

	void finalize();

	/*-----------------------------------------------------------------*/

	void setValue( const std::string & _inputPortName, const bool _value ) const;

	bool getValue( const std::string & _portName ) const;

	/*-----------------------------------------------------------------*/

private:

	/*-----------------------------------------------------------------*/

	typedef std::unordered_map< std::string, std::unique_ptr< Port > > PortContainer;

	PortContainer m_ports;

	std::vector< std::unique_ptr< Element > > m_elements;

	bool m_isFinalized;

	/*-----------------------------------------------------------------*/

	void checkChangeAvailable() const;
	void checkIsCorrect() const;

	/*-----------------------------------------------------------------*/

};

/*****************************************************************************/

#endif //_COMBINATIONAL_CIRCUIT_HPP_
