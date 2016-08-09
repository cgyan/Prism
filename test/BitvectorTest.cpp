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
 * Test: get(pos)
 */
TEST_F(BitvectorTest, get) {
	Bitvector bv(20);
	bool bit = bv.get(0);
	ASSERT_FALSE(bit);
}

/**
 * Test: reset()
 */
TEST_F(BitvectorTest, reset) {
	Bitvector bv(8);
	bv.set(0);
	bv.set(25);
	bv.set(49);
	bv.set(61);

	bv.reset();
	ASSERT_EQ(bv.toString(), "00000000");
}

/**
 * Test: set()
 */
TEST_F(BitvectorTest, set) {
	Bitvector bv(8);
	bv.set();
	ASSERT_EQ(bv.toString(), "11111111");
}

/**
 * Test: set(pos, bool)
 */
TEST_F(BitvectorTest, set_pos_bool) {
	Bitvector bv(16);
	bv.set(1, true);
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
	bv.set(0);
	bv.set(2);
	bv.set(4);
	bv.set(7);

	String s = bv.toString();
	ASSERT_EQ(s, "10010101");
}

}















