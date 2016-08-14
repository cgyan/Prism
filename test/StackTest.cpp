/*
 * StackTest.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <prism/Stack>

namespace prism {

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
 * Test: copy on write
 */
TEST_F(StackTest, copyOnWrite) {
	Stack<int> s1;
	s1 << 1 << 2 << 3 << 4 << 5;
	Stack<int> s2(s1);

	ASSERT_TRUE(s1.sp.data()->storage.start == s2.sp.data()->storage.start);
	ASSERT_EQ(s1.top(), 5);
	ASSERT_EQ(s2.top(), 5);
	ASSERT_EQ(s1.size(), 5);
	ASSERT_EQ(s2.size(), 5);

	s2.pop();

	ASSERT_FALSE(s1.sp.data()->storage.start == s2.sp.data()->storage.start);
//	ASSERT_EQ(s1.top(), 5);
//	ASSERT_EQ(s2.top(), 4);
	ASSERT_EQ(s1.size(), 5);
	ASSERT_EQ(4, s2.size());
}

}












