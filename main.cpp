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
//#include <prism/h/Obj.h>

using namespace prism;
using namespace std;

prism::String myfunc(){ return String::number(20); }
struct A { void x() {}; };

int main(int argc, char * argv[]) {
	// to run certain test cases use string with this format: "*Class1*:*Class2*:*ClassN*"
	// to run a single test within a test case use: "*Class.test*" e.g. "*Stack.pop*"
	::testing::GTEST_FLAG(filter) = "*type_traits*";
	::testing::InitGoogleTest(&argc, argv);



	return RUN_ALL_TESTS();
//	return 0;
}



/*
	using ARRAY 							= int[1];
	using CHAR								= char;
	using CLASS								= C;
	using DOUBLE							= double;
	using LONG_DOUBLE						= long double;
	using ENUM 								= E;
	using CONST_ENUM 						= E const;
	using VOLATILE_ENUM 					= E volatile;
	using UNION 							= U;
	using CONST_UNION						= U const;
	using VOLATILE_UNION					= U volatile;
	using FLOAT 							= float;
	using CONST_FLOAT						= float const;
	using VOLATILE_FLOAT					= float volatile;
	using INTEGRAL 							= int;
	using CONST_INTEGRAL 					= int const;
	using VOLATILE_INTEGRAL					= int volatile;
	using CONST_VOLATILE_INTEGRAL			= int volatile const;
	using FUNCTION 							= int(int);
	using MEMBER_FUNCTION_POINTER 			= int (C::*)();
	using CONST_MEMBER_FUNCTION_POINTER 	= int (C::*)() const;
	using MEMBER_OBJECT_POINTER 			= int C::*;
	using CONST_MEMBER_OBJECT_POINTER 		= int C::* const;
	using VOLATILE_MEMBER_OBJECT_POINTER 	= int C::* volatile;
	using LREF 								= int&;
	using RREF 								= int&&;
	using POINTER 							= int*;
	using CONST_POINTER_TO_T				= int* const;
	using CONST_POINTER_TO_CONST_T			= const int* const;
	using POINTER_TO_CONST_T				= const int*;
	using VOLATILE_POINTER_TO_T				= int* volatile;
	using VOLATILE_POINTER_TO_CONST_T		= const int* volatile;
	using POINTER_TO_VOLATILE_T				= volatile int*;
	using VOID								= void;
 */





































