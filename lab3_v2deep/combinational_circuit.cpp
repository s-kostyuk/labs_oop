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

CombinationalCircuit::CombinationalCircuit( )
		:   m_isFinalized( false )
{ }

/*****************************************************************************/

void CombinationalCircuit::checkChangeAvailable() const {

	if( m_isFinalized )
		throw std::logic_error( Messages::ChangesInFinalizedCircuit );

}

/*****************************************************************************/

void CombinationalCircuit::checkIsCorrect() const {

	if( m_ports.empty() )
		throw std::logic_error( Messages::CircuitWithoutPorts );

	if( m_elements.empty() )
		throw std::logic_error( Messages::CircuitWithoutElements );


	/* TODO: Сделать тут проверку схемы на целостность (этакий Trace()).
	 * Проверить, все ли элементы схемы, упомянутые в добавленых элементах,
	 * сохранены внутри схемы.
	 */
}

/*****************************************************************************/

void CombinationalCircuit::addPort( std::unique_ptr< Port > _p ) {

	checkChangeAvailable();

	if( ! _p )
		throw std::logic_error( Messages::WrongPointerToPort );

	m_ports.emplace( std::make_pair(_p->getName(), std::move( _p ) ) );

}

/*****************************************************************************/

void CombinationalCircuit::addElement( std::unique_ptr< Element > _e ) {

	checkChangeAvailable();

	if( ! _e )
		throw std::logic_error( Messages::WrongPointerToElement );

	m_elements.push_back( std::move( _e ) );

}

/*****************************************************************************/

void CombinationalCircuit::finalize() {

	if( m_isFinalized )
		throw std::logic_error( Messages::CircuitAlreadyFinalized );

	checkIsCorrect();

	m_isFinalized = true;

}

/*****************************************************************************/

bool CombinationalCircuit::getValue( const std::string & _portName ) const {

	PortContainer::const_iterator foundPort = m_ports.find( _portName );

	if( foundPort == m_ports.end() )
		throw std::logic_error( Messages::NonExistentPort );

	return foundPort->second->getValue();

}

/*****************************************************************************/

void CombinationalCircuit::setValue( const std::string & _inputPortName, const bool _value ) const {

	PortContainer::const_iterator foundPort = m_ports.find( _inputPortName );

	if( foundPort == m_ports.end() )
		throw std::logic_error( Messages::NonExistentPort );

	// TODO: Может лучше заменить dynamic_cast на что-то побыстрее
	InputPort * pTarget = dynamic_cast< InputPort * >( foundPort->second.get() );

	if( !pTarget )
		throw std::logic_error( Messages::NonInputPort );

	pTarget->setValue( _value );

}

/*****************************************************************************/
