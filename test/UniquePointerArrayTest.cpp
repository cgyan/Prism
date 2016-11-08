/*
 * UniquePointerArrayTest.cpp
 * v1
 *
 *  Created on: Nov 8, 2016
 *      Author: iainhemstock
 */

#include <gtest/gtest.h>
#include <prism/UniquePointer>
#include <prism/algorithm>

namespace prism {
namespace test {

template <typename T>
struct CustomArrayDeleter {
	using pointer = T*;

	void
	operator()(pointer p) {
		delete []p;
	}
};

class UniquePointerArrayTest : public ::testing::Test {
public:
	using pointer = UniquePointer<int[]>::pointer;
	UniquePointer<int[]> dup;
	UniquePointer<int[]> iup;

	UniquePointerArrayTest()
	: dup(),
	  iup(new int[5])
	{
		for (int i=0; i<5; i++) {
			*(iup.data()+i) = 10+i; // array = [10,11,12,13,14]
		}
	}
};

/**
 * Test: UniquePointer()
 */
TEST_F(UniquePointerArrayTest, default_ctor) {
	ASSERT_EQ(nullptr, dup.data());
}

/**
 * Test: UniquePointer(p)
 */
TEST_F(UniquePointerArrayTest, ctor_with_pointer) {
	ASSERT_EQ(10, iup[0]);
}

/**
 * Test: supplying a custom deleter object instead of using the default
 */
TEST_F(UniquePointerArrayTest, custom_deleter) {
	UniquePointer<int, CustomArrayDeleter<int>> up;
	ASSERT_TRUE(typeid(decltype(up.getDeleter()))
			== typeid(CustomArrayDeleter<int>));
}

/**
 * Test: data()
 */
TEST_F(UniquePointerArrayTest, data) {
	ASSERT_TRUE(dup.data() == nullptr);
}

/**
 * Test: getDeleter()
 */
TEST_F(UniquePointerArrayTest, getDeleter) {
	using DefaultDeleter = prism::UniquePointerDeleter<int[]>;
	UniquePointer<int[]>::deleter_type dt = dup.getDeleter();

	ASSERT_EQ(typeid(dt), typeid(DefaultDeleter));
}

/**
 * Test: isNull()
 */
TEST_F(UniquePointerArrayTest, isNull) {
	ASSERT_TRUE(dup.isNull());
	ASSERT_FALSE(iup.isNull());
}

/**
 * Test: release()
 */
TEST_F(UniquePointerArrayTest, release) {
	UniquePointer<int[]>::pointer p = iup.release();

	ASSERT_TRUE(iup.data() == nullptr);
	ASSERT_FALSE(p == nullptr);
	ASSERT_TRUE(p[0] == 10);

	delete p;
}

/**
 * Test: reset()
 */
TEST_F(UniquePointerArrayTest, reset_to_default) {
	iup.reset();

	ASSERT_TRUE(iup.data() == nullptr);
}

/**
 * Test: reset(p)
 */
TEST_F(UniquePointerArrayTest, reset_with_replacement_pointer) {
	int * p = new int[5];
	p[0] = 23;
	iup.reset(p);

	ASSERT_TRUE(iup.data() != nullptr);
	ASSERT_TRUE(iup[0] == 23);
}

/**
 * Test: swap(other)
 */
TEST_F(UniquePointerArrayTest, swap) {
	pointer p_dup = dup.data();
	pointer p_iup = iup.data();

	dup.swap(iup);

	ASSERT_TRUE(dup.data() == p_iup);
	ASSERT_TRUE(iup.data() == p_dup);
}

/**
 * Test: swap()
 * -- the non-member swap specialization for UniquePointers
 */
TEST_F(UniquePointerArrayTest, nonmember_swap) {
	UniquePointer<int[]> up1(new int[5]);
	UniquePointer<int[]> up2(new int[5]);

	up1[0] = 30;
	up2[0] = 40;

	using prism::swap;
	swap(up1, up2);

	ASSERT_TRUE(up1[0] == 40);
	ASSERT_TRUE(up2[0] == 30);
}

/**
 * Test: operator*()
 */
TEST_F(UniquePointerArrayTest, operator_deref) {
	ASSERT_EQ(10, *iup);
}

/**
 * Test: operator->()
 */
TEST_F(UniquePointerArrayTest, operator_arrow) {
	UniquePointer<std::string> up(new std::string("sample"));

	ASSERT_EQ(6, up->size());
}

/**
 * Test: T& operator[]()
 */
TEST_F(UniquePointerArrayTest, operator_subscript_nonconst) {
	// assert all five values
	ASSERT_EQ(10, iup[0]);
	ASSERT_EQ(11, iup[1]);
	ASSERT_EQ(12, iup[2]);
	ASSERT_EQ(13, iup[3]);
	ASSERT_EQ(14, iup[4]);

	// modify a value and assert it's new value
	iup[0] = 100;
	ASSERT_EQ(100, iup[0]);
}

/**
 * Test: const T& operator[]() const
 */
TEST_F(UniquePointerArrayTest, operator_subscript_const) {
	ASSERT_FALSE(true);

	// todo how to unit test the const version of the subscript operator?

	// assert all five values
//	const int a = iup[0];
//	ASSERT_EQ(10, a);
//	const int b = iup[1];
//	ASSERT_EQ(11, b);
//	const int c = iup[2];
//	ASSERT_EQ(12, c);
//	const int d = iup[3];
//	ASSERT_EQ(13, d);
//	const int e = iup[4];
//	ASSERT_EQ(14, e);
}

} // end namespace test
} // end namespace prism














