//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 28.12.15.
//

/*****************************************************************************/

#ifndef _TESTED_CIRCUITS_HPP_
#define _TESTED_CIRCUITS_HPP_

/*****************************************************************************/

#include "combinational_circuit.hpp"

/*****************************************************************************/

std::unique_ptr< CombinationalCircuit > CreateSingleXORCirc();
std::unique_ptr< CombinationalCircuit > Create4to1MX();

/*****************************************************************************/

#endif //_TESTED_CIRCUITS_HPP_
