//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 27.12.15.
//

/*****************************************************************************/

#include "combinational_circuit.hpp"
#include "all_ports.hpp"
#include "all_elements.hpp"

/*****************************************************************************/

#include "testslib.hpp"
#include "messages.hpp"
#include <memory>

/*****************************************************************************/

typedef std::unique_ptr< CombinationalCircuit > PCombCirc;

/*****************************************************************************/

std::unique_ptr< CombinationalCircuit >
CreateSingleXORCirc() {

	InputPort inputAPort( "a" );
	InputPort inputBPort( "b" );

	InputPortElement aProxy( inputAPort );
	InputPortElement bProxy( inputBPort );

	BinaryElement element( BinaryElement::Type::XOR, &aProxy, &bProxy );

	OutputPort output( "f" );

	output.setInput( &element );

	return std::unique_ptr< CombinationalCircuit >(
			new CombinationalCircuit(
				{ &inputAPort, &inputBPort, &output },
				{ &element }
			)
	);

}

/*****************************************************************************/

std::unique_ptr< CombinationalCircuit >
Create4to1MX() {



}

/*****************************************************************************/

DECLARE_OOP_TEST( test_XOR_circuit_creation ) {

	InputPort inputAPort( "a" );
	InputPort inputBPort( "b" );

	InputPortElement aProxy( inputAPort );
	InputPortElement bProxy( inputBPort );

	BinaryElement element( BinaryElement::Type::XOR, &aProxy, &bProxy );

	OutputPort output( "f" );

	output.setInput( &element );

	CombinationalCircuit circuit(
			{ &inputAPort, &inputBPort, &output },
			{ &element }
	);

	assert( circuit.getValue( "a" ) == inputAPort.getValue() );
	assert( circuit.getValue( "b" ) == inputBPort.getValue() );

	assert( !circuit.getValue( "f" ) );

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_XOR_circuit_behaviour ) {

	PCombCirc circuit = std::move( CreateSingleXORCirc() );

	circuit->setValue( "a", true );

	assert( circuit->getValue( "f" ) );

	circuit->setValue( "b", true );

	assert( ! circuit->getValue( "f" ) );

	circuit->setValue( "a", false );

	assert( circuit->getValue( "f" ) );

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_circuit_set_output_value ) {

	PCombCirc circuit = std::move( CreateSingleXORCirc() );

	ASSERT_THROWS(
			circuit->setValue( "f", true ),
			Messages::NonInputPort
	);

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_circuit_set_value_on_invalid_port ) {

	PCombCirc circuit = std::move( CreateSingleXORCirc() );

	ASSERT_THROWS(
			circuit->setValue( "aaaaaaaaaa", true ),
			Messages::NonExistentPort
	);

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_circuit_get_value_on_invalid_port ) {

	PCombCirc circuit = std::move( CreateSingleXORCirc() );

	ASSERT_THROWS(
			circuit->getValue( "aaaaaaaaaa" ),
			Messages::NonExistentPort
	);

}

/*****************************************************************************/