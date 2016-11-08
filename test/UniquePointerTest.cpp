/*
 * UniquePointerTest.cpp
 * v1
 *
 *  Created on: Nov 8, 2016
 *      Author: iainhemstock
 */

#include <gtest/gtest.h>
#include <prism/UniquePointer>
#include <string>

namespace prism {
namespace test {

class UniquePointerTest : public ::testing::Test {
public:
	struct D {};
	UniquePointer<int,D> up;
};

/**
 * Test: UniquePointer()
 */
TEST_F(UniquePointerTest, default_ctor) {
	ASSERT_EQ(nullptr, up.get());
}

/**
 * Test: UniquePointer(p)
 */
TEST_F(UniquePointerTest, ctor_with_pointer) {
	int * p = new int(20);
	UniquePointer<int,D> up(p);

	ASSERT_EQ(p, up.get());
	ASSERT_EQ(20, *up.get());
}

/**
 * Test: get()
 */
TEST_F(UniquePointerTest, get) {
	ASSERT_TRUE(up.get() == nullptr);
}

/**
 * Test: operator*()
 */
TEST_F(UniquePointerTest, operator_deref) {
	UniquePointer<int,D> up(new int(20));

	ASSERT_EQ(20, *up);
}

/**
 * Test: operator->()
 */
TEST_F(UniquePointerTest, operator_deref_member) {
	UniquePointer<std::string,D> up(new std::string("sample"));

	ASSERT_EQ(6, up->size());
}

} // end namespace test
} // end namespace prism
















