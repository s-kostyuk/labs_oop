//
// Created by srg on 23.09.15.
//

#include "bstree_symm_walk_alternative.hpp"

inline bool isLeftChild( BSTree::Node * _n ) {
    return _n->m_pParent->m_pLeft == _n;
}

BSTree::Node * findMin( BSTree::Node * _root ) {
    while( _root && _root->m_pLeft )
        _root = _root->m_pLeft;

    return _root;
}

BSTree::Node * findRightParent( BSTree::Node * _n ) {
    while ( _n && _n ->m_pParent ) {
    if ( isLeftChild( _n ) )
        return _n->m_pParent;

    _n = _n->m_pParent;
    }

    return nullptr;
}

BSTree::Node * getNext( BSTree::Node * _n ) {
    if( ! _n )
        return nullptr;

    if( _n->m_pRight )
        return findMin( _n->m_pRight );

    if( _n->m_pParent )
        return findRightParent( _n );

    return nullptr;
}

void BSTreeAltSymmetricWalk ( const BSTree & _tree, BSTreeWalkFunction _f ) {
    BSTree::Node * pCurrent = findMin( _tree.m_pRoot );

    while( pCurrent ) {
        ( * _f )( * pCurrent );
        pCurrent = getNext( pCurrent );
    }
}
