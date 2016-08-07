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
	s << 1 << 2 << 3 << 4 << 5;

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
	s << 1 << 2 << 3 << 4 << 5;

	ASSERT_TRUE(s.top() == 5);
}

/**
 * Test: operator==()
 */

/**
 * Test: operator!=()
 */

/**
 * Test: operator+=()
 */

/**
 * Test: operator<<()
 */

}












