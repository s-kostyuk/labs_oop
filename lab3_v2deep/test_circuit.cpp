//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 27.12.15.
//

/*****************************************************************************/

#include "realization/combinational_circuit.hpp"
#include "realization/all_ports.hpp"
#include "realization/all_elements.hpp"
#include "controller.hpp"

/*****************************************************************************/

#include "circuit_test_lib.hpp"
#include "tested_circuits.hpp"

/*****************************************************************************/

#include "testslib.hpp"
#include "realization/messages.hpp"
#include <memory>
#include <fstream>
#include <sstream>

/*****************************************************************************/

DECLARE_OOP_TEST( test_XOR_circuit_creation ) {

	CreateSingleXORCirc();

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_circuit_create_without_ports ) {

	std::unique_ptr< CombinationalCircuit > pCircuit
			= std::make_unique< CombinationalCircuit >();

	ASSERT_THROWS(
			pCircuit->finalize(),
			Messages::CircuitWithoutPorts
	);

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_circuit_create_without_elements ) {

	std::unique_ptr< CombinationalCircuit > pCircuit
			= std::make_unique< CombinationalCircuit >();

	pCircuit->addPort( std::make_unique< InputPort >( "a" ) );

	ASSERT_THROWS(
			pCircuit->finalize(),
			Messages::CircuitWithoutElements
	);

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_circuit_change_structure_after_finalization ) {

	std::unique_ptr< CombinationalCircuit > pCircuit
			= std::make_unique< CombinationalCircuit >();

	InputPort * pInputPort = new InputPort( "a" );

	InputPortElement * pIPortProxy = new InputPortElement( *pInputPort );

	OutputPort * pOutput = new OutputPort( "f" );

	pOutput->setInput( pIPortProxy );

	pCircuit->addPort( std::unique_ptr< Port >( pInputPort ) );

	pCircuit->addElement( std::unique_ptr< Element >( pIPortProxy ) );

	pCircuit->addPort( std::unique_ptr< Port >( pOutput ) );

	pCircuit->finalize();

	ASSERT_THROWS(
			pCircuit->addPort( std::make_unique< InputPort >( "b" ) ),
			Messages::ChangesInFinalizedCircuit
	);

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_circuit_double_finalize ) {

	std::unique_ptr< CombinationalCircuit > pCircuit
			= std::make_unique< CombinationalCircuit >();

	InputPort * pInputPort = new InputPort( "a" );

	InputPortElement * pIPortProxy = new InputPortElement( *pInputPort );

	OutputPort * pOutput = new OutputPort( "f" );

	pOutput->setInput( pIPortProxy );

	pCircuit->addPort( std::unique_ptr< Port >( pInputPort ) );

	pCircuit->addElement( std::unique_ptr< Element >( pIPortProxy ) );

	pCircuit->addPort( std::unique_ptr< Port >( pOutput ) );

	pCircuit->finalize();

	ASSERT_THROWS(
			pCircuit->finalize();,
			Messages::CircuitAlreadyFinalized
	);

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_XOR_circuit_behaviour ) {

	std::unique_ptr< CombinationalCircuit > pCircuit 
			= CreateSingleXORCirc();

	pCircuit->setValue( "a", false );
	pCircuit->setValue( "b", false );

	assert( ! pCircuit->getValue( "f" ) );

	pCircuit->setValue( "a", true );

	assert( pCircuit->getValue( "f" ) );

	pCircuit->setValue( "b", true );

	assert( ! pCircuit->getValue( "f" ) );

	pCircuit->setValue( "a", false );

	assert( pCircuit->getValue( "f" ) );

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_XOR_circuit_behaviour_2 ) {

	std::unique_ptr< CombinationalCircuit > pCircuit
			= CreateSingleXORCirc();

	TestBehaviour(
		*pCircuit,
		{ "a", "b" }, { "f" },
		{
				{ { 0, 0 }, { 0 } }
		    ,   { { 0, 1 }, { 1 } }
			,	{ { 1, 0 }, { 1 } }
			,	{ { 1, 1 }, { 0 } }
		}
	);

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_circuit_set_output_value ) {

	std::unique_ptr< CombinationalCircuit > pCircuit
			= CreateSingleXORCirc();

	ASSERT_THROWS(
			pCircuit->setValue( "f", true ),
			Messages::NonInputPort
	);

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_circuit_set_value_on_invalid_port ) {

	std::unique_ptr< CombinationalCircuit > pCircuit
			= CreateSingleXORCirc();

	ASSERT_THROWS(
			pCircuit->setValue( "z", true ),
			Messages::NonExistentPort
	);

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_circuit_get_value_from_invalid_port ) {

	std::unique_ptr< CombinationalCircuit > pCircuit
			= CreateSingleXORCirc();

	ASSERT_THROWS(
			pCircuit->getValue( "z" ),
			Messages::NonExistentPort
	);

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_MX_creation ) {

	std::unique_ptr< CombinationalCircuit > pCircuit
			= Create4to1MX();

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_MX_behaviour ) {

	std::unique_ptr< CombinationalCircuit > pCircuit
			= Create4to1MX();

	TestBehaviour(
			*pCircuit,
			{ "A1", "A2", "D0", "D1", "D2", "D3" }, { "F" },
			{
					{ { 0, 0, 0, 0, 0, 0 }, { 0 } },
					{ { 0, 0, 1, 0, 0, 0 }, { 1 } },
					{ { 0, 1, 0, 0, 0, 0 }, { 0 } },
					{ { 0, 1, 0, 1, 0, 0 }, { 1 } },
					{ { 1, 0, 0, 0, 0, 0 }, { 0 } },
					{ { 1, 0, 0, 0, 1, 0 }, { 1 } },
					{ { 1, 1, 0, 0, 0, 0 }, { 0 } },
					{ { 1, 1, 0, 0, 0, 1 }, { 1 } },
			}
	);

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_execution_for_XOR ) {

	Controller controller( CreateSingleXORCirc() );

	std::ofstream oFile( "test.txt" );

	GenerateTestFileForXOR( oFile );

	oFile.close();

	std::ifstream iFile( "test.txt" );

	std::stringstream result;

	controller.executeTestFile( iFile, result );

	assert( result.str() == "Got value true on port \"f\"\n" );

}

/*****************************************************************************/
