//
// Created by srg on 21.09.15.
// Using UTF-8
//

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <initializer_list>
#include <iostream>
#include <cassert>
/*****************************************************************************/

class RBTree {
private:
	class Node;

public:
	/*************************************************************************/

	class Iterator {

	public:
		explicit Iterator ( Node * _pNode = nullptr );

		int operator * () const;

		bool operator == ( Iterator _i ) const;
		bool operator != ( Iterator _i ) const;

		Iterator & operator ++ ();
		Iterator operator ++ ( int );

	private:
		friend class RBTree;

		void validate () const;

		Node * m_pCurrent;
	};

	/*************************************************************************/

	RBTree();
	RBTree( const int * _pArray, const int _nOfElements );
	RBTree( std::initializer_list< int > _l );

	RBTree( const RBTree & _t );
	RBTree( RBTree && _t );

	RBTree & operator = ( const RBTree & _t );
	RBTree & operator = ( RBTree && _t );

    ~RBTree() { Clear(); }

	void Clear();

	int GetNOfElements() const;
    bool HasKey( const int _key ) const;
    int Minimum() const;
    int Maximum() const;

	Iterator begin() const;
	Iterator end() const;

	RBTree & operator += ( const int _key );
	RBTree & operator -= ( const int _key );

	bool operator == ( const RBTree & _t ) const;
	bool operator != ( const RBTree & _t ) const;

private:
	friend class Iterator;

	void   DestroyRecursive( Node * _pRoot );
	Node * CopyRecursive ( Node * _pSource, Node * _pNewNodeParent );

	Node * InsertBase( const int _key );
	void   InsertFixup( Node * x );
	void   CormenDelete( const int _key );
	void   DeleteFixup( Node * x, Node * xParent = nullptr);

	void   Transplant( Node * _pNode, Node * _pOtherNode, Node ** pNilParentContainer = nullptr );
	void   LeftRotate ( Node * _l );
	void   RightRotate( Node * _r );
	Node * FindKeyNode( const int _key ) const;

	/*************************************************************************/

	Node * m_pRoot;

	/*************************************************************************/

	class Node {
	public:
		enum Color { RED, BLACK };

	private:
		const int m_value;

		Color m_color;

		Node * m_pParent;
		Node * m_pLeft;
		Node * m_pRight;

	public:
		Node( int _value )
				: m_value( _value )
				, m_color( RED )
				, m_pParent( nullptr )
				, m_pLeft( nullptr )
				, m_pRight( nullptr )
		{}

		int    GetValue()  { assert( this ); return m_value;   }

		Color  GetColor() { return ( this ) ? m_color : BLACK; }

		Node * GetParent() { assert( this ); return m_pParent; }
		Node * GetLeft()   { assert( this ); return m_pLeft;   }
		Node * GetRight()  { assert( this ); return m_pRight;  }

		void SetColor ( Color  _c ) { assert( this ); m_color   = _c; }

		void SetParent( Node * _p ) { assert( this ); m_pParent = _p; }
		void SetLeft  ( Node * _l ) { assert( this ); m_pLeft   = _l; }
		void SetRight ( Node * _r ) { assert( this ); m_pRight  = _r; }

		Node * FindMinChild();
		Node * FindMaxChild();
		Node * FindRightParent();
		
		bool IsLeftChild()  { assert( this ); return this == m_pParent->m_pLeft;  }
		bool IsRightChild() { assert( this ); return this == m_pParent->m_pRight; }
	};
};

/*****************************************************************************/

inline bool RBTree::HasKey( const int _key ) const {
	return FindKeyNode( _key ) != nullptr;
}

inline RBTree::Iterator RBTree::begin () const
{
	return Iterator( m_pRoot->FindMinChild() );
}

inline RBTree::Iterator RBTree::end () const
{
	return Iterator();
}

/*****************************************************************************/

std::ostream & operator << ( std::ostream & _o, const RBTree & _t );

/*****************************************************************************/

#endif //RBTREE_HPP
