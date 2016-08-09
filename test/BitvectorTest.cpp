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
 * Test: set(pos, bool)
 */
TEST_F(BitvectorTest, set) {
	Bitvector bv(16);
	bv.set(1, true);
	cout << bv.get(1) << endl;
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

}

}















