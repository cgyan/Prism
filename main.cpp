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
#include <bitset>
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
	// to run a single test within a test case use: "*Class.test*"
	::testing::GTEST_FLAG(filter) = "*Stack*";
	::testing::InitGoogleTest(&argc, argv);

//	Stack<int> a;
//	a << 1 << 2;
//
//	{
//		Stack<int> b(a);
//
//		cout << "a.start=" << a.sp.data()->storage.start << ", b.start=" << b.sp.data()->storage.start << endl;
//
//	//	cout << (a.sp.data() == b.sp.data()) << endl;
//	//	cout << a.d.refCount() << endl;
//	//	cout << b.d.refCount() << endl;
//
//		cout << "b detaching" << endl;
//		b.push(3);
//
//		cout << "a.start=" << a.sp.data()->storage.start << ", b.start=" << b.sp.data()->storage.start << endl;
//
//		cout << *(a.sp.data()->storage.start) << endl;
//		cout << a.top() << endl;
//		cout << b.top() << endl;
//		cout << (a.sp.data() == b.sp.data()) << endl;
//		cout << a.sp.refCount() << endl;
//		cout << b.sp.refCount() << endl;
//		cout << "";
//	}
//
//	cout << "a.start=" << a.sp.data()->storage.start << endl;
//	cout << *(a.sp.data()->storage.start + 1) << endl;
//	cout << (a.sp.data()->storage.finish - a.sp.data()->storage.start) << endl;
//	cout << a.top() << endl;
//	cout << "";

	Stack<int> a;
	a << 10 << 20 << 30 << 40 << 50;
	Stack<int> b(a);

	cout << "Stack a: " << a << endl;
	cout << "Stack b: " << b << endl;
	cout << "a: top=" << a.top() << " size=" << a.size() << " capacity=" << a.capacity() << endl;
	cout << "b: top=" << b.top() << " size=" << b.size() << " capacity=" << b.capacity() << endl;

	b.pop();

	cout << "Stack a: " << a << endl;
	cout << "Stack b: " << b << endl;
	cout << "a: top=" << a.top() << " size=" << a.size() << " capacity=" << a.capacity() << endl;
	cout << "b: top=" << b.top() << " size=" << b.size() << " capacity=" << b.capacity() << endl;

//	return RUN_ALL_TESTS();
//	return 0;
}

















