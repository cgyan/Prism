/*
 * BitvectorTest.cpp
 * v0.*
 *
 *  Created on: Aug 9, 2016
 *      Author: iainhemstock
 */
#include <gtest/gtest.h>
#include <prism/Bitvector>
#include <iostream> // todo remove this
using namespace std; // todo remove this

namespace prism {

class BitvectorTest : public ::testing::Test {
};

/**
 * Test: constructor(nBits)
 */
TEST_F(BitvectorTest, constructor) {
	Bitvector bv(16);
}

/**
 * Test: constructor(string)
 */
TEST_F(BitvectorTest, constructor_string) {
	String s = "11101110";
	Bitvector bv(s);
	cout << bv << endl;
}

/**
 * Test: copy constructor
 */
TEST_F(BitvectorTest, copyConstructor) {
	Bitvector bv(8);
	bv.set(0);
	bv.set(2);
	bv.set(4);
	bv.set(7);

	Bitvector copy(bv);
	ASSERT_EQ(copy.toString(), "10010101");
}

/**
 * Test: get(pos)
 */
TEST_F(BitvectorTest, get) {
	Bitvector bv(6);
	bv.set(0);
	bv.set(2);
	bv.set(4);

	ASSERT_TRUE(bv.get(0));
	ASSERT_TRUE(bv.get(2));
	ASSERT_TRUE(bv.get(4));
	ASSERT_FALSE(bv.get(1));
	ASSERT_FALSE(bv.get(3));
	ASSERT_FALSE(bv.get(5));
}

/**
 * Test: resetAll()
 */
TEST_F(BitvectorTest, resetAll) {
	Bitvector bv(8);
	bv.set(0);
	bv.set(2);
	bv.set(4);
	bv.set(7);

	bv.resetAll();
	ASSERT_EQ(bv.toString(), "00000000");
}

/**
 * Test: setAll()
 */
TEST_F(BitvectorTest, setAll) {
	Bitvector bv(8);
	bv.setAll();
	ASSERT_EQ(bv.toString(), "11111111");
}

/**
 * Test: set(pos, bool)
 */
TEST_F(BitvectorTest, set_pos_bool) {
	Bitvector bv(8);
	bv.set(1, true);
	bv.set(6);

	ASSERT_FALSE(bv.get(0));
	ASSERT_TRUE(bv.get(1));
	ASSERT_FALSE(bv.get(2));
	ASSERT_FALSE(bv.get(3));
	ASSERT_FALSE(bv.get(4));
	ASSERT_FALSE(bv.get(5));
	ASSERT_TRUE(bv.get(6));
	ASSERT_FALSE(bv.get(7));
}

/**
 * Test: size()
 * Bitvector uses unsigned short ints as the internal storage
 * that are 16 bits each.
 */
TEST_F(BitvectorTest, size) {
	Bitvector bv(16);
	ASSERT_EQ(bv.size(), 16);
	Bitvector bv2(17);
	ASSERT_EQ(bv2.size(), 17);
}

/**
 * Test: toString()
 */
TEST_F(BitvectorTest, toString) {
	Bitvector bv(8);
	bv.setAll();

	ASSERT_EQ(bv.toString(), "11111111");

	bv.set(0, false);
	bv.set(4, false);

	ASSERT_EQ(bv.toString(), "11101110");
}

/**
 * Test: operator==()
 */
TEST_F(BitvectorTest, opEqualsEquals) {
	Bitvector bv1(8);
	bv1.setAll();
	Bitvector bv2(bv1);
	Bitvector bv3(12);

	ASSERT_TRUE(bv1 == bv2);
	ASSERT_FALSE(bv1 == bv3);
}

/**
 * Test: operator!=()
 */
TEST_F(BitvectorTest, opNotEquals) {
	Bitvector bv1(8);
	bv1.setAll();
	Bitvector bv2(bv1);
	Bitvector bv3(12);

	ASSERT_FALSE(bv1 != bv2);
	ASSERT_TRUE(bv1 != bv3);
}

}















