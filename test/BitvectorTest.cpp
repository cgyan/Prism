/*
 * BitvectorTest.cpp
 * v0.*
 *
 *  Created on: Aug 9, 2016
 *      Author: iainhemstock
 */
#include <gtest/gtest.h>
#include <prism/Bitvector>

namespace prism {

class BitvectorTest : public ::testing::Test {
};

/**
 * Test: constructor(nBits)
 */
TEST_F(BitvectorTest, constructor) {
	Bitvector bv(16);
}

}

