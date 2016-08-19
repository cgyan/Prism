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
 * Test: constants
 */
TEST_F(TimeTest, constants) {
	ASSERT_TRUE(Time::MS_PER_SECOND == 1000);
	ASSERT_TRUE(Time::MS_PER_MINUTE == 60000);
	ASSERT_TRUE(Time::MS_PER_HOUR == 3600000);
	ASSERT_TRUE(Time::MS_PER_DAY == 86400000);
	ASSERT_TRUE(Time::SECS_PER_MINUTE == 60);
	ASSERT_TRUE(Time::SECS_PER_HOUR == 3600);
	ASSERT_TRUE(Time::SECS_PER_DAY == 86400);
	ASSERT_TRUE(Time::MINS_PER_HOUR == 60);
	ASSERT_TRUE(Time::MINS_PER_DAY == 1440);
	ASSERT_TRUE(Time::HOURS_PER_DAY == 24);
}

/**
 * Test: Time()
 */
TEST_F(TimeTest, ctor)
{
	Time time;

	ASSERT_EQ("00:00:00:000", time.toString());
	ASSERT_EQ(0, time.hour());
	ASSERT_EQ(0, time.min());
	ASSERT_EQ(0, time.sec());
	ASSERT_EQ(0, time.msec());
}

/**
 * Test: Time(h,m,s,ms)
 */
TEST_F(TimeTest, ctor_hour_min_sec_msec)
{
	Time time(14,23,56,862);

	ASSERT_EQ("14:23:56:862", time.toString());
	ASSERT_EQ(14, time.hour());
	ASSERT_EQ(23, time.min());
	ASSERT_EQ(56, time.sec());
	ASSERT_EQ(862, time.msec());
}

/**
 * Test: hour()
 */
TEST_F(TimeTest, hour)
{
	Time time(22,0);
	ASSERT_EQ(22, time.hour());
}

/**
 * Test: hoursTo(time)
 */
TEST_F(TimeTest, hoursTo)
{
	Time time(8,30);
	Time time2(12,45);
	Time time3(2,30);

	ASSERT_EQ(4, time.hoursTo(time2));
	ASSERT_EQ(-6, time.hoursTo(time3));
}

/**
 * Test: min()
 */
TEST_F(TimeTest, min) {
	Time t(17,56,45,123);
	ASSERT_EQ(56, t.min());
}

/**
 * Test: minsTo(time)
 */
TEST_F(TimeTest, minsTo)
{
	Time time(8,30);
	Time time2(12,45);
	Time time3(2,30);

	ASSERT_EQ(255, time.minsTo(time2));
	ASSERT_EQ(-360, time.minsTo(time3));
}

/**
 * Test: msec()
 */
TEST_F(TimeTest, msec) {
	Time t(17,56,45,123);
	ASSERT_EQ(123, t.msec());
}

/**
 * Test: msecsTo(time)
 */
TEST_F(TimeTest, msecsTo)
{
	Time time(8,30);
	Time time2(12,45);
	Time time3(2,30);

	ASSERT_EQ(15300000, time.msecsTo(time2));
	ASSERT_EQ(-21600000, time.msecsTo(time3));
}

/**
 * Test: reset()
 */
TEST_F(TimeTest, reset) {
	Time time(12,23,34,123);
	time.reset();

	ASSERT_EQ("00:00:00:000", time.toString());
	ASSERT_EQ(0, time.hour());
	ASSERT_EQ(0, time.min());
	ASSERT_EQ(0, time.sec());
	ASSERT_EQ(0, time.msec());
}

/**
 * Test: sec()
 */
TEST_F(TimeTest, sec) {
	Time t(17,56,45,123);
	ASSERT_EQ(45, t.sec());
}

/**
 * Test: secsTo(time)
 */
TEST_F(TimeTest, secsTo)
{
	Time time(8,30);
	Time time2(12,45);
	Time time3(2,30);

	ASSERT_EQ(15300, time.secsTo(time2));
	ASSERT_EQ(-21600, time.secsTo(time3));
}

/**
 * Test: set(h,m,s,ms)
 */
TEST_F(TimeTest, set) {
	Time time(1,2,3,123);

	ASSERT_EQ("01:02:03:123", time.toString());
	ASSERT_EQ(1, time.hour());
	ASSERT_EQ(2, time.min());
	ASSERT_EQ(3, time.sec());
	ASSERT_EQ(123, time.msec());
}

/**
 * Test: start()
 */
TEST_F(TimeTest, start) {
	Time time;
	time.start();
	for (int i=0; i<1000000000; i++);
	int ms = time.elapsed();

	ASSERT_GT(ms, time.msecsTo(time));
}

/**
 * Test: toString()
 */
TEST_F(TimeTest, toString) {
	Time time;
	ASSERT_EQ("00:00:00:000", time.toString());

	time.set(23,43,12,567);
	ASSERT_EQ("23:43:12:567", time.toString());
}

/**
 * Test: hour(nHours)
 */
TEST_F(TimeTest, hour_nHours) {
	Time t = Time::hours(13);
	ASSERT_EQ("13:00:00:000", t.toString());
	ASSERT_EQ(13, t.hour());
	ASSERT_EQ(0, t.min());
	ASSERT_EQ(0, t.sec());
	ASSERT_EQ(0, t.msec());
}

/**
 * Test: min(nMins)
 */
TEST_F(TimeTest, min_nMins) {
	Time t = Time::mins(45);
	ASSERT_EQ("00:45:00:000", t.toString());
	ASSERT_EQ(0, t.hour());
	ASSERT_EQ(45, t.min());
	ASSERT_EQ(0, t.sec());
	ASSERT_EQ(0, t.msec());
}

/**
 * Test: sec(nSecs)
 */
TEST_F(TimeTest, sec_nSecs) {
	Time t = Time::secs(56);
	ASSERT_EQ("00:00:56:000", t.toString());
	ASSERT_EQ(0, t.hour());
	ASSERT_EQ(0, t.min());
	ASSERT_EQ(56, t.sec());
	ASSERT_EQ(0, t.msec());
}

/**
 * Test: msec(nMsecs)
 */
TEST_F(TimeTest, msecs_nMsecs) {
	Time t = Time::msecs(995);
	ASSERT_EQ("00:00:00:995", t.toString());
	ASSERT_EQ(0, t.hour());
	ASSERT_EQ(0, t.min());
	ASSERT_EQ(0, t.sec());
	ASSERT_EQ(995, t.msec());
}

/**
 * Test: operator==()
 */
TEST_F(TimeTest, op_EqualsEquals) {
	Time time(12,30);
	Time time2(time);
	Time time3 = time;
	Time time4(23,10);

	ASSERT_TRUE(time == time2);
	ASSERT_TRUE(time == time3);
	ASSERT_FALSE(time == time4);
}

/**
 * Test: operator!=()
 */
TEST_F(TimeTest, op_NotEquals) {
	Time time(12,30);
	Time time2(23,10);
	Time time3 = time;

	ASSERT_TRUE(time != time2);
	ASSERT_FALSE(time != time3);
}

/**
 * Test: operator<()
 */
TEST_F(TimeTest, op_LessThan) {
	Time time(12,30);
	Time time2(23,10);

	ASSERT_TRUE(time < time2);
	ASSERT_FALSE(time2 < time);
}

/**
 * Test: operator<=()
 */
TEST_F(TimeTest, op_LessThanEquals) {
	Time time(23,10);
	Time time2(23,10);

	ASSERT_TRUE(time <= time2);
}

/**
 * Test: operator>()
 */
TEST_F(TimeTest, op_GreaterThan) {
	Time time(12,30);
	Time time2(23,10);

	ASSERT_TRUE(time2 > time);
	ASSERT_FALSE(time > time2);
}

/**
 * Test: operator>=()
 */
TEST_F(TimeTest, op_GreaterThanEquals) {
	Time time(23,10);
	Time time2(23,10);

	ASSERT_TRUE(time >= time2);
}

/**
 * Test: operator+=()
 */
TEST_F(TimeTest, opPlusEquals) {
	Time time;
	time += Time::msecs(43200000);

	ASSERT_EQ("12:00:00:000", time.toString());
	ASSERT_EQ(12, time.hour());
	ASSERT_EQ(0, time.min());
	ASSERT_EQ(0, time.sec());
	ASSERT_EQ(0, time.msec());
}

/**
 * Test: operator-=()
 */
TEST_F(TimeTest, opMinusEquals) {
	Time time = Time::msecs(43200000); // 12pm
	time -= Time::mins(45);

	ASSERT_EQ("11:15:00:000", time.toString());
	ASSERT_EQ(11, time.hour());
	ASSERT_EQ(15, time.min());
	ASSERT_EQ(0, time.sec());
	ASSERT_EQ(0, time.msec());
}

/**
 * Test: operator+(Time, Time)
 */
TEST_F(TimeTest, opPlus) {
	Time time = Time::msecs(43200000); // 12pm
	time = time + Time::hours(3) + Time::mins(25) + Time::secs(10) + Time::msecs(550);

	ASSERT_EQ("15:25:10:550", time.toString());
	ASSERT_EQ(15, time.hour());
	ASSERT_EQ(25, time.min());
	ASSERT_EQ(10, time.sec());
	ASSERT_EQ(550, time.msec());
}

/**
 * Test: operator-(Time, Time)
 */
TEST_F(TimeTest, opMinus) {
	Time time = Time::hours(12); // 12pm
	time = time - Time::hours(3) - Time::mins(25) - Time::secs(10) - Time::msecs(550);

	ASSERT_EQ("08:34:49:450", time.toString());
	ASSERT_EQ(8, time.hour());
	ASSERT_EQ(34, time.min());
	ASSERT_EQ(49, time.sec());
	ASSERT_EQ(450, time.msec());
}


}











