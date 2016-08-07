/*
 * algorithmsTest.cpp
 * v1
 *
 *  Created on: Aug 7, 2016
 *      Author: iainhemstock
 */


#include <gtest/gtest.h>
#include <iostream>
#include <prism/algorithms>

namespace prism {

class algorithmsTest : public ::testing::Test {
public:
	int * intArray(const int size);
};

/**
 * Returns a sequentially ordered array of ints.
 */
int * algorithmsTest::intArray(const int size) {
	int * a = new int(size);
	for (int i=0; i<10; i++)
		a[i] = i;
	return a;
}
// ============================================================
// TESTS
// ============================================================
/**
 *
 */
TEST_F(algorithmsTest, swap) {
	int * a = intArray(10);
	swap(a[0], a[9]);

	ASSERT_TRUE(a[0] == 9);
	ASSERT_TRUE(a[9] == 0);
}

}



