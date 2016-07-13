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
//	v << 1 << 2 << 3 << 4 << 5 << 6 << 7;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);


	Vector<int> vv;
	int count = prism::count_if(v.begin(), v.end(), isOdd);
	vv.resize(count);
	prism::copy_if(v.begin(), v.end(), vv.begin(), isOdd);

//	vector<int>::iterator first = v.begin();
//	while (first != v.end())
//		cout << *(first++) << endl;

	cout << vv;

//	return RUN_ALL_TESTS();
	return 0;
}

















