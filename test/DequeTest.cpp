/*
 * DequeTest.cpp
 * v1
 *
 *  Created on: Aug 20, 2016
 *      Author: iainhemstock
 */
#include <gtest/gtest.h>
#include <prism/Deque>
#include <ostream>
using namespace std;

namespace prism {

class DequeTest : public ::testing::Test {
protected:
	int** map;
	int mapSize;
	int bucketSize;
public:
	DequeTest() : map(nullptr), mapSize(2), bucketSize(8) {}

	~DequeTest() {
		if (map != nullptr) {
			for (int i=0; i<mapSize; i++)
				delete map[i];
			delete []map;
		}
	}

	int** getBuckets() {
			map = new int*[mapSize];

			int* block = new int[bucketSize];
			block[4] = 4; block[5] = 5; block[6] = 6; block[7] = 7;
			map[0] = block;

			block = new int[bucketSize];
			block[0] = 10; block[1] = 11; block[2] = 12; block[3] = 13;
			block[4] = 14; block[5] = 15; block[6] = 16; block[7] = 17;
			map[1] = block;

			return map;
	}
};

/**
 * Test: Deque<T>()
 */
TEST_F(DequeTest, default_ctor)
{
	int** buckets = getBuckets();

	DequeIterator<int> begin(buckets, *buckets+4);
	DequeIterator<int> end(buckets+1, *(buckets+1)+bucketSize);
	DequeIterator<int> it = end;

	cout << (end-begin) << endl;

}


}








