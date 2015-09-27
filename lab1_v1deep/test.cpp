//
// Created by srg on 21.09.15.
//

#include "rbtree.hpp"

#include <cstdlib>
#include <ctime>

int main() {
	srand( time( NULL ));

    RBTree testTree( { 10, 9, 3, 2, 1, 7 } );

	std::cout << testTree;

	RBTree testTree2( testTree );

	std::cout << testTree2;

	RBTree testTree3( { 15, 35, 89, 124, 122, 190, 191, 217, 284, 293, 327, 368, 407,
	                    436, 435, 490, 529, 536, 582, 599, 606, 656, 696, 696, 744,
	                    780, 789, 814, 887, 897, 912, 942, 995, 1032, 1068, 1087,
	                    1114, 1121, 1187, 1200, 1237, 1254, 1278, 1324, 1342, 1383,
	                    1405, 1433, 1451, 1489 } );

	/*const int nOfKeys = 50;

	std::cout << "\nInserted: { ";
	for( int i = 0, temp; i < nOfKeys; i++ ) {
		temp = rand() % 50 + 30 * i;
		std::cout << temp << ", ";
		testTree += temp;
	}
	std::cout << "}\n";
	*/

	std::cout << testTree3;

    return 0;
}
