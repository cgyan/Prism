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

struct IsOdd {
	bool operator()(int n) {
		return n%2==1;
	}
};

template <typename AllocType, class T>
void
doAllocatorStuff(const T& value) {
	typename prism::AllocatorTraits<AllocType>::allocator_type alloc;
	cout << alloc.max_size() << endl;

	typename prism::AllocatorTraits<AllocType>::pointer p =
			prism::AllocatorTraits<AllocType>::allocate(alloc, 1);
	prism::AllocatorTraits<AllocType>::construct(alloc, p, value);

	cout << *p << endl;

	prism::AllocatorTraits<AllocType>::destruct(alloc, p);
	prism::AllocatorTraits<AllocType>::deallocate(alloc, p);
}

int main(int argc, char * argv[]) {
	// to run certain test cases use string with this format: "*Class1*:*Class2*:*ClassN*"
	// to run a single test within a test case use: "*Class.test*" e.g. "*Stack.pop*"
	::testing::GTEST_FLAG(filter) = "*Deque*";
	::testing::InitGoogleTest(&argc, argv);

//	doAllocatorStuff<Allocator<int>>(12);
//
//	typedef typename Allocator<int>::template rebind<String>::other StringAlloc;
//	doAllocatorStuff<StringAlloc>("Hello world!");

//	Obj** start;
//	Obj** finish;
//
//	Allocator<Obj> objAllocator;
//	Allocator<Obj*> storageAllocator;
//	Allocator<Obj> bucketAllocator;
//
//	start = storageAllocator.allocate(1);
//	finish = start + 1;
//
//	*start = bucketAllocator.allocate(8);
//
//	Obj* bucket = *start;
//	objAllocator.construct(bucket, 10);
//	objAllocator.construct(bucket+1, 11);
//	objAllocator.construct(bucket+2, 12);
//	objAllocator.construct(bucket+3, 13);
//	objAllocator.construct(bucket+4, 14);
//	objAllocator.construct(bucket+5, 15);
//	objAllocator.construct(bucket+6, 16);
//	objAllocator.construct(bucket+7, 17);
//
//	objAllocator.destroy(bucket);
//	objAllocator.destroy(bucket+1);
//	objAllocator.destroy(bucket+2);
//	objAllocator.destroy(bucket+3);
//	objAllocator.destroy(bucket+4);
//	objAllocator.destroy(bucket+5);
//	objAllocator.destroy(bucket+6);
//	objAllocator.destroy(bucket+7);
//
//	bucketAllocator.deallocate(bucket);
//	storageAllocator.deallocate(start);

	Deque<int> d({1,2,3,4,5,6,7,8,9});

	cout << d << endl;
	cout << "!" << endl;






//	return RUN_ALL_TESTS();
//	return 0;
}






