//
// Created by betatester on 26.09.15.
//

#include "rbtree.hpp"

#include <stdexcept>

/*****************************************************************************/



/*****************************************************************************/

RBTree::RBTree() {
	m_pRoot = nullptr;
}

RBTree::RBTree(int * pArray, int _nOfElements)
	: RBTree()
{
	if( _nOfElements <= 0 || ! pArray )
		throw std::logic_error( "Invalid parameters" );
}

RBTree::RBTree( std::initializer_list<int> _l )
	: RBTree()
{
	for( int x : _l )
		*this += x;
}

RBTree::~RBTree() {
	DestroySubtree( m_pRoot );
}

void RBTree::DestroySubtree( Node * _pRoot ) {
	if( ! _pRoot )
		return;

	DestroySubtree( _pRoot->GetLeft() );
	DestroySubtree( _pRoot->GetRight() );
	delete _pRoot;
}

int RBTree::GetSize() const {
	Iterator curr = begin();
	int counter = 0;

	while( curr != end() )
		counter ++ ;

	return counter;
}

int RBTree::Minimum() const {
	if( ! m_pRoot )
		throw std::logic_error( "The tree is empty" );

	return m_pRoot->FindMinChild()->GetValue();
}

int RBTree::Maximum() const {
	if( ! m_pRoot )
		throw std::logic_error( "The tree is empty" );

	return m_pRoot->FindMaxChild()->GetValue();
}

/*****************************************************************************/

RBTree::Iterator::Iterator( Node * _pNode )
	: m_pCurrent( _pNode )
{
}

int RBTree::Iterator::operator * () const {
	return m_pCurrent->GetValue();
}

bool RBTree::Iterator::operator == ( Iterator i ) const {
	return this->m_pCurrent == i.m_pCurrent;
}

bool RBTree::Iterator::operator != ( Iterator i ) const {
	return !( *this == i );
}

RBTree::Iterator& RBTree::Iterator::operator ++ () {
	validate();

	if( m_pCurrent->GetRight() )
		m_pCurrent = m_pCurrent->GetRight()->FindMinChild();

	else if( m_pCurrent->GetParent() )
		m_pCurrent = m_pCurrent->FindRightParent();

	else
		m_pCurrent = nullptr;

}

RBTree::Iterator  RBTree::Iterator::operator ++ ( int ) {
	++ *this;
}

/*****************************************************************************/
