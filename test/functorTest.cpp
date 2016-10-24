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
namespace test {

class functorTest : public ::testing::Test {

};

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
 * Test: greater()
 */
TEST_F(functorTest, greater) {
	prism::greater<int> f;
	ASSERT_TRUE(f(5,4));
	ASSERT_FALSE(f(10,12));
}

/**
 * Test: less()
 */
TEST_F(functorTest, less) {
	prism::less<int> f;
	ASSERT_FALSE(f(5,4));
	ASSERT_TRUE(f(10,12));
}

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


} // end namespace test
} // end nsmaespace prism
