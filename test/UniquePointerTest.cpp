/*
 * UniquePointerTest.cpp
 * v1
 *
 *  Created on: Nov 8, 2016
 *      Author: iainhemstock
 */

#include <gtest/gtest.h>
#include <prism/UniquePointer>

namespace prism {
namespace test {

class UniquePointerTest : public ::testing::Test {
public:
	struct D {};
	UniquePointer<int*,D> up;
};

/**
 * Test: UniquePointer()
 */
TEST_F(UniquePointerTest, UniquePointer) {
	ASSERT_TRUE(false);
}

/**
 * Test: get()
 */
TEST_F(UniquePointerTest, get) {
	ASSERT_TRUE(up.get() == nullptr);
}

} // end namespace test
} // end namespace prism
















