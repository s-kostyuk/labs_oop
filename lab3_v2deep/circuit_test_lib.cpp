//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 28.12.15.
//

/*****************************************************************************/

#include "circuit_test_lib.hpp"

/*****************************************************************************/

// TODO: Переписать реализацию, может выбрать другие аргументы

void TestBehaviour(
		const CombinationalCircuit & _c,
		const std::initializer_list< std::string > _inputPortNames,
		const std::initializer_list< std::string > _outputPortNames,
		const std::initializer_list< TruthTableRow > _values )
{

	for( const TruthTableRow & _v : _values ) {

		assert( _v.m_inputs.size() == _inputPortNames.size() );
		assert( _v.m_outputs.size() == _outputPortNames.size() );

		auto iPortNamesIt = _inputPortNames.begin();
		auto iPortValuesIt = _v.m_inputs.begin();

		while ( iPortNamesIt != _inputPortNames.end() ){

			_c.setValue( *iPortNamesIt, *iPortValuesIt );

			++ iPortNamesIt;
			++ iPortValuesIt;

		}

		auto oPortNamesIt = _outputPortNames.begin();
		auto oPortValuesIt = _v.m_outputs.begin();

		while ( oPortNamesIt != _outputPortNames.end() ) {

			assert( _c.getValue( *oPortNamesIt ) == *oPortValuesIt );

			++ oPortNamesIt;
			++ oPortValuesIt;

		}

	}

}

/*****************************************************************************/

void GenerateTestFileForXOR( std::ostream & _o ) {

	_o << "SET_INPUT a true" << "\n";
	_o << "SET_INPUT b false" << "\n";
	_o << "SHOW_PORT f" << std::endl;

}

/*****************************************************************************/
