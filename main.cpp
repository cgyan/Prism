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
#include <ctime>
#include <vector>
#include <stack>
#include <list>
#include <queue>
#include <deque>
#include <forward_list>
#include <climits>
#include <algorithm>
#include <cmath>
#include <prism/Array>
#include <prism/Stack>
#include <prism/List>
#include <prism/Queue>
#include <prism/Vector>
#include <prism/Iterator>
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
#include <prism/algorithms>
#include <prism/Bitvector>


using namespace prism;
using namespace std;

bool isOdd(int n) { return n%2 == 1; }
bool isEven(int n) { return n%2 == 0; }
bool isNegative(int n) { return n<0; }
void print(int n) { cout << n << endl; }

int main(int argc, char * argv[]) {
	// to run certain test cases use string with this format: "*Class1*:*Class2*:*ClassN*"
	::testing::GTEST_FLAG(filter) = "*Bitvector*";
	::testing::InitGoogleTest(&argc, argv);


	int bytes;

//	int bytes = sizeof(short int);
//	cout << "short int has " << bytes << " bytes" << " (" << (8*bytes) << " bits)" << endl;
//	cout << "================================================"<<endl;
//
	bytes = sizeof(unsigned short int);
	cout << "unsigned short int has " << bytes << " bytes" << " (" << (8*bytes) << " bits)" << endl;
	cout << "================================================"<<endl;
//
//	bytes = sizeof(signed long int);
//	cout << "signed long int has " << bytes << " bytes" << " (" << (8*bytes) << " bits)" << endl;
//	cout << "================================================"<<endl;
//
//	bytes = sizeof(char);
//	cout << "char has " << bytes << " bytes" << " (" << (8*bytes) << " bits)" << endl;
//	cout << "================================================"<<endl;
//
//	bytes = sizeof(bool);
//	cout << "bool has " << bytes << " bytes" << " (" << (8*bytes) << " bits)" << endl;
//	cout << "================================================"<<endl;
////
//	//   0000 0000 0000 0000 n
//	//   0000 0000 0000 0010 mask
//	// &
//	//   0000 0000 0000 0101 result
//	unsigned short int n 	= 1;
//	n				 		= (n<<16);
//	cout << n << endl;
//





	return RUN_ALL_TESTS();
//	return 0;
}

















