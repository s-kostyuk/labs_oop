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

/*****************************************************************************/

struct TestSetUnit {
	bool a;
	bool b;
	bool f;
};

/*****************************************************************************/

void TestBinaryElements(
		BinaryElement::Type _type,
		std::initializer_list< TestSetUnit > _set
);

/*****************************************************************************/

DECLARE_OOP_TEST( test_input_port ) {

	InputPort p( "x" );

	assert( !p.getValue() );
	assert( p.getName() == "x" );

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_input_port_wrong_name ) {

	ASSERT_THROWS(
			InputPort p( "" ),
			Messages::WrongPortName
	);

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_input_port_set_value ) {

	InputPort p( "x" );

	p.setValue( true );

	assert( p.getValue() );

	p.setValue( false );

	assert( !p.getValue() );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_input_port_element ) {

	InputPort port( "x" );

	InputPortElement e( port );

	assert( !e.evaluate() );

	port.setValue( true );

	assert( e.evaluate() );

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_output_port ) {

	OutputPort output( "y" );

	assert( ! output.getValue() );
	assert( output.getName() == "y" );

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_output_port_wrong_name ) {

	ASSERT_THROWS(
			OutputPort output( "" ),
			Messages::WrongPortName
	);

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_output_port_with_input ) {

	InputPort inputPort( "x" );

	InputPortElement e( inputPort );

	OutputPort output( "y" );

	output.setInput( &e );

	assert( output.getValue() == e.evaluate() );
	assert( ! output.getValue() );

	inputPort.setValue( true );

	assert( output.getValue() == e.evaluate() );
	assert( output.getValue() );

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_buffer ) {

	InputPort inputPort( "x" );

	InputPortElement e( inputPort );

	UnaryElement buffer( UnaryElement::Type::BUFFER, &e );

	assert( !buffer.evaluate() );

	inputPort.setValue( true );

	assert( buffer.evaluate() );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_invertor ) {

	InputPort inputPort( "x" );

	InputPortElement e( inputPort );

	UnaryElement invertor( UnaryElement::Type::INVERTOR, &e );

	assert( invertor.evaluate() );

	inputPort.setValue( true );

	assert( !invertor.evaluate() );
}

/*****************************************************************************/

DECLARE_OOP_TEST( test_unary_element_nullptr_input ) {

	ASSERT_THROWS(
			UnaryElement ue( UnaryElement::Type::INVERTOR, nullptr ),
			Messages::WrongPointerToElement
	);

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_double_invertor ) {

	InputPort inputPort( "x" );

	InputPortElement e( inputPort );

	UnaryElement inv1( UnaryElement::Type::INVERTOR, &e );

	UnaryElement inv2( UnaryElement::Type::INVERTOR, &inv1 );

	assert( ! inv2.evaluate() );

	inputPort.setValue( true );

	assert( inv2.evaluate() );

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_AND_element ) {

	TestBinaryElements(
			BinaryElement::Type::AND,
			{
					     { 0, 0, 0 }
					,	{ 0, 1, 0 }
					,	{ 1, 0, 0 }
					,	{ 1, 1, 1 }
			}
	);

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_OR_element ) {

	TestBinaryElements(
			BinaryElement::Type::OR,
			{
					     { 0, 0, 0 }
					,	{ 0, 1, 1 }
					,	{ 1, 0, 1 }
					,	{ 1, 1, 1 }
			}
	);

}

/*****************************************************************************/

DECLARE_OOP_TEST( test_XOR_element ) {

	TestBinaryElements(
			BinaryElement::Type::XOR,
			{
					     { 0, 0, 0 }
					,	{ 0, 1, 1 }
					,	{ 1, 0, 1 }
					,	{ 1, 1, 0 }
			}
	);

}

/*****************************************************************************/

void TestBinaryElements(
		BinaryElement::Type _type,
		std::initializer_list< TestSetUnit > _set
) {

	InputPort inputAPort( "a" );
	InputPort inputBPort( "b" );

	InputPortElement aProxy( inputAPort );
	InputPortElement bProxy( inputBPort );

	BinaryElement element( _type, &aProxy, &bProxy );

	for( const TestSetUnit & ts : _set ) {

		inputAPort.setValue( ts.a );
		inputBPort.setValue( ts.b );

		assert( element.evaluate() == ts.f );
	}

}

/*****************************************************************************/
