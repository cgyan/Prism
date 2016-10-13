/*
 * algorithmsTest.cpp
 * v1
 *
 *  Created on: Aug 7, 2016
 *      Author: iainhemstock
 */


#include <gtest/gtest.h>
#include <prism/algorithm>
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

/**
 * Predicates for tests
 */
bool algorithmsTest_isOdd(const int n) { return n%2 == 1; }
bool algorithmsTest_isEven(int n) { return n%2 == 0; }
bool algorithmsTest_isNegative(int n) { return n<0; }
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
 * Test: all_of(first, last, pred)
 */
TEST_F(algorithmsTest, all_of) {
	int a[5] = {2,4,6,8,10};
	bool allEven = all_of(a, a+5, algorithmsTest_isEven);
	bool allOdd = all_of(a, a+5, algorithmsTest_isOdd);
	ASSERT_TRUE(allEven);
	ASSERT_FALSE(allOdd);
}

/**
 * Test: any_of(first, last, pred)
 */
TEST_F(algorithmsTest, any_of) {
	int a[6] = {2,4,6,-12,8,10};
	bool anyNeg = any_of(a, a+6, algorithmsTest_isNegative);
	bool anyOdd = any_of(a, a+6, algorithmsTest_isOdd);
	ASSERT_TRUE(anyNeg);
	ASSERT_FALSE(anyOdd);
}

/**
 * Test: swap(val1, val2)
 */
TEST_F(algorithmsTest, swap) {
	int a[5] = {1,2,3,4,5};
	swap(a[0], a[4]);

	ASSERT_TRUE(a[0] == 5);
	ASSERT_TRUE(a[4] == 1);
}

}



