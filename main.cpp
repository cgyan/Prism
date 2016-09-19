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
#include <prism/tmp/List.h>


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

struct IsOdd {
	bool operator()(int n) {
		return n%2==1;
	}
};

int main(int argc, char * argv[]) {
	// to run certain test cases use string with this format: "*Class1*:*Class2*:*ClassN*"
	// to run a single test within a test case use: "*Class.test*" e.g. "*Stack.pop*"
	::testing::GTEST_FLAG(filter) = "*Deque*";
	::testing::InitGoogleTest(&argc, argv);

	typedef tmp::List<int, LogAllocator<int>> 	List;
	typedef List::iterator	 					Iterator;
	typedef List::const_iterator				ConstIterator;
	typedef tmp::ListNode<int> 					Node;

	List list;



//	return RUN_ALL_TESTS();
//	return 0;
}






