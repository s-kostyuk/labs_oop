//
// Created by srg on 23.09.15.
//

#include "bstree.hpp"
#include "bstree_symm_walk_alternative.hpp"
#include "computation_time.hpp"

#include <cstdlib>
#include <iostream>
#include <vector>

void PrintTree( const BSTree::Node & _node ) {
    //std::cout << _node.m_key << " ";
}

int main() {
    srand( time( NULL ) );

    BSTree * pT = BSTreeCreate();

    int nOfElements = 1000000;
    for ( int i = 0, temp; i < nOfElements; i++ ) {
        temp = rand() % 1000000;
        if( nOfElements < 20 )
            std::cout << "Inserted temp = " << temp << "\n";

        BSTreeInsertKey( * pT, temp );
    }

    std::cout << std::endl;

    /*std::vector<int> temp {66, 175, 515, 545, 626, 907, 911, 983};

    for( int x : temp )
        BSTreeInsertKey( * pT, x );

     */

    double time;
    if( nOfElements < 20 )
        std::cout << "Symm walk for tree: \n";

    FixComputationTime();

    BSTreeSymmetricWalk ( *pT, PrintTree );
    FixComputationTime( & time );
    std::cout << "\nRecursive realization finished for " << time << " seconds" << std::endl;

    std::cout << "And" << std::endl;
    FixComputationTime();

    BSTreeAltSymmetricWalk ( *pT, PrintTree );
    FixComputationTime( & time );
    std::cout << "\nNon-recursive realization finished for " << time << " seconds" << std::endl;

    BSTreeDestroy( pT );

    return 0;
}