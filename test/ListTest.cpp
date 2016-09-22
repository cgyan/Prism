///*
// * ListTest.cpp
// *
// *  Created on: Jan 13, 2015
// *      Author: iainhemstock
// */
//
#include "gtest/gtest.h"
#include <prism/h/List.h>

namespace prism {

class ListTest : public ::testing::Test {

};

TEST_F(ListTest, defaultState) {
	List<int> list;
	ASSERT_TRUE(list.size() == 0);
}

TEST_F(ListTest, append) {
	List<int> list;
	list.append(10);

	ASSERT_TRUE(list.size() == 1);
	ASSERT_EQ(*list.begin(), 10);
}

TEST_F(ListTest, back) {
	List<int> list;
	list.append(10);
	ASSERT_TRUE(list.back() == 10);
	list.append(20);
	ASSERT_TRUE(list.back() == 20);
}

TEST_F(ListTest, clear) {
	List<int> list;
	list << 1 << 2 << 3;
	list.clear();
	ASSERT_TRUE(list.size() == 0);
}

} // end namespace prism
