//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 27.12.15.
//

/*****************************************************************************/

#include "combinational_circuit.hpp"
#include "all_ports.hpp"

/*****************************************************************************/

#include "messages.hpp"
#include <stdexcept>

/*****************************************************************************/

CombinationalCircuit::CombinationalCircuit(
		std::initializer_list< Port * > _allPorts,
        std::initializer_list< Element * > _elements )
{

	for( Port * pPort : _allPorts ) {

		m_ports.insert( std::make_pair(
				pPort->getName(), std::unique_ptr< Port >( pPort )
		) );

	}

	for( Element * pElement : _elements )
		m_elements.push_back( std::unique_ptr< Element >( pElement ) );

}

/*****************************************************************************/

bool CombinationalCircuit::getValue( const std::string & _portName ) const {

	PortContainer::const_iterator foundPort = m_ports.find( _portName );

	if( foundPort == m_ports.end() )
		throw std::logic_error( Messages::NonExistentPort );

	return foundPort->second->getValue();

}

/*****************************************************************************/

void CombinationalCircuit::setValue( const std::string & _inputPortName, const bool _value ) {

	PortContainer::iterator foundPort = m_ports.find( _inputPortName );

	if( foundPort == m_ports.end() )
		throw std::logic_error( Messages::NonExistentPort );

	// TODO: Может лучше заменить dynamic_cast на что-то побыстрее
	InputPort * pTarget = dynamic_cast< InputPort * >( foundPort->second.get() );

	if( !pTarget )
		throw std::logic_error( Messages::NonInputPort );

	pTarget->setValue( _value );

}

/*****************************************************************************/
