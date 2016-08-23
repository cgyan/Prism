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
#include <prism/h/DequeIterator.h>


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
//	::testing::GTEST_FLAG(filter) = "*Deque*";
//	::testing::InitGoogleTest(&argc, argv);

	Block<int>** map_ = new Block<int>*[1];

	Block<int>* block = new Block<int>();
//	block->storage.start[0] = 0;
//	block->storage.start[1] = 1;
//	block->storage.start[2] = 2;
//	block->storage.start[3] = 3;
	block->storage.start[4] = 4;
	block->storage.start[5] = 5;
	block->storage.start[6] = 6;
	block->storage.start[7] = 7;
	block->storage.begin = block->storage.start+4;

	map_[0] = block;

	block = new Block<int>();
	block->storage.start[0] = 10;
	block->storage.start[1] = 11;
	block->storage.start[2] = 12;
	block->storage.start[3] = 13;
	block->storage.start[4] = 14;
	block->storage.start[5] = 15;
	block->storage.start[6] = 16;
	block->storage.start[7] = 17;
	block->storage.end = block->storage.start+2;

	map_[1] = block;

	block = new Block<int>();
	block->storage.start[0] = 20;
	block->storage.start[1] = 21;
	block->storage.start[2] = 22;
	block->storage.start[3] = 23;
	block->storage.start[4] = 24;
//	block->storage.start[5] = 25;
//	block->storage.start[6] = 26;
//	block->storage.start[7] = 27;
	block->storage.end = block->storage.start+5;

	map_[2] = block;

	DequeIterator<int> start(map_[0]->storage.begin, map_);
	DequeIterator<int> end(map_[1]->storage.end, map_+1);
//	DequeIterator<int> end = start;
//	DequeIterator<int> startCopy = start;

//	for (; start != end; start++) {
//		cout << *start << endl;
//	}

	cout << *(start+=12) << endl;



//	return RUN_ALL_TESTS();
//	return 0;
}

















