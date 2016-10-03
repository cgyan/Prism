/*
 * PairTest.cpp
 * v1
 *
 *  Created on: Aug 20, 2016
 *      Author: iainhemstock
 */
#include <gtest/gtest.h>
#include <prism/Pair>
#include <prism/String>

namespace prism {

class pairTest : public ::testing::Test {

};

/**
 * Test: Pair()
 * first and second should be default initialized i.e. T1() and T2()
 */
TEST_F(pairTest, defaultConstructor) {
	pair<int, String> p;
	ASSERT_TRUE(p.first == 0);
	ASSERT_TRUE(p.second == String(""));

}

/**
 * Test: Pair(val1, val2)
 */
TEST_F(pairTest, constructorWithValues) {
	pair<int, String> p(42, "Twenty pounds");
	ASSERT_TRUE(p.first == 42);
	ASSERT_TRUE(p.second == String("Twenty pounds"));

}

/**
 * Test: operator==()
 */
TEST_F(pairTest, opComparison) {
	pair<int, String> p(42, "Twenty pounds");
	pair<int, String> p2;
	p2.first = 42;
	p2.second = "Twenty pounds";
	pair<int,String> p3(25, "Hourly rate");

	ASSERT_TRUE(p == p2);
	ASSERT_FALSE(p == p3);
}

/**
 * Test: operator!=()
 */
TEST_F(pairTest, opNotEquals) {
	pair<int, String> p(42, "Twenty pounds");
	pair<int, String> p2;
	p2.first = 42;
	p2.second = "Twenty pounds";
	pair<int,String> p3(25, "Hourly rate");

	ASSERT_FALSE(p != p2);
	ASSERT_TRUE(p != p3);
}

}



