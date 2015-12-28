//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 28.12.15.
//

/*****************************************************************************/

#ifndef _CIRCUIT_TEST_LIB_HPP_
#define _CIRCUIT_TEST_LIB_HPP_

/*****************************************************************************/

#include "realization/combinational_circuit.hpp"

/*****************************************************************************/

#include <vector>
#include <cassert>
#include <string>
#include <initializer_list>

/*****************************************************************************/

struct TruthTableRow {
	std::vector< bool > m_inputs;
	std::vector< bool > m_outputs;
};

typedef std::vector< const char * const > PortNames;

/*****************************************************************************/

void TestBehaviour(
		const CombinationalCircuit & _c,
		const std::initializer_list< std::string > _inputPortNames,
		const std::initializer_list< std::string > _outputPortNames,
		const std::initializer_list< TruthTableRow > _values
);

/*****************************************************************************/

#endif //_CIRCUIT_TEST_LIB_HPP_
