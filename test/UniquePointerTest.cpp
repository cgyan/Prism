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

};

/**
 * Test: UniquePointer()
 */
TEST_F(UniquePointerTest, UniquePointer) {
	struct Deleter{};
	UniquePointer<int*,Deleter> up;

	ASSERT_TRUE(false);
}

} // end namespace test
} // end namespace prism

