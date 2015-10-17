//
// Created by srg on 01.10.15.
//

#ifndef INTEGERSET_HPP
#define INTEGERSET_HPP

#include "rbtree.hpp"
#include <utility>

/*****************************************************************************/

class IntegerSet {

public:
	/*************************************************************************/

	typedef RBTree::Iterator Iterator;

	/*************************************************************************/

	IntegerSet();
	IntegerSet( const int * _pArray, const int _nOfElements );
	IntegerSet( std::initializer_list< int > _l );

	IntegerSet( const IntegerSet & _s );
	IntegerSet( IntegerSet && _s );

	IntegerSet & operator = ( const IntegerSet & _s );
	IntegerSet & operator = ( IntegerSet && _s );

	~IntegerSet() { this->clear(); }

	void clear() { m_tree.Clear(); }

	int getSize() const;
	bool hasKey( const int _key ) const;

	Iterator begin() const;
	Iterator end() const;

	IntegerSet & operator += ( const int _key );
	IntegerSet & operator -= ( const int _key );

	IntegerSet   operator &  ( const IntegerSet & _s ) const;
	IntegerSet & operator &= ( const IntegerSet & _s );

	IntegerSet   operator |  ( const IntegerSet & _s ) const;
	IntegerSet & operator |= ( const IntegerSet & _s );

	IntegerSet   operator -  ( const IntegerSet & _s ) const;

	bool operator == ( const IntegerSet & _s ) const;
	bool operator != ( const IntegerSet & _s ) const;

private:
	friend std::ostream & operator << ( std::ostream & _o, const IntegerSet & _s );

	RBTree m_tree;

};

/*****************************************************************************/

inline int IntegerSet::getSize() const {
	return m_tree.GetNOfElements();
}

inline bool IntegerSet::hasKey( const int _key ) const {
	return m_tree.HasKey( _key );
}

inline IntegerSet::Iterator IntegerSet::begin() const {
	return m_tree.begin();
}

inline IntegerSet::Iterator IntegerSet::end() const {
	return m_tree.end();
}

/*****************************************************************************/

inline bool IntegerSet::operator == ( const IntegerSet & _s ) const {
	return m_tree == _s.m_tree;
}

inline bool IntegerSet::operator != ( const IntegerSet & _s ) const {
	return !( *this == _s );
}

/*****************************************************************************/

inline std::ostream & operator << ( std::ostream & _o, const IntegerSet & _s ) {
	return _o << _s.m_tree;
}

/*****************************************************************************/

#endif //INTEGERSET_HPP
