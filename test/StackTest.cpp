/*
 * StackTest.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/Stack>
#include <prism/Vector>
#include <prism/List>

namespace prism {
namespace test {

class StackTest : public ::testing::Test {

};

/**
 * Test: constructor
 */
TEST_F(StackTest, constructor) {
	Stack<int> s;
	ASSERT_TRUE(s.size() == 0);
}

/**
 * Test: empty()
 */
TEST_F(StackTest, empty) {
	Stack<int> s;
	ASSERT_EQ(s.empty(), true);

	s.push(10);
	ASSERT_NE(s.empty(), true);
}

/**
 * Test: pop()
 */
TEST_F(StackTest, pop) {
	Stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);

	s.pop();
	ASSERT_TRUE(s.size() == 4);
	ASSERT_EQ(s.top(), 4);
}

/**
 * Test: push(value)
 */
TEST_F(StackTest, push) {
	Stack<int> s;
	s.push(1);

	ASSERT_EQ(s.size(), 1);
	ASSERT_TRUE(s.top() == 1);
}

/**
 * Test: size()
 */
TEST_F(StackTest, size) {
	Stack<int> s;
	ASSERT_EQ(s.size(), 0);

	s.push(123);
	ASSERT_TRUE(s.size() == 1);

	s.pop();
	ASSERT_TRUE(s.size() == 0);
}

/**
 * Test: squeeze()
 */
TEST_F(StackTest, squeeze) {
	Stack<int> s;
	s << 1 << 3 << 5 << 7 << 9;

	ASSERT_GT(s.capacity(), s.size());

	s.squeeze();

	ASSERT_EQ(s.capacity(), s.size());
	ASSERT_EQ(5, s.size());
	ASSERT_EQ(9, s.top());
}

/**
 * Test: top()
 */
TEST_F(StackTest, top) {
	Stack<int> s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);

	ASSERT_TRUE(s.top() == 5);
}

/**
 * Test: toVector()
 */
TEST_F(StackTest, toVector) {
	Stack<int> s;
	s << 1 << 3 << 5 << 7 << 9;
	Vector<int> v = s.toVector();

	ASSERT_EQ(5, v.size());
	ASSERT_EQ(1, v.at(0));
	ASSERT_EQ(3, v.at(1));
	ASSERT_EQ(5, v.at(2));
	ASSERT_EQ(7, v.at(3));
	ASSERT_EQ(9, v.at(4));
}

/**
 * Test: toList()
 */
TEST_F(StackTest, toList) {
	Stack<int> s;
	s << 10 << 20 << 30 << 40 << 50;
	List<int> l = s.toList();

	ASSERT_EQ(5, l.size());

	List<int>::const_iterator it = l.constBegin();
	for (int i=0; i<l.size(); i++)
		ASSERT_EQ(i*10+10, *it++);
}

/**
 * Test: operator==()
 */
TEST_F(StackTest, opEqualsEquals) {
	Stack<int> s1;
	Stack<int> s2;
	Stack<int> s3;

	for (int i=0; i<5; i++) {
		s1.push(i);
		s2.push(i);
	}

	ASSERT_TRUE(s1 == s2);
	ASSERT_FALSE(s1 == s3);
}

/**
 * Test: operator!=()
 */
TEST_F(StackTest, opNotEquals) {
	Stack<int> s1;
	Stack<int> s2;
	Stack<int> s3;

	for (int i=0; i<5; i++) {
		s1.push(i);
		s2.push(i);
	}

	ASSERT_TRUE(s1 != s3);
	ASSERT_FALSE(s1 != s2);
}

/**
 * Test: operator+=(value)
 */
TEST_F(StackTest, opPlusEquals) {
	Stack<int> s;
	s += 1;

	ASSERT_EQ(s.size(), 1);
	ASSERT_TRUE(s.top() == 1);
}

/**
 * Test: operator<<(value)
 */
TEST_F(StackTest, opStreamIn) {
	Stack<int> s;
	s << 1 << 2 << 3;

	ASSERT_EQ(s.size(), 3);
	ASSERT_TRUE(s.top() == 3);
}

/**
 * Test: copy on write (pop)
 */
TEST_F(StackTest, copyOnWritePop) {
	Stack<int> s1;
	s1 << 1 << 2 << 3 << 4 << 5;
	Stack<int> s2=s1;

//	ASSERT_TRUE(s1.d.data()->storage.start == s2.d.data()->storage.start);
	ASSERT_EQ(s1.top(), 5);
	ASSERT_EQ(s2.top(), 5);
	ASSERT_EQ(s1.size(), 5);
	ASSERT_EQ(s2.size(), 5);

	s2.pop();

//	ASSERT_FALSE(s1.d.data()->storage.start == s2.d.data()->storage.start);
	ASSERT_EQ(s1.top(), 5);
	ASSERT_EQ(s2.top(), 4);
	ASSERT_EQ(s1.size(), 5);
	ASSERT_EQ(4, s2.size());
}

/**
 * Test: copy on write (push)
 */
TEST_F(StackTest, copyOnWritePush) {
	Stack<int> s1;
	s1 << 1 << 2 << 3 << 4 << 5;
	Stack<int> s2=s1;

//	ASSERT_TRUE(s1.d.data()->storage.start == s2.d.data()->storage.start);
	ASSERT_EQ(5, s1.top());
	ASSERT_EQ(5, s2.top());
	ASSERT_EQ(5, s1.size());
	ASSERT_EQ(5, s2.size());

	s2.push(6);

//	ASSERT_FALSE(s1.d.data()->storage.start == s2.d.data()->storage.start);
	ASSERT_EQ(5, s1.top());
	ASSERT_EQ(6, s2.top());
	ASSERT_EQ(5, s1.size());
	ASSERT_EQ(6, s2.size());
}

/**
 * Test: copy on write (operator+=)
 */
TEST_F(StackTest, copyOnWriteOpPlusEquals) {
	Stack<int> s1;
	s1 << 1 << 2 << 3 << 4 << 5;
	Stack<int> s2=s1;

//	ASSERT_TRUE(s1.d.data()->storage.start == s2.d.data()->storage.start);
	ASSERT_EQ(5, s1.top());
	ASSERT_EQ(5, s2.top());
	ASSERT_EQ(5, s1.size());
	ASSERT_EQ(5, s2.size());

	s2 += 10;

//	ASSERT_FALSE(s1.d.data()->storage.start == s2.d.data()->storage.start);
	ASSERT_EQ(5, s1.top());
	ASSERT_EQ(10, s2.top());
	ASSERT_EQ(5, s1.size());
	ASSERT_EQ(6, s2.size());
}

/**
 * Test: copy on write (operator<<)
 */
TEST_F(StackTest, copyOnWriteOpInsertion) {
	Stack<int> s1;
	s1 << 1 << 2 << 3 << 4 << 5;
	Stack<int> s2=s1;

//	ASSERT_TRUE(s1.d.data()->storage.start == s2.d.data()->storage.start);
	ASSERT_EQ(5, s1.top());
	ASSERT_EQ(5, s2.top());
	ASSERT_EQ(5, s1.size());
	ASSERT_EQ(5, s2.size());

	s2 << 10;

//	ASSERT_FALSE(s1.d.data()->storage.start == s2.d.data()->storage.start);
	ASSERT_EQ(5, s1.top());
	ASSERT_EQ(10, s2.top());
	ASSERT_EQ(5, s1.size());
	ASSERT_EQ(6, s2.size());
}

} // end namespace test
} // end namespace prism












