//
// Created by betatester on 26.09.15.
// Using UTF-8
//

#include "rbtree.hpp"

#include <stdexcept>
#include <cassert>

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

void RBTree::operator += ( int _key ) {
	Node * x = InsertBase( _key );

	if( ! x )
		throw std::logic_error( "Failed to insert key" );

	DeleteFixup( x );
}

bool RBTree::operator == ( const RBTree & _t ) const {
	Iterator pThisTree  = this->begin();
	Iterator pOtherTree = _t.begin();

	// Выходим из цикла, если полностью обошли оба дерева
	while( pThisTree != this->begin() && pOtherTree != _t.end() ) {

		// Если одно из деревьев содержит меньше элементов, чем другое - выходим
		if( pThisTree != this->begin() || pOtherTree != _t.end() )
			return false;

		// Если хоть один элемент не совпадает - выходим
		if( *pThisTree != *pOtherTree )
			return false;

		++ pThisTree;
		++ pOtherTree;
	}

	// Если мы не вышли из цикла досрочно - деревья равны
	return true;
}

bool RBTree::operator != ( const RBTree & _t ) const {
	return !( *this == _t );
}

/*****************************************************************************/

/*
RBTree::Node * RBTree::InsertBase( int _key ) { }

void RBTree::InsertFixup( Node * _n ) { }

RBTree::Node * RBTree::DeleteBase( int _key ) { }

RBTree::Node * RBTree::DeleteFixup( Node * _n ) { }

RBTree::Node * RBTree::CreateNode( int _key ) { }

void RBTree::LeftRotate( Node * _l ) { }

void RBTree::RightRotate( Node * _r ) { }
*/

RBTree::Node * RBTree::FindKeyNode( const int _key ) const {
	Node * pCurrent = m_pRoot;
	while( pCurrent ) {
		if( _key == pCurrent->GetValue() )
			return pCurrent;

		else if( _key < pCurrent->GetValue())
			pCurrent = pCurrent->GetLeft();

		else
			pCurrent = pCurrent->GetRight();
	}

	return nullptr;
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
