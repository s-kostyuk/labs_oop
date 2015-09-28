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
	DestroyRecursive( m_pRoot );
}

RBTree::RBTree( const RBTree & _t ) {
	m_pRoot = CopyRecursive( _t.m_pRoot, nullptr );
}

RBTree::RBTree( RBTree && _t )
	: m_pRoot( _t.m_pRoot )
{
	_t.m_pRoot = nullptr;
}

/*****************************************************************************/

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
		return;

	InsertFixup( x );
}

void RBTree::operator -= ( int _key ) {
	CormenDelete( _key );
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

void RBTree::DestroyRecursive( Node * _pRoot ) {
	if( ! _pRoot )
		return;

	DestroyRecursive( _pRoot->GetLeft()  );
	DestroyRecursive( _pRoot->GetRight() );
	delete _pRoot;
}

RBTree::Node * RBTree::CopyRecursive( Node * _pSource, Node * _pNewNodeParent ) {
	// Idea from russian Stack Overflow: http://goo.gl/HRVaB4

	if( _pSource == nullptr )
		return nullptr;

	Node * pNewNode = new Node( _pSource->GetValue() );
	pNewNode->SetColor( _pSource->GetColor() );

	pNewNode->SetLeft( CopyRecursive( _pSource->GetLeft(), pNewNode ));
	pNewNode->SetRight( CopyRecursive( _pSource->GetRight(), pNewNode ));
	pNewNode->SetParent( _pNewNodeParent );

	return pNewNode;
}

RBTree::Node * RBTree::InsertBase( int _key ) {
	if( ! m_pRoot ) {
		m_pRoot = new Node( _key );
		return m_pRoot;
	}

	Node * pCurrent = m_pRoot;

	while( pCurrent ) {
		if( pCurrent->GetValue() == _key )
			return nullptr;

		else if( _key < pCurrent->GetValue() ) {
			if( pCurrent->GetLeft() )
				pCurrent = pCurrent->GetLeft();

			else {
				Node * pNewNode = new Node( _key );
				pNewNode->SetParent( pCurrent );
				pCurrent->SetLeft( pNewNode );
				return pNewNode;
			}
		}

		else {
			if( pCurrent->GetRight() )
				pCurrent = pCurrent->GetRight();

			else {
				Node * pNewNode = new Node( _key );
				pNewNode->SetParent( pCurrent );
				pCurrent->SetRight( pNewNode );
				return pNewNode;
			}
		}
	}

	assert( ! "Error in insertion, you must not be here" );
	return nullptr;
}

void RBTree::InsertFixup( Node * x ) {
	/* Что такое x, y, z - см. алгоритм вставки в красно-черное дерево
	 * ( Кормен и др.: "Алгоритмы: построение и анализ". Раздел 13.3 )
	 */

	Node * p;

	while( x && ( p = x->GetParent() ) && p->GetColor() == Node::RED ) {
		Node * pp = p->GetParent();

		if( p->IsLeftChild() ) {
			Node * y = pp->GetRight();

			if( y->GetColor() == Node::RED ) {
				p->SetColor( Node::BLACK );
				y->SetColor( Node::BLACK );
				pp->SetColor( Node::RED );
				x = pp;
			}

			else {
				if( x == p->GetRight() ) {
					x = p;
					LeftRotate( x );
				}

				p  = x->GetParent();
				pp = p->GetParent();

				p->SetColor( Node::BLACK );

				if( pp ) {
					pp->SetColor( Node::RED );
					RightRotate( pp );
				}
			}
		}

		else {
			Node * y = pp->GetLeft();

			if( y->GetColor() == Node::RED ) {
				p->SetColor( Node::BLACK );
				y->SetColor( Node::BLACK );
				pp->SetColor( Node::RED );
				x = pp;
			}

			else {
				if( x == p->GetLeft() ) {
					x = p;
					RightRotate( x );
				}

				p  = x->GetParent();
				pp = p->GetParent();

				p->SetColor( Node::BLACK );

				if( pp ) {
					pp->SetColor( Node::RED );
					LeftRotate( pp );
				}
			}
		}
	}

	m_pRoot->SetColor( Node::BLACK );

}

// Алгоритм удаления ключа из красно-черного дерева -
// см. Cormen: "Introduction to Algorithms", 3-е издание, раздел 13.4
void RBTree::CormenDelete( const int _key ) {
	Node * z = FindKeyNode( _key );

	if( ! z )
		return;

	Node * y = z;

	Node::Color yOriginalColor = y->GetColor();

	Node * x;

	if( ! z->GetLeft() ) {
		x = z->GetLeft();
		Transplant( z, z->GetRight() );
	}
	else if ( ! z->GetRight() ) {
		x = z->GetLeft();
		Transplant( z, z->GetLeft() );
	}

	else {
		y = z->GetRight()->FindMinChild();
		yOriginalColor = y->GetColor();
		x = y->GetRight();

		if( y->GetParent() == z )
			x->SetParent( y );
		else {
			Transplant( y, y->GetRight() );
			y->SetRight( z->GetRight() );
			y->GetRight()->SetParent( y );
		}

		Transplant( z, y );

		y->SetLeft( z->GetLeft() );
		y->GetLeft()->SetParent( y );
		y->SetColor( z->GetColor() );
	}

	delete z;

	if( yOriginalColor == Node::BLACK )
		DeleteFixup( x );
}

/*

void RBTree::DeleteFixup( Node * _n ) { }

*/

void RBTree::Transplant( Node * _pNode, Node * _pOtherNode ) {
	if( ! _pNode->GetParent() ) {
		assert( _pNode == m_pRoot );
		m_pRoot = _pOtherNode;
	}

	else if( _pNode->IsLeftChild() )
		_pNode->GetParent()->SetLeft ( _pOtherNode );

	else if( _pNode->IsRightChild() )
		_pNode->GetParent()->SetRight( _pOtherNode );

	else
		assert( ! "Transplant error" );

	if( _pOtherNode )
		_pOtherNode->SetParent( _pNode->GetParent());

}

void RBTree::LeftRotate( Node * _l ) {
	Node * r = _l->GetRight();
	if( ! r )
		return;

	_l->SetRight( r->GetLeft() );
	if( _l->GetRight())
		_l->GetRight()->SetParent( _l );

	r->SetParent( _l->GetParent());
	if( ! r->GetParent() )
		m_pRoot = r;
	else if( _l->IsLeftChild() )
		_l->GetParent()->SetLeft( r );
	else if( _l->IsRightChild() )
		_l->GetParent()->SetRight( r );
	else
		assert( ! "Error in rotation, you must not be here" );

	r->SetLeft( _l );
	_l->SetParent( r );
}

void RBTree::RightRotate( Node * _r ) {
	Node * l = _r->GetLeft();
	if( ! l )
		return;

	_r->SetLeft( l->GetRight() );
	if( _r->GetLeft())
		_r->GetLeft()->SetParent( _r );

	l->SetParent( _r->GetParent());
	if( ! l->GetParent() )
		m_pRoot = l;
	else if( _r->IsLeftChild() )
		_r->GetParent()->SetLeft( l );
	else if( _r->IsRightChild() )
		_r->GetParent()->SetRight( l );
	else
		assert( ! "Error in rotation, you must not be here" );

	l->SetRight( _r );
	_r->SetParent( l );
}

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

std::ostream & operator << ( std::ostream & _o, const RBTree & _t ) {
	RBTree::Iterator pCurrent = _t.begin();

	_o << "{ " << *pCurrent ++;

	while( pCurrent != _t.end() )
		_o << ", " << *pCurrent ++;

	_o << " }";

	return _o;
}

/*****************************************************************************/
