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
#include <limits>
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
#include <array>
#include <cstdio>
#include <functional>
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
#include <prism/Allocator>
#include <prism/LogAllocator>
#include <prism/functor>
#include <prism/Map>
#include <prism/h/BinarySearchTree.h>
#include <prism/Version>
#include <prism/PrismVersion>
#include <prism/type_traits>
#include <prism/UniquePointer>
#include <prism/h/Foo.h>

using namespace prism;
using namespace std;


void f(int&);		// binds to lvalue
void f(const int&);	// binds to lvalue, const lvalue, rvalue, const rvalue
void f(int&&);		// binds to rvalue
void f(const int&&);// binds to rvalue, const rvalue

void f(int&&) {
	cout << "ha!\n";
}

template <typename T>
struct HasPublicType_value_type {
	typedef char 	yes[1];
	typedef char 	no[2];

	template <typename C>
	static yes& 	test(typename C::value_type*);
	template <typename>
	static no& 		test(...);

	static const bool value = sizeof(test<T>(0)) == 1;
};

template <typename T>
struct Container {
	typedef T key_type;
	Container() noexcept(prism::IsFundamental<T>::value) {}
//	Container() = delete;
	void foo() {}
};

class Base{};
class Derived : public Base{};

template <typename T>
void printValue(const T& value) {
	cout << value << endl;
}

int main(int argc, char * argv[]) {
	// to run certain test cases use string with this format: "*Class1*:*Class2*:*ClassN*"
	// to run a single test within a test case use: "*Class.test*" e.g. "*Stack.pop*"
	::testing::GTEST_FLAG(filter) = "*ReverseIteratorTest*";
	::testing::InitGoogleTest(&argc, argv);




	return RUN_ALL_TESTS();
//	return 0;
}





/* REFERENCE BINDINGS
 * http://www.codesynthesis.com/~boris/blog/2012/07/24/const-rvalue-references/

 non-const lvalue reference
 -- non-const lvalue of the same type

 const lvalue reference
 -- non-const lvalue of the same type
 -- const lvalue of the same type
 -- non-const rvalue of the same type
 -- const rvalue of the same type

 non-const rvalue reference
 -- non-const rvalue of the same type

 const rvalue reference
 -- non-const rvalue of the same type
 -- const rvalue of the same type

*/
