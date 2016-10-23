/*
 * algorithmTest.cpp
 * v1
 *
 *  Created on: Aug 7, 2016
 *      Author: iainhemstock
 */


#include <gtest/gtest.h>
#include <prism/algorithm>
#include <algorithm> // todo remove this
#include <prism/functor>
#include <iostream>
#include <cstdlib> // srand()
#include <ctime> // time()
#include <functional> // std::function<>

namespace prism {
namespace test {

class algorithmTest : public ::testing::Test {

};

/**
 * Predicates for tests
 */
bool algorithmTest_isOdd(const int n) { return n%2 == 1; }
bool algorithmTest_isEven(int n) { return n%2 == 0; }
bool algorithmTest_isNegative(int n) { return n<0; }
void algorithmTest_double(int& i) { i *= 2; }
// ============================================================
// TESTS
// ============================================================
/**
 * Test: adjacent_find(first, last)
 */
TEST_F(algorithmTest, adjacentFind) {
	int a[6] = { 1,3,7,7,5,6 };
	int * p = adjacent_find(a, a+6);
	int pValue = *p;
	int pIndex = p-a;

	ASSERT_TRUE(pValue == 7);
	ASSERT_TRUE(pIndex == 2	);
}

/**
 * Test: all_of(first, last, pred)
 */
TEST_F(algorithmTest, all_of) {
	int a[5] = {2,4,6,8,10};
	bool allEven = all_of(a, a+5, prism::even<int>());
	bool allOdd = all_of(a, a+5, prism::odd<int>());
	ASSERT_TRUE(allEven);
	ASSERT_FALSE(allOdd);
}

/**
 * Test: any_of(first, last, pred)
 */
TEST_F(algorithmTest, any_of) {
	int a[6] = {2,4,6,-12,8,10};
	bool anyEven = any_of(a, a+6, prism::even<int>());
	bool anyOdd = any_of(a, a+6, prism::odd<int>());
	ASSERT_TRUE(anyEven);
	ASSERT_FALSE(anyOdd);
}

/**
 * Test: copy
 */
TEST_F(algorithmTest, copy) {
	int a[5] = {1,2,3,4,5};
	int b[5];
	int * it = prism::copy(a, a+5, b);

	ASSERT_EQ(1, b[0]);
	ASSERT_EQ(2, b[1]);
	ASSERT_EQ(3, b[2]);
	ASSERT_EQ(4, b[3]);
	ASSERT_EQ(5, b[4]);
	ASSERT_EQ(b+5, it);
}

/**
 * Test: copy_backward
 */
TEST_F(algorithmTest, copy_backward) {
	int a[5] = {1,2,3,4,5};
	int b[5];
	int * begin = &a[0];
	int * end = begin+5;
	int * otherEnd = &b[0] + 5;

	int * it = prism::copy_backward(begin,end,otherEnd);

	ASSERT_EQ(1, b[0]);
	ASSERT_EQ(2, b[1]);
	ASSERT_EQ(3, b[2]);
	ASSERT_EQ(4, b[3]);
	ASSERT_EQ(5, b[4]);
	ASSERT_EQ(b, it);
}

/**
 * Test: copy_if
 */
TEST_F(algorithmTest, copy_if) {
	int a[5] = {1,2,3,4,5};
	int b[3];

	std::function<bool (int)> pred = [](int i) {
		return i % 2 == 1; // is odd
	};

	int * it = prism::copy_if(a, a+5, b, pred);

	ASSERT_EQ(1, b[0]);
	ASSERT_EQ(3, b[1]);
	ASSERT_EQ(5, b[2]);
	ASSERT_EQ(b+3, it);
}

/**
 * Test: copy_n
 */
TEST_F(algorithmTest, copy_n) {
	int a[5] = {1,2,3,4,5};
	int b[3];

	int * it = prism::copy_n(a+1, 3, b);

	ASSERT_EQ(2, b[0]);
	ASSERT_EQ(3, b[1]);
	ASSERT_EQ(4, b[2]);
	ASSERT_EQ(b+3, it);
}

/**
 * Test: count
 */
TEST_F(algorithmTest, count) {
	int a[11] = {1,2,3,4,5,1,6,7,8,1,9};
	int count = prism::count(a, a+11, 1);

	ASSERT_EQ(3, count);

	count = prism::count(a+1, a+11, 1);
	ASSERT_EQ(2, count);

	count = prism::count(a+1, a+9, 1);
	ASSERT_EQ(1, count);
}

/**
 * Test: count_if
 */
TEST_F(algorithmTest, count_if) {
	int a[5] = {1,2,3,4,5};

	std::function<bool (int)> pred = [](int i) {
		return i%2==0; // is even
	};

	int count = prism::count_if(a, a+5, pred);
	ASSERT_EQ(2, count);

	count = prism::count_if(a, a+3, pred);
	ASSERT_EQ(1, count);
}

/**
 * Test: equal
 */
TEST_F(algorithmTest, equal) {
	int a[5] = {1,2,3,4,5};
	int b[9] = {1,2,3,4,5,2,3,4};

	bool equal = prism::equal(a, a+5, b);
	ASSERT_TRUE(equal);

	equal = prism::equal(a+1, a+5, b+1);
	ASSERT_TRUE(equal);

	equal = prism::equal(a+1, a+3, b+5);
	ASSERT_TRUE(equal);
}

/**
 * Test: fill
 */
TEST_F(algorithmTest, fill) {
	int a[5];
	prism::fill(a, a+5, '*');

	ASSERT_EQ('*', a[0]);
	ASSERT_EQ('*', a[1]);
	ASSERT_EQ('*', a[2]);
	ASSERT_EQ('*', a[3]);
	ASSERT_EQ('*', a[4]);

}

/**
 * Test: fill_n
 */
TEST_F(algorithmTest, fill_n) {
	int a[5];
	prism::fill(a, a+3, '*');

	ASSERT_EQ('*', a[0]);
	ASSERT_EQ('*', a[1]);
	ASSERT_EQ('*', a[2]);
	ASSERT_NE('*', a[3]); // not equals
	ASSERT_NE('*', a[4]); // not equals

}

/**
 * Test: find
 */
TEST_F(algorithmTest, find) {
	int a[5] = {8,6,3,3,5};

	// find first 3
	int * begin = a;
	int * end = a+5;
	int * it = prism::find(begin, end, 3);

	ASSERT_EQ(a+2, it);
	ASSERT_EQ(3, *it);

	// find second 3
	begin = a+3;
	end = a+5;
	it = prism::find(begin, end, 3);
	ASSERT_EQ(a+3, it);
	ASSERT_EQ(3, *it);

	// non-existent value
	begin = a;
	end = a+5;
	it = prism::find(begin, end, 10);
	ASSERT_EQ(end, it);

	// value exists but not in range
	begin = a;
	end = a+4;
	it = prism::find(begin, end, 5);
	ASSERT_EQ(end, it);
}

/**
 * Test: find_if
 */
TEST_F(algorithmTest, find_if) {
	int a[5] = {1,2,3,4,5};

	std::function<bool (int)> greaterThan3 = [](int i) {
		return i > 3;
	};
	std::function<bool (int)> greaterThan5 = [](int i) {
		return i > 5;
	};

	// find 1st value greater than 3
	int * begin = a;
	int * end = a+5;
	int * it = prism::find_if(begin, end, greaterThan3);

	ASSERT_EQ(a+3, it);
	ASSERT_EQ(4, *it);

	// non-existent value
	begin = a;
	end = a+5;
	it = prism::find_if(begin, end, greaterThan5);

	ASSERT_EQ(end, it);
}

/**
 * Test: find_last
 */
TEST_F(algorithmTest, find_last) {
	int a[5] = {1,9,4,9,5};

	// find last 9 in full range
	int * begin = a;
	int * end = a+5;
	int * it = prism::find_last(begin, end, 9);

	ASSERT_EQ(a+3, it);
	ASSERT_EQ(9, *it);

	// find last 9 in subrange [a,a+3]
	begin = a;
	end = a+3;
	it = prism::find_last(begin, end, 9);

	ASSERT_EQ(a+1, it);
	ASSERT_EQ(9, *it);

	// non-existent value
	begin = a;
	end = a+5;
	it = prism::find_last(begin, end, 10);

	ASSERT_EQ(end, it);
}

/**
 * Test: for_each
 */
TEST_F(algorithmTest, for_each) {
	int a[5] = {1,2,3,4,5};
	int * begin = a;
	int * end = a+5;

	std::function<void (int&)> pred = [](int& i) {
		i *= 2;
	};

	// double the value of each element
	// todo test the returned value (func) somehow
	// Suppresses compiler warnings that func is unused
	auto func = prism::for_each(begin, end, pred);
	(void)func;

	ASSERT_EQ(2, a[0]);
	ASSERT_EQ(4, a[1]);
	ASSERT_EQ(6, a[2]);
	ASSERT_EQ(8, a[3]);
	ASSERT_EQ(10, a[4]);
}

/**
 * Test: is_sorted
 */
TEST_F(algorithmTest, is_sorted) {

	// not sorted
	int a[5] = {1,3,5,2,4};
	int * begin = a;
	int * end = a+5;

	bool sorted = prism::is_sorted(begin, end);
	ASSERT_FALSE(sorted);

	// sequentially sorted
	int b[5] = {10,11,12,13,14};
	begin = b;
	end = b+5;
	sorted = prism::is_sorted(begin, end);
	ASSERT_TRUE(sorted);

	// sorted but values not sequential
	int c[5] = {20,40,60,80,100};
	begin = c;
	end = c+5;
	sorted = prism::is_sorted(begin, end);
	ASSERT_TRUE(sorted);
}

/**
 * Test: make+heap
 */
TEST_F(algorithmTest, make_heap) {
	int a[5] = {13,45,34,8,99};
	int * begin = a;
	int * end = a+5;
	prism::make_heap(begin, end);

	ASSERT_EQ(99, a[0]);
	ASSERT_EQ(45, a[1]);
	ASSERT_EQ(34, a[2]);
	ASSERT_EQ(8, a[3]);
	ASSERT_EQ(13, a[4]);
}

/**
 * Test: max
 */
TEST_F(algorithmTest, max) {

	// compare two values
	int a = 45;
	int b = 55;
	int maxValue = prism::max(a,b);
	ASSERT_EQ(b, maxValue);

	// compare two pointers
	int c[5] = {1,2,3,4,5};
	int * p1 = c;
	int * p2 = c+5;
	int * maxPointer = prism::max(p1,p2);
	ASSERT_EQ(p2, maxPointer);
}

/**
 * Test: min
 */
TEST_F(algorithmTest, min) {

	// compare two values
	int a = 45;
	int b = 55;
	int minValue = prism::min(a,b);
	ASSERT_EQ(a, minValue);

	// compare two pointers
	int c[5] = {1,2,3,4,5};
	int * p1 = c;
	int * p2 = c+5;
	int * minPointer = prism::min(p1,p2);
	ASSERT_EQ(p1, minPointer);
}

/**
 * Test: none_of
 */
TEST_F(algorithmTest, none_of) {
	int a[5] = {5,10,15,20,25};

	std::function<bool (int)> pred = [](int i) {
		return i > 20;
	};

	// test first four elements for being larger than 20
	int * begin = a;
	int * end = a+4;
	bool result = prism::none_of(begin, end, pred);

	ASSERT_TRUE(result);

	// test full range for same condition
	begin = a;
	end = a+5;
	result = prism::none_of(begin, end, pred);

	ASSERT_FALSE(result);
}

/**
 * Test: remove
 */
TEST_F(algorithmTest, remove) {
	int a[7] = {1,2,3,2,5,2,7};
	int b[7] = {1,2,3,2,5,2,7}; // identical arrays

	// remove all 2's from full range
	int * begin = a;
	int * end = a+7;
	int * it = prism::remove(begin, end, 2);

	ASSERT_EQ(1, a[0]);
	ASSERT_EQ(3, a[1]);
	ASSERT_EQ(5, a[2]);
	ASSERT_EQ(7, a[3]);
	ASSERT_EQ(a+4, it);

	// remove all 2's from subrange
	// should leave third 2 alone
	begin = b;
	end = b+5;
	it = prism::remove(begin, end, 2);

	ASSERT_EQ(1, b[0]);
	ASSERT_EQ(3, b[1]);
	ASSERT_EQ(5, b[2]);
	ASSERT_EQ(b+3, it);
}

/**
 * Test: remove_copy
 */
TEST_F(algorithmTest, remove_copy) {
	int a[8] = {1,5,3,4,5,6,7,5};
	int b[5];

	// copy all values that are not 5 into other storage
	int * begin = a;
	int * end = a+8;
	int * it = prism::remove_copy(begin, end, b, 5);

	ASSERT_EQ(1, b[0]);
	ASSERT_EQ(3, b[1]);
	ASSERT_EQ(4, b[2]);
	ASSERT_EQ(6, b[3]);
	ASSERT_EQ(7, b[4]);
	ASSERT_EQ(b+5, it);
}

/**
 * Test: remove_copy_if
 */
TEST_F(algorithmTest, remove_copy_if) {
	int a[8] = {1,2,3,4,5,6,7,8};
	int b[4];

	std::function<bool (int)> pred = [](int i) {
		return i % 2 == 0; // is even
	};

	// copy all elements that are odd into other storage
	int * begin = a;
	int * end = a+8;
	int * it = prism::remove_copy_if(begin, end, b, pred);

	ASSERT_EQ(1, b[0]);
	ASSERT_EQ(3, b[1]);
	ASSERT_EQ(5, b[2]);
	ASSERT_EQ(7, b[3]);
	ASSERT_EQ(b+4, it);
}

/**
 * Test: remove_if
 */
TEST_F(algorithmTest, remove_if) {
	int a[8] = {1,2,3,4,5,6,7,8};

	std::function<bool(int)> pred = [](int i) {
		return i % 2 == 0;
	};

	// remove all even values
	int * begin = a;
	int * end = a+8;
	int * it = prism::remove_if(begin, end, pred);

	ASSERT_EQ(1, a[0]);
	ASSERT_EQ(3, a[1]);
	ASSERT_EQ(5, a[2]);
	ASSERT_EQ(7, a[3]);
	ASSERT_EQ(a+4, it);
}

/**
 * Test: replace
 */
TEST_F(algorithmTest, replace) {
	std::string str = "I _ee _ea _hell_";

	// replace all underscores with lower case s
	auto begin = str.begin();
	auto end = str.end();
	prism::replace(begin, end, '_', 's');

	ASSERT_EQ('I', str[0]);
	ASSERT_EQ(' ', str[1]);
	ASSERT_EQ('s', str[2]);
	ASSERT_EQ('e', str[3]);
	ASSERT_EQ('e', str[4]);
	ASSERT_EQ(' ', str[5]);
	ASSERT_EQ('s', str[6]);
	ASSERT_EQ('e', str[7]);
	ASSERT_EQ('a', str[8]);
	ASSERT_EQ(' ', str[9]);
	ASSERT_EQ('s', str[10]);
	ASSERT_EQ('h', str[11]);
	ASSERT_EQ('e', str[12]);
	ASSERT_EQ('l', str[13]);
	ASSERT_EQ('l', str[14]);
	ASSERT_EQ('s', str[15]);
}

/**
 * Test: replace_copy
 */
TEST_F(algorithmTest, replace_copy) {
	int a[8] = {1,2,1,3,1,4,1,5};
	int b[8];

	// replace-copy all 1's with 10
	int * begin = a;
	int * end = a+8;
	int oldValue = 1;
	int newValue = 10;
	int * it = prism::replace_copy(begin, end, b, oldValue, newValue);

	ASSERT_EQ(10, b[0]);
	ASSERT_EQ(2, b[1]);
	ASSERT_EQ(10, b[2]);
	ASSERT_EQ(3, b[3]);
	ASSERT_EQ(10, b[4]);
	ASSERT_EQ(4, b[5]);
	ASSERT_EQ(10, b[6]);
	ASSERT_EQ(5, b[7]);
	ASSERT_EQ(b+8, it);
}

/**
 * Test: replace_copy_if
 */
TEST_F(algorithmTest, replace_copy_if) {
	int a[10] = { 110, 140, 60, 430, 70, 330, 870, 90, 760, 0 };
	int b[10];

	std::function<bool(int)> pred = [](int i) {
		return i > 100;
	};

	// replace-copy everything greater than 100 with 100
	int * begin = a;
	int * end = a+10;
	int newValue = 100;
	int * it = prism::replace_copy_if(begin, end, b, pred, newValue);

	ASSERT_EQ(100, b[0]);
	ASSERT_EQ(100, b[1]);
	ASSERT_EQ(60, b[2]);
	ASSERT_EQ(100, b[3]);
	ASSERT_EQ(70, b[4]);
	ASSERT_EQ(100, b[5]);
	ASSERT_EQ(100, b[6]);
	ASSERT_EQ(90, b[7]);
	ASSERT_EQ(100, b[8]);
	ASSERT_EQ(0, b[9]);
	ASSERT_EQ(b+10, it);
}

/**
 * Test: replace_if
 */
TEST_F(algorithmTest, replace_if) {
	int a[10] = { 110, 140, 60, 430, 70, 330, 870, 90, 760, 0 };

	std::function<bool(int)> pred = [](int i) {
		return i > 100;
	};

	// replace any element greater than 100 with 100
	int * begin = a;
	int * end = a+10;
	int newValue = 100;
	prism::replace_if(begin, end, pred, newValue);

	ASSERT_EQ(100, a[0]);
	ASSERT_EQ(100, a[1]);
	ASSERT_EQ(60, a[2]);
	ASSERT_EQ(100, a[3]);
	ASSERT_EQ(70, a[4]);
	ASSERT_EQ(100, a[5]);
	ASSERT_EQ(100, a[6]);
	ASSERT_EQ(90, a[7]);
	ASSERT_EQ(100, a[8]);
	ASSERT_EQ(0, a[9]);
}

/**
 * Test: search
 */
TEST_F(algorithmTest, search) {
	std::string str = "I see sea shells";
	std::string substr = "sea shells";
	std::string substr2 = "invalid";

	// search for substring "sea shells"
	char * begin = &str[0];
	char * end = begin + str.size();
	char * otherBegin = &substr[0];
	char * otherEnd = otherBegin + substr.size();
	char * it = prism::search(begin, end, otherBegin, otherEnd);

	ASSERT_EQ(&str[6], it);
	ASSERT_EQ('s', *it);

	// search for substring that doesn't exist
	begin = &str[0];
	end = begin + str.size();
	otherBegin = &substr2[0];
	otherEnd = otherBegin + substr2.size();
	it = prism::search(begin, end, otherBegin, otherEnd);

	ASSERT_EQ(end, it);
}

/**
 * Test: sort
 */
TEST_F(algorithmTest, sort) {
	char a[5] = {'d','a','e','b','c'};

	char * begin = a;
	char * end = a+5;
	prism::sort(begin, end);

	ASSERT_EQ('a', a[0]);
	ASSERT_EQ('b', a[1]);
	ASSERT_EQ('c', a[2]);
	ASSERT_EQ('d', a[3]);
	ASSERT_EQ('e', a[4]);
}

/**
 * Test: swap(val1, val2)
 */
TEST_F(algorithmTest, swap) {
	// swap values
	int a[5] = {1,2,3,4,5};
	swap(a[0], a[4]);

	ASSERT_TRUE(a[0] == 5);
	ASSERT_TRUE(a[4] == 1);

	// swap pointers
	bool * t = new bool(true);
	bool * f = new bool(false);
	ASSERT_TRUE(*t);
	ASSERT_FALSE(*f);

	prism::swap(t,f);
	ASSERT_TRUE(*f);
	ASSERT_FALSE(*t);

	delete t;
	delete f;
}

/**
 * Test: swapRanges
 */
TEST_F(algorithmTest, swapRanges) {
	int a[5] = {1,2,3,4,5};
	int b[5] = {6,7,8,9,10};

	int * begin = a;
	int * end = a+5;
	int * otherBegin = b;
	int * it = prism::swap_ranges(begin, end, otherBegin);

	ASSERT_EQ(6, a[0]);
	ASSERT_EQ(7, a[1]);
	ASSERT_EQ(8, a[2]);
	ASSERT_EQ(9, a[3]);
	ASSERT_EQ(10, a[4]);

	ASSERT_EQ(1, b[0]);
	ASSERT_EQ(2, b[1]);
	ASSERT_EQ(3, b[2]);
	ASSERT_EQ(4, b[3]);
	ASSERT_EQ(5, b[4]);

	ASSERT_EQ(b+5, it);
}

/**
 * Test: uninitialized_fill
 */
TEST_F(algorithmTest, uninitialized_fill) {
	// allocate memory for 5 ints
	int numElements = 5;
	int value = 50;
	int * ptr = static_cast<int*>(::operator new(numElements * sizeof(int)));
	prism::uninitialized_fill(ptr, ptr+numElements, value);

	ASSERT_EQ(50, *ptr);
	ASSERT_EQ(50, *(ptr+1));
	ASSERT_EQ(50, *(ptr+2));
	ASSERT_EQ(50, *(ptr+3));
	ASSERT_EQ(50, *(ptr+4));

	delete ptr;
}

/**
 * Test: uninitialized_fill_n
 */
TEST_F(algorithmTest, uninitialized_fill_n) {
	// allocate memory for 5 ints
	int numElements = 5;
	int value = 50;
	int * ptr = static_cast<int*>(::operator new(numElements * sizeof(int)));
	prism::uninitialized_fill_n(ptr, numElements, value);

	ASSERT_EQ(50, *ptr);
	ASSERT_EQ(50, *(ptr+1));
	ASSERT_EQ(50, *(ptr+2));
	ASSERT_EQ(50, *(ptr+3));
	ASSERT_EQ(50, *(ptr+4));

	delete ptr;
}

/**
 * Test: uninitialized_copy
 */
TEST_F(algorithmTest, uninitialized_copy) {

	int a[5] = {1,2,3,4,5};
	// allocate memory for 5 ints
	int numElements = 5;
	int * ptr = static_cast<int*>(::operator new(numElements * sizeof(int)));
	int * begin = a;
	int * end = a + numElements;
	int * it = prism::uninitialized_copy(begin, end, ptr);

	ASSERT_EQ(1, *ptr);
	ASSERT_EQ(2, *(ptr+1));
	ASSERT_EQ(3, *(ptr+2));
	ASSERT_EQ(4, *(ptr+3));
	ASSERT_EQ(5, *(ptr+4));
	ASSERT_EQ(ptr+5, it);

	delete ptr;
}

/**
 * Test: uninitialized_copy_n
 */
TEST_F(algorithmTest, uninitialized_copy_n) {
	int a[5] = {1,2,3,4,5};
	// allocate memory for 5 ints
	int numElements = 5;
	int * ptr = static_cast<int*>(::operator new(numElements * sizeof(int)));
	int * begin = a;
	int * it = prism::uninitialized_copy_n(begin, numElements, ptr);

	ASSERT_EQ(1, *ptr);
	ASSERT_EQ(2, *(ptr+1));
	ASSERT_EQ(3, *(ptr+2));
	ASSERT_EQ(4, *(ptr+3));
	ASSERT_EQ(5, *(ptr+4));
	ASSERT_EQ(ptr+5, it);

	delete ptr;
}

} // end namespace test
} // end namespace prism



