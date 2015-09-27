//
// Created by srg on 21.09.15.
// Using UTF-8
//

#ifndef RBTREE_HPP
#define RBTREE_HPP

#include <initializer_list>
#include <iostream>

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

		bool operator == ( Iterator i ) const;
		bool operator != ( Iterator i ) const;

		Iterator & operator ++ ();
		Iterator operator ++ ( int );

	private:
		friend class RBTree;

		void validate () const;

		Node * m_pCurrent;
	};
	/*************************************************************************/

	RBTree();
	RBTree( int * pArray, int _nOfElements );
	RBTree( std::initializer_list< int > _l );

	RBTree( const RBTree & _t );
	RBTree( RBTree && _t );

    ~RBTree();

	int GetSize() const;
    bool HasKey( const int _key ) const;
    int Minimum() const;
    int Maximum() const;

	Iterator begin() const;
	Iterator end() const;

	void operator += ( int _key );
	void operator -= ( int _key );

	bool operator == ( const RBTree & _t ) const;
	bool operator != ( const RBTree & _t ) const;

private:
	friend class Iterator;

	void   DestroyRecursive( Node * _pRoot );
	Node * CopyRecursive ( Node * _pSource, Node * _pNewNodeParent );

	Node * InsertBase ( int _key );
	void   InsertFixup( Node * x );
	Node * DeleteBase( const int _key );
	Node * DeleteFixup( Node * _n );

	void   Transplant( Node * _pNode, Node * _pOtherNode );
	void   LeftRotate ( Node * _l );
	void   RightRotate( Node * _r );
	Node * FindKeyNode( const int _key ) const;

	Node * m_pRoot;

	class Node {
	public:
		enum Color { RED, BLACK };

	private:
		friend Node * RBTree::DeleteFixup( Node * _n );
		int m_value;

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

		int GetValue() { return m_value; }

		Node::Color GetColor() { return ( this ) ?  m_color : BLACK; }

		Node * GetParent() { return m_pParent; }
		Node * GetLeft()   { return m_pLeft;   }
		Node * GetRight()  { return m_pRight;  }

		void SetColor( Node::Color _c ) { m_color = _c; }

		void SetParent( Node * _p ) { m_pParent = _p; }
		void SetLeft  ( Node * _l ) { m_pLeft   = _l; }
		void SetRight ( Node * _r ) { m_pRight  = _r; }

		Node * FindMinChild();
		Node * FindMaxChild();
		Node * FindRightParent();

		/* Лишние функции в классах откровенно раздражают
		 * (используется буквально один раз, но повышает читабельность)
		 */
		bool IsLeftChild()  { return this == m_pParent->m_pLeft;  }
		bool IsRightChild() { return this == m_pParent->m_pRight; }
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
