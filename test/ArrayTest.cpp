/*
 * ArrayTest.cpp
 * v1
 *
 *  Created on: Oct 24, 2016
 *      Author: iainhemstock
 */

#include <gtest/gtest.h>
#include <prism/Array>

namespace prism {
namespace test {

class ArrayTest : public::testing::Test {

};

/**
 * Test: ctor(size)
 */
TEST_F(ArrayTest, ctor_size) {
	Array<int> a(5);

	ASSERT_EQ(5, a.size());
	ASSERT_EQ(5, a.length());
	ASSERT_EQ(0, a[0]);
	ASSERT_EQ(0, a[1]);
	ASSERT_EQ(0, a[2]);
	ASSERT_EQ(0, a[3]);
	ASSERT_EQ(0, a[4]);
}

/**
 * Test: ctor_size_value
 */
TEST_F(ArrayTest, ctor_size_value) {
	Array<int> a(5, 123);

	ASSERT_EQ(5, a.size());
	ASSERT_EQ(123, a[0]);
	ASSERT_EQ(123, a[1]);
	ASSERT_EQ(123, a[2]);
	ASSERT_EQ(123, a[3]);
	ASSERT_EQ(123, a[4]);
}

/**
 * Test: ctor_init_list
 */
TEST_F(ArrayTest, ctor_init_list) {
	Array<int> a({1,2,3,4,5});

	ASSERT_EQ(5, a.size());
	ASSERT_EQ(1, a[0]);
	ASSERT_EQ(2, a[1]);
	ASSERT_EQ(3, a[2]);
	ASSERT_EQ(4, a[3]);
	ASSERT_EQ(5, a[4]);
}

/**
 * Test: copy_ctor
 */
TEST_F(ArrayTest, copy_ctor) {
	Array<int> a = {1,2,3,4,5};
	Array<int> b(a);

	ASSERT_EQ(5, a.size());
	ASSERT_EQ(1, a[0]);
	ASSERT_EQ(2, a[1]);
	ASSERT_EQ(3, a[2]);
	ASSERT_EQ(4, a[3]);
	ASSERT_EQ(5, a[4]);

	ASSERT_EQ(5, b.size());
	ASSERT_EQ(1, b[0]);
	ASSERT_EQ(2, b[1]);
	ASSERT_EQ(3, b[2]);
	ASSERT_EQ(4, b[3]);
	ASSERT_EQ(5, b[4]);
}

/**
 * Test: at
 */
TEST_F(ArrayTest, at) {
	Array<int> a = {1,2,3,4,5};

	ASSERT_EQ(1, a.at(0));
	ASSERT_EQ(2, a.at(1));
	ASSERT_EQ(3, a.at(2));
	ASSERT_EQ(4, a.at(3));
	ASSERT_EQ(5, a.at(4));
}

/**
 * Test: back()
 */
TEST_F(ArrayTest, back) {
	Array<int> a = {1,2,3,4,5};
	ASSERT_EQ(5, a.back());
}

/**
 * Test: back() const
 */
TEST_F(ArrayTest, back_const) {
	const Array<int> a = {1,2,3,4,5};
	Array<int>::const_reference ref = a.back();
	ASSERT_EQ(5, ref);
}

/**
 * Test: begin()
 */
TEST_F(ArrayTest, begin_non_const) {
	Array<int> a = {1,2,3,4,5};
	Array<int>::iterator it = a.begin();

	ASSERT_EQ(&a[0], it.p);
	ASSERT_EQ(1, *it);
}

/**
 * Test: begin() const
 */
TEST_F(ArrayTest, begin_const) {
	const Array<int> a = {1,2,3,4,5};
	Array<int>::const_iterator it = a.begin();

	ASSERT_EQ(&a[0], it.p);
	ASSERT_EQ(1, *it);
}

/**
 * Test: constBegin
 */
TEST_F(ArrayTest, constBegin) {
	Array<int> a = {1,2,3,4,5};
	Array<int>::const_iterator cit = a.constBegin();

	ASSERT_EQ(&a[0], cit.p);
	ASSERT_EQ(1, *cit);
}

/**
 * Test: constData
 */
TEST_F(ArrayTest, constData) {
	Array<int> a = {1,2,3,4,5};
	Array<int>::const_pointer data = a.constData();

	ASSERT_EQ(1, data[0]);
	ASSERT_EQ(2, data[1]);
	ASSERT_EQ(3, data[2]);
	ASSERT_EQ(4, data[3]);
	ASSERT_EQ(5, data[4]);
}

/**
 * Test: constEnd
 */
TEST_F(ArrayTest, constEnd) {
	Array<int> a = {1,2,3,4,5};
	Array<int>::const_iterator cit = a.constEnd();

	ASSERT_EQ(a.data()+5, cit.p);
}

/**
 * Test: contains
 */
TEST_F(ArrayTest, contains) {
	Array<int> a = {1,2,3,4,5};

	bool contains = a.contains(5);
	ASSERT_TRUE(contains);

	contains = a.contains(45);
	ASSERT_FALSE(contains);
}

/**
 * Test: count
 */
TEST_F(ArrayTest, count) {
	Array<char> a = {'a','b','c','a','d','a','e','a'};

	// count the number of a's
	int count = a.count('a');
	ASSERT_EQ(4, count);

	// non-existent value
	count = a.count('z');
	ASSERT_EQ(0, count);
}

/**
 * Test: data()
 */
TEST_F(ArrayTest, data_non_const) {
	Array<int> a = {1,2,3,4,5};
	Array<int>::pointer p = a.data();

	ASSERT_EQ(&a[0], p);
}

/**
 * Test: data() const
 */
TEST_F(ArrayTest, data_const) {
	const Array<int> a = {1,2,3,4,5};
	Array<int>::const_pointer p = a.data();

	ASSERT_EQ(&a[0], p);
}

/**
 * Test: end()
 */
TEST_F(ArrayTest, end) {
	Array<int> a = {1,2,3,4,5};
	Array<int>::iterator it = a.end();

	ASSERT_EQ(&a[0]+5, it.p);
}

/**
 * Test: end() const
 */
TEST_F(ArrayTest, end_const) {
	const Array<int> a = {1,2,3,4,5};
	Array<int>::const_iterator it = a.end();

	ASSERT_EQ(&a[0]+5, it.p);
}

/**
 * Test: endsWith()
 */
TEST_F(ArrayTest, endsWith) {
	Array<int> a = {1,49,65,87,34};

	ASSERT_TRUE(a.endsWith(34));
	ASSERT_FALSE(a.endsWith(1));
	ASSERT_FALSE(a.endsWith(49));
	ASSERT_FALSE(a.endsWith(65));
	ASSERT_FALSE(a.endsWith(87));
}

/**
 * Test: fill()
 */
TEST_F(ArrayTest, fill) {
	Array<int> a(5);
	a.fill(10);

	ASSERT_EQ(10, a[0]);
	ASSERT_EQ(10, a[1]);
	ASSERT_EQ(10, a[2]);
	ASSERT_EQ(10, a[3]);
	ASSERT_EQ(10, a[4]);
}

/**
 * Test: first()
 */
TEST_F(ArrayTest, first) {
	Array<int> a = {1,2,3,4,5};

	ASSERT_EQ(1, a.first());
	ASSERT_NE(2, a.first());
	ASSERT_NE(3, a.first());
	ASSERT_NE(4, a.first());
	ASSERT_NE(5, a.first());
}

/**
 * Test: first() const
 */
TEST_F(ArrayTest, first_const) {
	const Array<int> a = {1,2,3,4,5};

	ASSERT_EQ(1, a.first());
	ASSERT_NE(2, a.first());
	ASSERT_NE(3, a.first());
	ASSERT_NE(4, a.first());
	ASSERT_NE(5, a.first());
}

/**
 * Test: indexOf()
 */
TEST_F(ArrayTest, indexOf) {
	Array<int> a = {1,2,3,4,5,1};

	// find the first index of 4
	int index = a.indexOf(4);
	ASSERT_EQ(3, index);
	ASSERT_NE(0, index);
	ASSERT_NE(1, index);
	ASSERT_NE(2, index);
	ASSERT_NE(4, index);
	ASSERT_NE(5, index);

	// find first index of 1 in subrange
	index = a.indexOf(1, 1);
	ASSERT_EQ(5, index);
	ASSERT_NE(0, index);
	ASSERT_NE(1, index);
	ASSERT_NE(2, index);
	ASSERT_NE(3, index);
	ASSERT_NE(4, index);

	// non-existent value
	index = a.indexOf(123);
	ASSERT_EQ(-1, index);
	ASSERT_NE(0, index);
	ASSERT_NE(1, index);
	ASSERT_NE(2, index);
	ASSERT_NE(3, index);
	ASSERT_NE(4, index);
}

/**
 * Test: last()
 */
TEST_F(ArrayTest, last) {
	Array<int> a = { 1,2,3,4,5 };

	ASSERT_EQ(5, a.last());
	ASSERT_NE(1, a.last());
	ASSERT_NE(2, a.last());
	ASSERT_NE(3, a.last());
	ASSERT_NE(4, a.last());
}

/**
 * Test: last() const
 */
TEST_F(ArrayTest, last_const) {
	const Array<int> a = { 1,2,3,4,5 };

	ASSERT_EQ(5, a.last());
	ASSERT_NE(1, a.last());
	ASSERT_NE(2, a.last());
	ASSERT_NE(3, a.last());
	ASSERT_NE(4, a.last());
}

/**
 * Test: lastIndexOf
 */
TEST_F(ArrayTest, lastIndexOf) {
	Array<int> a = {1,2,3,4,5,1};
	int valueToFind = 1;

	// search whole range
	int index = a.lastIndexOf(valueToFind);
	ASSERT_EQ(5, index);
	ASSERT_NE(0, index);
	ASSERT_NE(1, index);
	ASSERT_NE(2, index);
	ASSERT_NE(3, index);
	ASSERT_NE(4, index);

	// search subrange
	int indexToSearchFrom = 4;
	index = a.lastIndexOf(valueToFind, indexToSearchFrom);
	ASSERT_EQ(0, index);
	ASSERT_NE(1, index);
	ASSERT_NE(2, index);
	ASSERT_NE(3, index);
	ASSERT_NE(4, index);
	ASSERT_NE(5, index);

	// non-existent value
	valueToFind = 123;
	index = a.lastIndexOf(valueToFind);
	ASSERT_EQ(-1, index);
	ASSERT_NE(0, index);
	ASSERT_NE(1, index);
	ASSERT_NE(2, index);
	ASSERT_NE(3, index);
	ASSERT_NE(4, index);
	ASSERT_NE(5, index);
}

/**
 * Test: length()
 */
TEST_F(ArrayTest, length) {
	Array<int> a = {1,2,3,4,5};
	ASSERT_EQ(5, a.length());
}

/**
 * Test: mid()
 */
TEST_F(ArrayTest, mid) {
	Array<int> a = { 1, 2, 3, 10, 11, 12, 4, 5, 6 };

	// take subrange of index 3 to the end
	int startIndex = 3;
	Array<int> mid = a.mid(startIndex);

	ASSERT_EQ(6, mid.size());
	ASSERT_EQ(10, mid[0]);
	ASSERT_EQ(11, mid[1]);
	ASSERT_EQ(12, mid[2]);
	ASSERT_EQ(4, mid[3]);
	ASSERT_EQ(5, mid[4]);
	ASSERT_EQ(6, mid[5]);

	// take subrange of index 3 for 3 elements
	int numElements = 3;
	Array<int> mid2 = a.mid(startIndex, numElements);

	ASSERT_EQ(3, mid2.size());
	ASSERT_EQ(10, mid2[0]);
	ASSERT_EQ(11, mid2[1]);
	ASSERT_EQ(12, mid2[2]);
}

/**
 * Test: replace()
 */
TEST_F(ArrayTest, replace) {
	Array<int> a = {1,2,3,3,5};

	// replcae index 3 with a value of 4
	int indexToReplace = 3;
	int replacementValue = 4;
	a.replace(indexToReplace, replacementValue);

	ASSERT_EQ(1, a[0]);
	ASSERT_EQ(2, a[1]);
	ASSERT_EQ(3, a[2]);
	ASSERT_EQ(4, a[3]);
	ASSERT_EQ(5, a[4]);
}

/**
 * Test: size()
 */
TEST_F(ArrayTest, size) {
	Array<float> a = {1.1, 1.2, 1.3, 1.4, 1.5};
	ASSERT_EQ(5, a.size());
}

/**
 * Test: startsWith()
 */
TEST_F(ArrayTest, startsWith) {
	Array<float> a = {1.1, 1.2, 1.3, 1.4, 1.5};

	// does it start with 1.4?
	float value = 1.4;
	bool startsWith = a.startsWith(value);
	ASSERT_FALSE(startsWith);

	// does it start with 1.1?
	value = 1.1;
	startsWith = a.startsWith(value);
	ASSERT_TRUE(startsWith);
}

/**
 * Test: value
 */
TEST_F(ArrayTest, value) {
	Array<float> a = {1.1, 1.2, 1.3, 1.4, 1.5};

	ASSERT_FLOAT_EQ(1.1, a.value(0));
	ASSERT_FLOAT_EQ(1.2, a.value(1));
	ASSERT_FLOAT_EQ(1.3, a.value(2));
	ASSERT_FLOAT_EQ(1.4, a.value(3));
	ASSERT_FLOAT_EQ(1.5, a.value(4));
}

/**
 * Test: operator[]
 */
TEST_F(ArrayTest, operatorBrackets) {
	Array<float> a = {1.1, 1.2, 1.3, 1.4, 1.5};

	ASSERT_FLOAT_EQ(1.1, a[0]);
	ASSERT_FLOAT_EQ(1.2, a[1]);
	ASSERT_FLOAT_EQ(1.3, a[2]);
	ASSERT_FLOAT_EQ(1.4, a[3]);
	ASSERT_FLOAT_EQ(1.5, a[4]);
}

/**
 * Test: operator[] const
 */
TEST_F(ArrayTest, operatorBrackets_const) {
	const Array<float> a = {1.1, 1.2, 1.3, 1.4, 1.5};

	ASSERT_FLOAT_EQ(1.1, a[0]);
	ASSERT_FLOAT_EQ(1.2, a[1]);
	ASSERT_FLOAT_EQ(1.3, a[2]);
	ASSERT_FLOAT_EQ(1.4, a[3]);
	ASSERT_FLOAT_EQ(1.5, a[4]);
}

/**
 * Test: operator==()
 */
TEST_F(ArrayTest, operatorEquals) {
	Array<float> a = {1.1, 1.2, 1.3, 1.4, 1.5};
	Array<float> b(a);
	Array<float> c(5);

	ASSERT_TRUE(a == b);
	ASSERT_TRUE(b == a);
	ASSERT_FALSE(a == c);
}

/**
 * Test: operator!=()
 */
TEST_F(ArrayTest, operatorNotEquals) {
	Array<float> a = {1.1, 1.2, 1.3, 1.4, 1.5};
	Array<float> b(a);
	Array<float> c(5);

	ASSERT_FALSE(a != b);
	ASSERT_FALSE(b != a);
	ASSERT_TRUE(a != c);
}

} // end namespace test
} // end namespace rpism












