/*
 * DequeTest.cpp
 * v1
 *
 *  Created on: Aug 20, 2016
 *      Author: iainhemstock
 */
#include <gtest/gtest.h>
#include <prism/Deque>
#include <ostream>
using namespace std;

namespace prism {

class DequeTest : public ::testing::Test {

};

/**
 * Test: Deque<T>()
 */
TEST_F(DequeTest, ctor) {
	Deque<int> d;
}

}








