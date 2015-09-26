//
// Created by betatester on 26.09.15.
// Using UTF-8
//

#include "rbtree.hpp"

#include <stdexcept>

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

RBTree::Node * RBTree::Node::FindMinChild() {
	Node * pCurrent = this;

	while( pCurrent && pCurrent->GetLeft() )
		pCurrent = pCurrent->GetLeft();

	return pCurrent;
}

RBTree::Node * RBTree::Node::FindMaxChild() {
	Node * pCurrent = this;

	while( pCurrent && pCurrent->GetRight() )
		pCurrent = pCurrent->GetRight();

	return pCurrent;
}

RBTree::Node * RBTree::Node::FindRightParent() {
	Node * pCurrent = this;

	while( pCurrent && pCurrent->GetParent() ) {
		if( pCurrent->IsLeftChild() )
			return pCurrent->m_pParent;

		pCurrent = pCurrent->m_pParent;
	}

	return nullptr;
}

/*****************************************************************************/

RBTree::Iterator::Iterator( Node * _pNode )
	: m_pCurrent( _pNode )
{
}

void RBTree::Iterator::validate() const {
	if ( !m_pCurrent )
		throw std::logic_error( "Invalid tree iterator state" );
}

int RBTree::Iterator::operator * () const {
	return m_pCurrent->GetValue();
}

bool RBTree::Iterator::operator == ( Iterator i ) const {
	return m_pCurrent == i.m_pCurrent;
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

	return *this;
}

RBTree::Iterator  RBTree::Iterator::operator ++ ( int ) {
	Iterator copy = *this;

	++ *this;

	return copy;
}

/*****************************************************************************/
