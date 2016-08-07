/*
 * algorithmsTest.cpp
 * v1
 *
 *  Created on: Aug 7, 2016
 *      Author: iainhemstock
 */


#include <gtest/gtest.h>
#include <prism/algorithms>
#include <iostream>
#include <cstdlib> // srand()
#include <ctime> // time()

namespace prism {

class algorithmsTest : public ::testing::Test {
public:
	int * intArray(const int size);
	int * randIntArray(const int size, const int min, const int max);
};

/**
 * Returns a sequentially ordered array of ints.
 */
int * algorithmsTest::intArray(const int size) {
	int * a = new int(size);
	for (int i=0; i<size; i++)
		a[i] = i;
	return a;
}
/**
 * Returns a randomly ordered array of ints ranging from min to max
 */
int * algorithmsTest::randIntArray(const int size, const int min, const int max) {
	int * a = new int(size);
	srand(time(0));
	for (int i=0; i<size; i++)
		a[i] = rand() % max;
	return a;
}
// ============================================================
// TESTS
// ============================================================
/**
 * Test: adjacent_find(first, last)
 */
TEST_F(algorithmsTest, adjacentFind) {
	int a[6] = { 1,3,7,7,5,6 };
	int * p = adjacent_find(a, a+6);
	int pValue = *p;
	int pIndex = p-a;

	ASSERT_TRUE(pValue == 7);
	ASSERT_TRUE(pIndex == 2	);
}

/**
 * Test: swap(val1, val2)
 */
TEST_F(algorithmsTest, swap) {
	int * a = intArray(10);
	swap(a[0], a[9]);

	ASSERT_TRUE(a[0] == 9);
	ASSERT_TRUE(a[9] == 0);

	delete []a;
}

}



