/*
 * main.cpp
 *
 *  Created on: Dec 28, 2014
 *      Author: iainhemstock
 */


#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <list>
#include <queue>
#include <deque>
#include <forward_list>
#include <climits>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <chrono>
#include <ctime>
#include <initializer_list>
#include <utility>
#include <type_traits>
#include <new>
#include <memory>
#include <map>
#include <prism/Array>
#include <prism/Stack>
#include <prism/List>
#include <prism/Queue>
#include <prism/Vector>
#include <prism/iterator>
#include <prism/Point>
#include <prism/Pointf>
#include <prism/OutOfBoundsException>
#include <prism/SharedPointer>
#include <prism/Fraction>
#include <prism/Mathf>
#include <prism/Size>
#include <prism/Rect>
#include <prism/Circle>
#include <prism/String>
#include <prism/Char>
#include <prism/algorithm>
#include <prism/Bitvector>
#include <prism/Time>
#include <prism/Pair>
#include <prism/Deque>
#include <prism/utility>
#include <prism/memory>
#include <prism/Allocator>
#include <prism/LogAllocator>
#include <prism/functor>
#include <prism/Map>
//#include <prism/h/Obj.h>

using namespace prism;
using namespace std;



int main(int argc, char * argv[]) {
	// to run certain test cases use string with this format: "*Class1*:*Class2*:*ClassN*"
	// to run a single test within a test case use: "*Class.test*" e.g. "*Stack.pop*"
//	::testing::GTEST_FLAG(filter) = "*functor*";
//	::testing::InitGoogleTest(&argc, argv);

	typedef prism::pair<const int,int>		 	pair;
	typedef BSTNode<pair>			 			Node;
	typedef Node*								node_pointer;
	typedef BSTIterator<pair,false>				iterator;


	node_pointer np 			= new Node(pair(7,7));
	np->left 					= new Node(pair(5,5));
	np->left->parent			= np;

	np->left->left 				= new Node(pair(2,2));
	np->left->left->parent 		= np->left;

	np->right 					= new Node(pair(9,9));
	np->right->parent			= np;

	np->right->left 			= new Node(pair(8,8));
	np->right->left->parent 	= np->right;

	np->right->right 			= new Node(pair(10,10));
	np->right->right->parent 	= np->right;

	np->left->left->right		= new Node(pair(3,3));
	np->left->left->right->parent = np->left->left;

	iterator it(np->left->left);

	for (int i=0; i<8; i++) {
		if (it.np == np->parent)
			cout << "reached the end" << endl;
		else {
			cout << it->first << " " << it->second << "\n";
			it++;
		}
	}



//	pair p(7,7);
//	Node * node = new Node(p);
//
//	pair p2(5,5);
//	node->left = new Node(p2);
//
//	pair p3(9,9);
//	node->right = new Node(p3);
//
//	pair p4(2,2);
//	node->left->left = new Node(p4);
//
//	pair p5(8,8);
//	node->right->left = new Node(p5);
//
//	pair p6(10,10);
//	node->right->right = new Node(p6);
//
//	iterator it(node->left->left);
//	cout << (*it).first << " " << (*it).second << endl;



//	return RUN_ALL_TESTS();
//	return 0;
}













