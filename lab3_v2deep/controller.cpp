//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 28.12.15.
//

/*****************************************************************************/

#include "controller.hpp"

/*****************************************************************************/

#include "realization/all_ports.hpp"
#include "realization/all_elements.hpp"
#include "realization/messages.hpp"

/*****************************************************************************/

#include <string>
#include <cstring>
#include <stdexcept>
#include <iomanip>

/*****************************************************************************/

bool GetValue( const char * const _sStart, size_t _lenght ) {

	if( ! strncmp( _sStart, "true", _lenght ) )
		return true;

	else if( ! strncmp( _sStart, "false", _lenght ) )
		return false;

	else
		throw std::logic_error( Messages::InvalidValue );

}

Controller::Controller( std::unique_ptr< CombinationalCircuit > _storedC )
{
	m_circuit = std::move( _storedC );
}

/*****************************************************************************/

void Controller::executeTestFile( std::istream & _input, std::ostream & _output ) {

	std::string lineBuffer;
	const char * pOperCode;
	const char * pPortName;
	const char * pNewValue;
	const char * pOther;
	long lenght;

	while( std::getline( _input, lineBuffer ) ) {

		if( lineBuffer.empty() )
			continue;

		pOperCode = lineBuffer.c_str();

		pPortName = strpbrk( pOperCode, " " ) + 1;

		if( (pPortName - 1) == 0 )
			throw std::logic_error( Messages::UnspecifiedPort );

		pNewValue = strpbrk( pPortName, " " ) + 1;

		// Длина кода операции
		lenght = pPortName - pOperCode - 1;

		if( !strncmp( pOperCode, "SET_INPUT", lenght ) ) {

			pOther = strpbrk( pNewValue, " " );

			if( pOther != nullptr )
				throw std::logic_error( Messages::UnexpectedTextInLine );

			if( (pNewValue - 1) == 0 )
				throw std::logic_error( Messages::UnspecifiedValue );

			lenght = pNewValue - pPortName - 1;

			m_circuit->setValue(
					std::string( pPortName, lenght ),
					GetValue( pNewValue, strlen( pNewValue ) )
			);

		}

		else if( !strncmp( pOperCode, "SHOW_PORT", lenght ) ) {

			if( (pNewValue - 1) != 0 )
				throw std::logic_error( Messages::UnexpectedTextInLine );

			_output << "Got value "
				<< std::boolalpha
				<< m_circuit->getValue( std::string( pPortName ) )
				<< " on port \"" << std::string( pPortName )
				<< "\"\n";

		}

		else
			throw std::logic_error( Messages::UnknownOperation );

	}

}

/*****************************************************************************/
