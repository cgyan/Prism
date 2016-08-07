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


using namespace prism;
using namespace std;

bool isOdd(int n) { return n%2 == 1; }
bool isEven(int n) { return n%2 == 0; }
bool isNegative(int n) { return n<0; }
void print(int n) { cout << n << endl; }

int main(int argc, char * argv[]) {
	// to run certain test cases use string with this format: "*Class1*:*Class2*:*ClassN*"
//	::testing::GTEST_FLAG(filter) = "*String*";
//	::testing::InitGoogleTest(&argc, argv);

	Array<int> c(12);
	c[0] = 4;
	c[1] = 11;
	c[2] = 3;
	c[3] = 2;
	c[4] = 6;
	c[5] = 9;
	c[6] = 1;
	c[7] = 8;
	c[8] = 5;
	c[9] = 7;
	c[10] = 12;
	c[11] = 10;
//
	prism::make_heap(c.begin(), c.end());
//
	cout << c << endl;

	prism::make_heap(c.begin(), c.end());

	cout << c;

//	return RUN_ALL_TESTS();
//	return 0;
}

















