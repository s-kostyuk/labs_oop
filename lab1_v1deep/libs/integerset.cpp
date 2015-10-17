//
// Created by srg on 01.10.15.
//

#include "integerset.hpp"

/*****************************************************************************/

IntegerSet::IntegerSet()
	: m_tree()
    , m_nOfElements(0)
{ }

IntegerSet::IntegerSet( const int * _pArray, const int _nOfElements )
	: m_tree( _pArray, _nOfElements )
	, m_nOfElements( (unsigned long) _nOfElements )
{ }

IntegerSet::IntegerSet( const int * _pArray, const unsigned long _nOfElements )
	: m_tree( _pArray, _nOfElements )
	, m_nOfElements( _nOfElements )
{ }

IntegerSet::IntegerSet( std::initializer_list<int> _l )
	: m_tree( _l )
	, m_nOfElements( _l.size() )
{ }

IntegerSet::IntegerSet( const IntegerSet & _s )
	: m_tree( _s.m_tree )
	, m_nOfElements( _s.m_nOfElements )
{ }

IntegerSet::IntegerSet( IntegerSet && _s )
	: m_tree( std::move( _s.m_tree ) )
	, m_nOfElements( _s.m_nOfElements )
{ }

IntegerSet & IntegerSet::operator = ( const IntegerSet & _s ) {
	m_tree = _s.m_tree;
	m_nOfElements = _s.m_nOfElements;

	return *this;
}

IntegerSet & IntegerSet::operator = ( IntegerSet && _s ) {
	m_tree = std::move( _s.m_tree );
	m_nOfElements = _s.m_nOfElements;

	return *this;
}

/*****************************************************************************/

IntegerSet & IntegerSet::operator += ( const int _key ) {
	m_tree += _key;
	++ m_nOfElements;

	return *this;
}

IntegerSet & IntegerSet::operator -= ( const int _key ) {
	m_tree -= _key;
	-- m_nOfElements;

	return *this;
}

IntegerSet   IntegerSet::operator &  ( const IntegerSet & _s ) const {
	IntegerSet result;

	Iterator itSet1 = this->begin();
	Iterator itSet2 = _s.begin();

	while( itSet1 != this->end() && ( itSet2 != _s.end()) ) {
		if( *itSet1 == *itSet2 ) {
			result += *itSet1;
			++ itSet1;
			++ itSet2;
		}

		else if( *itSet1 < *itSet2 )
			++ itSet1;

		else
			++ itSet2;
	}

	return result;
}

IntegerSet & IntegerSet::operator &= ( const IntegerSet & _s ) {
	*this = *this & _s;
	return *this;
}

IntegerSet   IntegerSet::operator |  ( const IntegerSet & _s ) const {
	IntegerSet result( *this );

	result |= _s;

	return result;
}

IntegerSet & IntegerSet::operator |= ( const IntegerSet & _s ) {
	for( int x : _s )
		*this += x;

	return *this;
}

IntegerSet   IntegerSet::operator -  ( const IntegerSet & _s ) const {
	IntegerSet result( *this );

	for( int x : _s )
		result -= x;

	return result;
}

/*****************************************************************************/
