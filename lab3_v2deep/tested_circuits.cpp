//
// Created by Sergey Kostyuk (http://git.io/vBvMH) on 28.12.15.
//

/*****************************************************************************/

#include "tested_circuits.hpp"
#include "realization/all_ports.hpp"
#include "realization/all_elements.hpp"

/*****************************************************************************/

#include <cstdio>
#include <array>

/*****************************************************************************/

std::unique_ptr< CombinationalCircuit >
CreateSingleXORCirc() {

	std::unique_ptr< CombinationalCircuit > pCircut =
			std::make_unique< CombinationalCircuit >();

	InputPort * pInputAPort = new InputPort( "a" );
	InputPort * pInputBPort = new InputPort( "b" );

	InputPortElement * pA = new InputPortElement( *pInputAPort );
	InputPortElement * pB = new InputPortElement( *pInputBPort );

	BinaryElement * pElement = new BinaryElement(
			BinaryElement::Type::XOR, pA, pB
	);

	OutputPort * pOutput = new OutputPort( "f" );

	pOutput->setInput( pElement );

	pCircut->addPort( std::unique_ptr< Port >( pInputAPort ) );
	pCircut->addPort( std::unique_ptr< Port >( pInputBPort ) );

	pCircut->addElement( std::unique_ptr< Element >( pA ) );
	pCircut->addElement( std::unique_ptr< Element >( pB ) );

	pCircut->addElement( std::unique_ptr< Element >( pElement ) );

	pCircut->addPort( std::unique_ptr< Port >( pOutput ) );

	pCircut->finalize();

	return pCircut;

}

/*****************************************************************************/

std::unique_ptr< CombinationalCircuit >
Create4to1MX() {

	// TODO: ЭТО никто не должен видеть
	// FIXME: Ниже - боль и ад

	// Умный указатель на всю комбинационную схему
	std::unique_ptr< CombinationalCircuit > pCircut =
			std::make_unique< CombinationalCircuit >();

	// Буффер для формирования имен портов
	char nameBuf[ 3 ];

	// Порты данных
	std::array< InputPort *, 4 > D;

	for( unsigned int i = 0; i < D.size(); ++ i ) {
		sprintf( nameBuf, "D%d", i );

		D.at( i ) = new InputPort( nameBuf );
	}

	for( InputPort * p : D ) {
		pCircut->addPort( std::unique_ptr< Port >( p ) );
	}

	// Порты управления
	InputPort * A1 = new InputPort( "A1" );
	InputPort * A2 = new InputPort( "A2" );

	pCircut->addPort( std::unique_ptr< Port >( A1 ) );
	pCircut->addPort( std::unique_ptr< Port >( A2 ) );

	// Элементы для подключения портов данных
	std::array< InputPortElement *, 4 > DProxy;

	for( unsigned int i = 0; i < DProxy.size(); ++ i ) {
		DProxy.at( i ) = new InputPortElement( * D.at( i ) );
	}

	for( InputPortElement * p : DProxy ) {
		pCircut->addElement( std::unique_ptr< Element >( p ) );
	}

	// Элементы для подключения портов управления
	InputPortElement * pA1 = new InputPortElement( * A1 );
	InputPortElement * pA2 = new InputPortElement( * A2 );

	pCircut->addElement( std::unique_ptr< Element >( pA1 ) );
	pCircut->addElement( std::unique_ptr< Element >( pA2 ) );

	// Инверторы
	UnaryElement * pNotA1 = new UnaryElement( UnaryElement::Type::INVERTOR, pA1 );
	UnaryElement * pNotA2 = new UnaryElement( UnaryElement::Type::INVERTOR, pA2 );

	pCircut->addElement( std::unique_ptr< Element >( pNotA1 ) );
	pCircut->addElement( std::unique_ptr< Element >( pNotA2 ) );

	// Элементы И - первая линия, кобинация управляющих входов
	BinaryElement * pNOT_A1_NOT_A2 = new BinaryElement(
			BinaryElement::Type::AND, pNotA1, pNotA2
	);
	
	BinaryElement * pNOT_A1_A2 = new BinaryElement(
			BinaryElement::Type::AND, pNotA1, pA2
	);

	BinaryElement * pA1_NOT_A2 = new BinaryElement(
			BinaryElement::Type::AND, pA1, pNotA2
	);

	BinaryElement * pA1_A2 = new BinaryElement(
			BinaryElement::Type::AND, pA1, pA2
	);

	// Элементы И - вторая линия, кобинация с входами данных
	BinaryElement * pNOT_A1_NOT_A2_D0 = new BinaryElement(
			BinaryElement::Type::AND, pNOT_A1_NOT_A2, DProxy.at( 0 )
	);

	BinaryElement * pNOT_A1_A2_D1 = new BinaryElement(
			BinaryElement::Type::AND, pNOT_A1_A2, DProxy.at( 1 )
	);

	BinaryElement * pA1_NOT_A2_D2 = new BinaryElement(
			BinaryElement::Type::AND, pA1_NOT_A2, DProxy.at( 2 )
	);

	BinaryElement * pA1_A2_D3 = new BinaryElement(
			BinaryElement::Type::AND, pA1_A2, DProxy.at( 3 )
	);

	// TODO: Может все-таки сделать констуктор с InitializerList< указатели > ???
	pCircut->addElement( std::unique_ptr< Element >( pNOT_A1_NOT_A2 ) );
	pCircut->addElement( std::unique_ptr< Element >( pNOT_A1_NOT_A2_D0 ) );

	pCircut->addElement( std::unique_ptr< Element >( pNOT_A1_A2 ) );
	pCircut->addElement( std::unique_ptr< Element >( pNOT_A1_A2_D1 ) );

	pCircut->addElement( std::unique_ptr< Element >( pA1_NOT_A2 ) );
	pCircut->addElement( std::unique_ptr< Element >( pA1_NOT_A2_D2 ) );

	pCircut->addElement( std::unique_ptr< Element >( pA1_A2 ) );
	pCircut->addElement( std::unique_ptr< Element >( pA1_A2_D3 ) );

	// Элементы ИЛИ, первая линия
	BinaryElement * pLeftOR = new BinaryElement(
			BinaryElement::Type::OR, pNOT_A1_NOT_A2_D0, pNOT_A1_A2_D1
	);

	BinaryElement * pRightOR = new BinaryElement(
			BinaryElement::Type::OR, pA1_NOT_A2_D2, pA1_A2_D3
	);

	// Элемент ИЛИ, вершина иерархии
	BinaryElement * pTopOR = new BinaryElement(
			BinaryElement::Type::OR, pLeftOR, pRightOR
	);

	pCircut->addElement( std::unique_ptr< Element >( pLeftOR ) );
	pCircut->addElement( std::unique_ptr< Element >( pRightOR ) );
	pCircut->addElement( std::unique_ptr< Element >( pTopOR ) );

	// Выход комбинационной схемы
	OutputPort * pOutput = new OutputPort( "F" );
	pOutput->setInput( pTopOR );

	pCircut->addPort( std::unique_ptr< Port >( pOutput ) );

	pCircut->finalize();

	return pCircut;

}

/*****************************************************************************/