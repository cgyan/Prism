/*
 * SharedDataTest.cpp
 * v1
 *
 *  Created on: Aug 13, 2016
 *      Author: iainhemstock
 */
#include <gtest/gtest.h>
#include <prism/SharedData>

namespace prism {
namespace test {

class SharedDataTest : public ::testing::Test {

};

// SharedData is a base class and cannot be instantiated by itself
class Data : public SharedData {};

/**
 * Test: constructor
 */
TEST_F(SharedDataTest, constructor) {
	Data d;
	ASSERT_EQ(d.refCount(), 0);
	ASSERT_TRUE(d.isShareable());
}

/**
 * Test: copy constructor
 */
TEST_F(SharedDataTest, copyConstructor) {
	Data d;
	Data cd(d);
	ASSERT_EQ(cd.refCount(), 0);
	ASSERT_TRUE(cd.isShareable());
}

/**
 * Test: decRef()
 */
TEST_F(SharedDataTest, decRef) {
	Data d;
	d.incRef();
	d.incRef();
	ASSERT_EQ(d.refCount(), 2);
	d.decRef();
	ASSERT_EQ(d.refCount(), 1);
}

/**
 * Test: incRef()
 */
TEST_F(SharedDataTest, incRef) {
	Data d;
	d.incRef();
	d.incRef();
	ASSERT_EQ(d.refCount(), 2);
	d.decRef();
	ASSERT_EQ(d.refCount(), 1);
}

/**
 * Test: isShareable()
 */
TEST_F(SharedDataTest, isShareable) {
	Data d;
	ASSERT_TRUE(d.isShareable());
	d.setUnshareable();
	ASSERT_FALSE(d.isShareable());
}

/**
 * Test: isShared()
 */
TEST_F(SharedDataTest, isShared) {
	Data d;
	d.incRef();
	ASSERT_FALSE(d.isShared());
	d.incRef();
	ASSERT_TRUE(d.isShared());
}

/**
 * Test: refCount()
 */
TEST_F(SharedDataTest, refCount) {
	Data d;
	ASSERT_EQ(d.refCount(), 0);
	d.incRef();
	ASSERT_EQ(d.refCount(), 1);
	d.incRef();
	ASSERT_EQ(d.refCount(), 2);
	d.decRef();
	ASSERT_EQ(d.refCount(), 1);
}

/**
 * Test: setUnshareable()
 */
TEST_F(SharedDataTest, setUnshareable) {
	Data d;
	ASSERT_TRUE(d.isShareable());
	d.setUnshareable();
	ASSERT_FALSE(d.isShareable());
}

} // end namespace test
} // end namespace prism








