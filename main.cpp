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

int main(int argc, char * argv[]) {
	// to run certain test cases use string with this format: "*Class1*:*Class2*:*ClassN*"
	// to run a single test within a test case use: "*Class.test*" e.g. "*Stack.pop*"
	::testing::GTEST_FLAG(filter) = "*UniquePointerTest*";
	::testing::InitGoogleTest(&argc, argv);

	UniquePointer<Foo> p = makeUnique<Foo>("Bonnie");
	cout << *p << endl;






//	return RUN_ALL_TESTS();
//	return 0;
}

//139   template<typename _Tp, typename _Alloc>
//140     typename vector<_Tp, _Alloc>::iterator
//141     vector<_Tp, _Alloc>::
//142     _M_erase(iterator __position)
//143     {
//144       if (__position + 1 != end())
//145         _GLIBCXX_MOVE3(__position + 1, end(), __position);
//146       --this->_M_impl._M_finish;
//147       _Alloc_traits::destroy(this->_M_impl, this->_M_impl._M_finish);
//148       return __position;
//149     }
//150
//151   template<typename _Tp, typename _Alloc>
//152     typename vector<_Tp, _Alloc>::iterator
//153     vector<_Tp, _Alloc>::
//154     _M_erase(iterator __first, iterator __last)
//155     {
//156       if (__first != __last)
//157         {
//158           if (__last != end())
//159             _GLIBCXX_MOVE3(__last, end(), __first);
//160           _M_erase_at_end(__first.base() + (end() - __last));
//161         }
//162       return __first;
//163     }



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

































