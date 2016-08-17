/*
 * TimeTest.cpp
 * v1
 *
 *  Created on: Aug 15, 2016
 *      Author: iainhemstock
 */

#include <gtest/gtest.h>
#include <prism/Time>
#include <iostream>
using namespace std;

namespace prism {

class TimeTest : public ::testing::Test {

};

/**
 * Test: Time()
 */
TEST_F(TimeTest, ctor) {

}

/**
 * Test: Time(h,m,s,ms)
 */
TEST_F(TimeTest, ctor_time) {
	Time t(15,33, 24,125);
	cout << t.toString() << endl;
}

/**
 * Test: hour()
 */
TEST_F(TimeTest, hour) {

}

/**
 * Test: currentTime()
 */
TEST_F(TimeTest, currentTime) {
	Time t = Time::currentTime();
	cout << t.toString() << endl;
}


}











