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
	UniquePointer<int,D> dup;
	UniquePointer<int,D> iup;

	UniquePointerTest()
	: dup(), // default unique pointer
	  iup(new int(20))
	{}
};

/**
 * Test: UniquePointer()
 */
TEST_F(UniquePointerTest, default_ctor) {
	ASSERT_EQ(nullptr, dup.get());
}

/**
 * Test: UniquePointer(p)
 */
TEST_F(UniquePointerTest, ctor_with_pointer) {
	ASSERT_EQ(20, *iup.get());
}

/**
 * Test: get()
 */
TEST_F(UniquePointerTest, get) {
	ASSERT_TRUE(dup.get() == nullptr);
}

/**
 * Test: isNull()
 */
TEST_F(UniquePointerTest, isNull) {
	ASSERT_TRUE(dup.isNull());
	ASSERT_FALSE(iup.isNull());
}

/**
 * Test: release()
 */
TEST_F(UniquePointerTest, release) {
	UniquePointer<int,D>::pointer p = iup.release();

	ASSERT_TRUE(iup.get() == nullptr);
	ASSERT_FALSE(p == nullptr);
	ASSERT_TRUE(*p == 20);

	delete p;
}

/**
 * Test: reset(p)
 */
TEST_F(UniquePointerTest, reset_with_replacement_pointer) {
	int * p = new int(100);
	iup.reset(p);

	ASSERT_TRUE(iup.get() != nullptr);
	ASSERT_TRUE(*iup == 100);
}

/**
 * Test: reset()
 */
TEST_F(UniquePointerTest, reset_to_default) {
	iup.reset();

	ASSERT_TRUE(iup.get() == nullptr);
}

/**
 * Test: operator*()
 */
TEST_F(UniquePointerTest, operator_deref) {
	ASSERT_EQ(20, *iup);
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
















