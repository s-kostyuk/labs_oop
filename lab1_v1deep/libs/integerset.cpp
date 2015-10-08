//
// Created by srg on 01.10.15.
//

#include "integerset.hpp"

/*****************************************************************************/

IntegerSet::Iterator::Iterator()
	: m_treeIt()
{ }

IntegerSet::Iterator::Iterator( RBTree::Iterator _it )
	: m_treeIt( _it )
{ }

IntegerSet::Iterator & IntegerSet::Iterator::operator ++ () {
	++ m_treeIt;
	return *this;
}

IntegerSet::Iterator IntegerSet::Iterator::operator ++( int ) {
	Iterator copy = *this;

	++ *this;

	return copy;
}

/*****************************************************************************/

IntegerSet::IntegerSet()
	: m_tree()
{ }

IntegerSet::IntegerSet( const int * _pArray, const int _nOfElements )
	: m_tree( _pArray, _nOfElements )
{ }

IntegerSet::IntegerSet( std::initializer_list<int> _l )
	: m_tree( _l )
{ }

IntegerSet::IntegerSet( const IntegerSet & _s )
	: m_tree( _s.m_tree )
{ }

IntegerSet::IntegerSet( IntegerSet && _s )
	: m_tree( std::move( _s.m_tree ) )
{ }

IntegerSet & IntegerSet::operator = ( const IntegerSet & _s ) {
	m_tree = _s.m_tree;
	return *this;
}

IntegerSet & IntegerSet::operator = ( IntegerSet && _s ) {
	m_tree = std::move( _s.m_tree );
	return *this;
}

/*****************************************************************************/

IntegerSet & IntegerSet::operator += ( const int _key ) {
	m_tree += _key;

	return *this;
}

IntegerSet & IntegerSet::operator -= ( const int _key ) {
	m_tree -= _key;

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
