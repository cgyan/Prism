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
protected:
	Array<int,5> a;
	Array<int,5> b;
	Array<int,5> c;

	// a = [0,4]
	// b = [10,14]
	// c = [0,4]
	ArrayTest() {
		for (int i=0; i<5; i++) {
			a[i] = i;
			b[i] = i+10;
		}

		c = a;
	}

};

/**
 * Test: ctor()
 */
TEST_F(ArrayTest, ctor) {
	ASSERT_EQ(5, a.size());
}

/**
 * Test: ctor(value)
 */
TEST_F(ArrayTest, ctor_fill) {
	Array<int,5> array(123);

	ASSERT_EQ(5, array.size());
	ASSERT_EQ(123, array[0]);
	ASSERT_EQ(123, array[1]);
	ASSERT_EQ(123, array[2]);
	ASSERT_EQ(123, array[3]);
	ASSERT_EQ(123, array[4]);
}

/**
 * Test: ctor(init_list)
 */
TEST_F(ArrayTest, ctor_init_list) {
	Array<int,3> ilArray({1,2,3});

	ASSERT_EQ(3, ilArray.size());
	ASSERT_EQ(1, ilArray[0]);
	ASSERT_EQ(2, ilArray[1]);
	ASSERT_EQ(3, ilArray[2]);
}

/**
 * Test: copy_ctor
 */
TEST_F(ArrayTest, copy_ctor) {
	Array<int,5> copy(a);

	ASSERT_EQ(5, a.size());
	ASSERT_EQ(0, a[0]);
	ASSERT_EQ(1, a[1]);
	ASSERT_EQ(2, a[2]);
	ASSERT_EQ(3, a[3]);
	ASSERT_EQ(4, a[4]);

	ASSERT_EQ(5, copy.size());
	ASSERT_EQ(0, copy[0]);
	ASSERT_EQ(1, copy[1]);
	ASSERT_EQ(2, copy[2]);
	ASSERT_EQ(3, copy[3]);
	ASSERT_EQ(4, copy[4]);
}

/**
 * Test: move_ctor()
 */
TEST_F(ArrayTest, move_ctor) {
	Array<int,5> copy(std::move(a));

	ASSERT_EQ(0, copy[0]);
	ASSERT_EQ(1, copy[1]);
	ASSERT_EQ(2, copy[2]);
	ASSERT_EQ(3, copy[3]);
	ASSERT_EQ(4, copy[4]);
}

/**
 * Test: operator=()
 */
TEST_F(ArrayTest, opAssignment) {
	a = b;

	ASSERT_EQ(10, a[0]);
	ASSERT_EQ(11, a[1]);
	ASSERT_EQ(12, a[2]);
	ASSERT_EQ(13, a[3]);
	ASSERT_EQ(14, a[4]);
}

/**
 * Test: operator=(&&)
 */
TEST_F(ArrayTest, opAssignment_move) {
	a = std::move(b);

	ASSERT_EQ(10, a[0]);
	ASSERT_EQ(11, a[1]);
	ASSERT_EQ(12, a[2]);
	ASSERT_EQ(13, a[3]);
	ASSERT_EQ(14, a[4]);
}

/**
 * Test: at
 */
TEST_F(ArrayTest, at) {
	ASSERT_EQ(0, a.at(0));
	ASSERT_EQ(1, a.at(1));
	ASSERT_EQ(2, a.at(2));
	ASSERT_EQ(3, a.at(3));
	ASSERT_EQ(4, a.at(4));
}

/**
 * Test: at() const
 */
TEST_F(ArrayTest, at_const) {
	for (int i=0; i<5; i++) {
		Array<int,5>::const_reference ref = a[i];
		ASSERT_EQ(i, ref);
	}
}

/**
 * Test: back()
 */
TEST_F(ArrayTest, back) {
	Array<int,5>::reference ref = a.back();
	ASSERT_EQ(4, ref);
}

/**
 * Test: back() const
 */
TEST_F(ArrayTest, back_const) {
	Array<int,5>::const_reference ref = a.back();
	ASSERT_EQ(4, ref);
}

/**
 * Test: begin()
 */
TEST_F(ArrayTest, begin) {
	Array<int,5>::iterator it = a.begin();

	ASSERT_EQ(&a[0], it.p);
	ASSERT_EQ(0, *it);
}

/**
 * Test: begin() const
 */
TEST_F(ArrayTest, begin_const) {
	Array<int,5>::const_iterator it = a.begin();

	ASSERT_EQ(&a[0], it.p);
	ASSERT_EQ(0, *it);
}

/**
 * Test: cbegin()
 */
TEST_F(ArrayTest, cbegin) {
	Array<int,5>::const_iterator cit = a.constBegin();

	ASSERT_EQ(&a[0], cit.p);
	ASSERT_EQ(0, *cit);
}

/**
 * Test: constBegin
 */
TEST_F(ArrayTest, constBegin) {
	Array<int,5>::const_iterator cit = a.constBegin();

	ASSERT_EQ(&a[0], cit.p);
	ASSERT_EQ(0, *cit);
}

/**
 * Test: constData
 */
TEST_F(ArrayTest, constData) {
	Array<int,5>::const_pointer data = a.constData();

	ASSERT_EQ(0, data[0]);
	ASSERT_EQ(1, data[1]);
	ASSERT_EQ(2, data[2]);
	ASSERT_EQ(3, data[3]);
	ASSERT_EQ(4, data[4]);
}

/**
 * Test: cend()
 */
TEST_F(ArrayTest, cend) {
	Array<int,5>::const_iterator cit = a.constEnd();

	ASSERT_EQ(a.data()+5, cit.p);
}

/**
 * Test: constEnd
 */
TEST_F(ArrayTest, constEnd) {
	Array<int,5>::const_iterator cit = a.constEnd();

	ASSERT_EQ(a.data()+5, cit.p);
}

/**
 * Test: data()
 */
TEST_F(ArrayTest, data) {
	Array<int,5>::pointer p = a.data();

	ASSERT_EQ(&a[0], p);
}

/**
 * Test: data() const
 */
TEST_F(ArrayTest, data_const) {
	Array<int,5>::const_pointer p = a.data();

	ASSERT_EQ(&a[0], p);
}

/**
 * Test: empty()
 */
TEST_F(ArrayTest, empty) {
	Array<int,0> zeroArray;

	ASSERT_TRUE(zeroArray.empty());
	ASSERT_FALSE(a.empty());
}

/**
 * Test: end()
 */
TEST_F(ArrayTest, end) {
	Array<int,5>::iterator it = a.end();

	ASSERT_EQ(&a[0]+5, it.p);
}

/**
 * Test: end() const
 */
TEST_F(ArrayTest, end_const) {
	Array<int,5>::const_iterator it = a.end();

	ASSERT_EQ(&a[0]+5, it.p);
}

/**
 * Test: fill()
 */
TEST_F(ArrayTest, fill) {
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
	Array<int,5>::reference ref = a.first();

	ASSERT_EQ(0, ref);
	ASSERT_NE(1, ref);
	ASSERT_NE(2, ref);
	ASSERT_NE(3, ref);
	ASSERT_NE(4, ref);
}

/**
 * Test: first() const
 */
TEST_F(ArrayTest, first_const) {
	Array<int,5>::const_reference ref = a.first();

	ASSERT_EQ(0, ref);
	ASSERT_NE(1, ref);
	ASSERT_NE(2, ref);
	ASSERT_NE(3, ref);
	ASSERT_NE(4, ref);
}

/**
 * Test: last()
 */
TEST_F(ArrayTest, last) {
	Array<int,5>::reference ref = a.last();

	ASSERT_EQ(4, ref);
	ASSERT_NE(0, ref);
	ASSERT_NE(1, ref);
	ASSERT_NE(2, ref);
	ASSERT_NE(3, ref);
}

/**
 * Test: last() const
 */
TEST_F(ArrayTest, last_const) {
	Array<int,5>::const_reference ref = a.last();

	ASSERT_EQ(4, ref);
	ASSERT_NE(0, ref);
	ASSERT_NE(1, ref);
	ASSERT_NE(2, ref);
	ASSERT_NE(3, ref);
}

/**
 * Test: size()
 */
TEST_F(ArrayTest, size) {
	ASSERT_EQ(5, a.size());
}

/**
 * Test: swap(rhs)
 */
TEST_F(ArrayTest, swap) {
	a.swap(b);

	ASSERT_EQ(10, a[0]);
	ASSERT_EQ(11, a[1]);
	ASSERT_EQ(12, a[2]);
	ASSERT_EQ(13, a[3]);
	ASSERT_EQ(14, a[4]);

	ASSERT_EQ(0, b[0]);
	ASSERT_EQ(1, b[1]);
	ASSERT_EQ(2, b[2]);
	ASSERT_EQ(3, b[3]);
	ASSERT_EQ(4, b[4]);
}

/**
 * Test: swap(lhs,rhs)
 */
TEST_F(ArrayTest, swap_non_member) {
	using prism::swap;
	swap(a, b);

	ASSERT_EQ(10, a[0]);
	ASSERT_EQ(11, a[1]);
	ASSERT_EQ(12, a[2]);
	ASSERT_EQ(13, a[3]);
	ASSERT_EQ(14, a[4]);

	ASSERT_EQ(0, b[0]);
	ASSERT_EQ(1, b[1]);
	ASSERT_EQ(2, b[2]);
	ASSERT_EQ(3, b[3]);
	ASSERT_EQ(4, b[4]);
}

/**
 * Test: operator[]
 */
TEST_F(ArrayTest, operatorBrackets) {
	ASSERT_EQ(0, a[0]);
	ASSERT_EQ(1, a[1]);
	ASSERT_EQ(2, a[2]);
	ASSERT_EQ(3, a[3]);
	ASSERT_EQ(4, a[4]);
}

/**
 * Test: operator[] const
 */
TEST_F(ArrayTest, operatorBrackets_const) {
	for (int i = 0; i<5; i++) {
		Array<int,5>::const_reference ref = a[i];
		ASSERT_EQ(i, ref);
	}
}

/**
 * Test: operator==()
 */
TEST_F(ArrayTest, operatorEquality) {
	ASSERT_TRUE(a == c);
	ASSERT_TRUE(c == a);
	ASSERT_FALSE(a == b);
}

/**
 * Test: operator!=()
 */
TEST_F(ArrayTest, operatorInequality) {
	ASSERT_FALSE(a != c);
	ASSERT_FALSE(c != a);
	ASSERT_TRUE(a != b);
}

} // end namespace test
} // end namespace rpism












