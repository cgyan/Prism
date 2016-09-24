/*
 * main.cpp
 *
 *  Created on: Dec 28, 2014
 *      Author: iainhemstock
 */

#define PRISM_DEBUG_

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
#include <prism/Time>
#include <prism/Pair>
#include <prism/Deque>
#include <prism/utilities>
#include <prism/memory>
#include <prism/Allocator>
#include <prism/LogAllocator>
#include <prism/h/Obj.h>

using namespace prism;
using namespace std;

//bool isOdd(int n) { return n%2 == 1; }
bool isEven(int n) { return n%2 == 0; }
bool isNegative(int n) { return n<0; }
void print(int n) { cout << n << endl; }
template <class ForwardIterator>
std::ostream& printRange(std::ostream& out, ForwardIterator start, ForwardIterator end) {
	while (start != end) out << *start++ << endl;
	return out;
}

struct IsOddPredicate {
	bool operator()(int n) {
		return n%2==1;
	}
};



int main(int argc, char * argv[]) {
	// to run certain test cases use string with this format: "*Class1*:*Class2*:*ClassN*"
	// to run a single test within a test case use: "*Class.test*" e.g. "*Stack.pop*"
	::testing::GTEST_FLAG(filter) = "*List*";
	::testing::InitGoogleTest(&argc, argv);



	typedef prism::List<int, LogAllocator<int>> 	IntList;
	typedef prism::List<Obj, LogAllocator<Obj>>		ObjList;

	List<int> c({5,4,3,2,1});
	prism::sort_quicksort(c.begin(), c.end());
	cout << c << endl;

//	std::initializer_list<int> il = {4,2,3,5,6,1,8,9};
//	ObjList list;
//	list.push_back(Obj(1));
//	list.push_back(Obj(2));
//	list.push_back(Obj(3));
//	list.push_back(Obj(4));
//	cout << list << endl;


//	printRange(cout, c.begin(), c.end());




//	return RUN_ALL_TESTS();
//	return 0;
}






