/*
 * predicateTest.cpp
 * v1
 *
 *  Created on: Sep 30, 2016
 *      Author: iainhemstock
 */

#include <gtest/gtest.h>
#include <prism/functor>

namespace prism {

class functorTest : public ::testing::Test {

};

/**
 * Test: odd
 */
TEST_F(functorTest, odd) {
	prism::odd<int> f;
	ASSERT_TRUE(f(1));
	ASSERT_TRUE(f(3));
	ASSERT_TRUE(f(5));
	ASSERT_TRUE(f(7));
	ASSERT_TRUE(f(100000001));
	ASSERT_FALSE(f(2));
	ASSERT_FALSE(f(4));
	ASSERT_FALSE(f(6));
	ASSERT_FALSE(f(8));
	ASSERT_FALSE(f(100000002));
}

/**
 * Test: even
 */
TEST_F(functorTest, even) {
	prism::even<int> f;
	ASSERT_FALSE(f(1));
	ASSERT_FALSE(f(3));
	ASSERT_FALSE(f(5));
	ASSERT_FALSE(f(7));
	ASSERT_FALSE(f(100000001));
	ASSERT_TRUE(f(2));
	ASSERT_TRUE(f(4));
	ASSERT_TRUE(f(6));
	ASSERT_TRUE(f(8));
	ASSERT_TRUE(f(100000002));
}

/**
 * Test: positive
 */
TEST_F(functorTest, positive) {
	prism::positive<int> f;
	ASSERT_TRUE(f(1));
	ASSERT_TRUE(f(3));
	ASSERT_TRUE(f(5));
	ASSERT_TRUE(f(7));
	ASSERT_TRUE(f(100000001));
	ASSERT_FALSE(f(-2));
	ASSERT_FALSE(f(-4));
	ASSERT_FALSE(f(-6));
	ASSERT_FALSE(f(-8));
	ASSERT_FALSE(f(-100000002));
}

/**
 * Test: negative
 */
TEST_F(functorTest, negative) {
	prism::negative<int> f;
	ASSERT_FALSE(f(1));
	ASSERT_FALSE(f(3));
	ASSERT_FALSE(f(5));
	ASSERT_FALSE(f(7));
	ASSERT_FALSE(f(100000001));
	ASSERT_TRUE(f(-2));
	ASSERT_TRUE(f(-4));
	ASSERT_TRUE(f(-6));
	ASSERT_TRUE(f(-8));
	ASSERT_TRUE(f(-100000002));
}

} // end nsmaespace prism
