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
	Time t = Time::currentTime();
	t = t + Time::hour(2);
	cout << t.toString() << endl;
}

/**
 * Test: Time(h,m,s,ms)
 */
TEST_F(TimeTest, ctor_time) {

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

}


}











