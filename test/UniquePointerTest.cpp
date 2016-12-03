/*
 * UniquePointerTest.cpp
 * v1
 *
 *  Created on: Nov 8, 2016
 *      Author: iainhemstock
 */

#include <gtest/gtest.h>
#include <prism/UniquePointer>
#include <prism/h/type_traits.h>
#include <string>

namespace prism {
namespace test {

template <typename T>
struct CustomDeleter {
	using pointer = T*;

	void
	operator()(pointer p) {
		delete p;
	}
};

class UniquePointerTest : public ::testing::Test {
public:
	using pointer = UniquePointer<int>::pointer;

	UniquePointer<int> dup; // default
	UniquePointer<int> iup;	// initialised

	UniquePointerTest()
	: dup(), // default unique pointer
	  iup(new int(20))
	{}
};

/**
 * Test: UniquePointer()
 */
TEST_F(UniquePointerTest, default_ctor) {
	ASSERT_EQ(nullptr, dup.data());
}

/**
 * Test: UniquePointer(p)
 */
TEST_F(UniquePointerTest, ctor_with_pointer) {
	ASSERT_EQ(20, *iup.data());
}

/**
 * Test: UniquePointer(UniquePointer&&)
 */
TEST_F(UniquePointerTest, move_ctor) {
	UniquePointer<int> p(prism::move(iup));
	ASSERT_TRUE(*p == 20);
}

/**
 * Test: operator=(UniquePointer&&)
 */
TEST_F(UniquePointerTest, move_assignment) {
	prism::UniquePointer<int> up;
	int * p_up = up.data();
	int * p_iup = iup.data();
	up = prism::move(iup);

	ASSERT_TRUE(up.data() == p_iup);
//	ASSERT_TRUE(iup.data() == p_up); // can't read it after a move
	ASSERT_TRUE(*up == 20);
//	ASSERT_FALSE(iup.data()); // // can't read it after a move
}

/**
 * Test: supplying a custom deleter object instead of using the default
 */
TEST_F(UniquePointerTest, custom_deleter) {
	UniquePointer<int, CustomDeleter<int>> up;
	ASSERT_TRUE(typeid(decltype(up.getDeleter()))
			== typeid(CustomDeleter<int>));
}

/**
 * Test: data()
 */
TEST_F(UniquePointerTest, data) {
	ASSERT_TRUE(dup.data() == nullptr);
}

/**
 * Test: getDeleter()
 */
TEST_F(UniquePointerTest, getDeleter) {
	using DefaultDeleter = prism::UniquePointerDeleter<int>;
	UniquePointer<int>::deleter_type dt = dup.getDeleter();

	ASSERT_EQ(typeid(dt), typeid(DefaultDeleter));
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
	UniquePointer<int>::pointer p = iup.release();

	ASSERT_TRUE(iup.data() == nullptr);
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

	ASSERT_TRUE(iup.data() != nullptr);
	ASSERT_TRUE(*iup == 100);
}

/**
 * Test: reset()
 */
TEST_F(UniquePointerTest, reset_to_default) {
	iup.reset();

	ASSERT_TRUE(iup.data() == nullptr);
}

/**
 * Test: swap(other)
 */
TEST_F(UniquePointerTest, swap) {
	pointer p_dup = dup.data();
	pointer p_iup = iup.data();

	dup.swap(iup);

	ASSERT_TRUE(dup.data() == p_iup);
	ASSERT_TRUE(iup.data() == p_dup);
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
	UniquePointer<std::string> up(new std::string("sample"));

	ASSERT_EQ(6, up->size());
}

/**
 * Test: swap()
 * -- the non-member swap specialization for UniquePointers
 */
TEST_F(UniquePointerTest, nonmember_swap) {
	UniquePointer<int> up1(new int(10));
	UniquePointer<int> up2(new int(20));

	swap(up1, up2);

	ASSERT_TRUE(*up1 == 20);
	ASSERT_TRUE(*up2 == 10);
}

} // end namespace test
} // end namespace prism
















