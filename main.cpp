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
//#include <algorithm>
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
#include <prism/Algorithms>

using namespace prism;
using namespace std;

bool isOdd(int n) { return n%2 == 1; }

int main(int argc, char * argv[]) {
//	::testing::InitGoogleTest(&argc, argv);

	Vector<int> v;
	v << 1 << 7 << 3 << 7 << 7 << 8 << 7 << 7 << 9;

	prism::fill_n(v.begin(), 4, 39);

	cout << v;

//	return RUN_ALL_TESTS();
	return 0;
}

















