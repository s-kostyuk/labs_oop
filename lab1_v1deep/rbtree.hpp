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

	class Node {
	private:
		int m_value;

		enum Color { RED, BLACK } m_color;

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

		Node::Color GetColor() { return m_color; }

		Node * GetParent() { return m_pParent; }
		Node * GetLeft() { return m_pLeft; }
		Node * GetRight() { return m_pRight; }

		Node * FindMinChild();
		Node * FindMaxChild();
		Node * FindRightParent();

		/* Лишние функции в классах откровенно раздражают
		 * (используется буквально один раз, но повышает читабельность)
		 */
		bool IsLeftChild() { return this == m_pParent->m_pLeft; }
	};

	void DestroySubtree( Node * _pRoot );

    Node * InsertBase( int _key );
    Node * DeleteBase( int _key );

    Node * CreateNode ( int _key );
    void   LeftRotate ( Node * _l );
    void   RightRotate( Node * _r );
    Node * FindKeyNode( const int _key ) const;

	Node * m_pRoot;
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

std::ostream & operator << ( std::ostream & _o, const RBTree & _t );

/*****************************************************************************/

#endif //RBTREE_HPP
