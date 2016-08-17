/*
 * main.cpp
 *
 *  Created on: Dec 28, 2014
 *      Author: iainhemstock
 */

#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <stack>
#include <list>
#include <queue>
#include <deque>
#include <forward_list>
#include <climits>
#include <algorithm>
#include <cmath>
#include <bitset>
#include <chrono>
#include <ctime>
#include <prism/Array>
#include <prism/Stack>
#include <prism/List>
#include <prism/Queue>
#include <prism/Vector>
#include <prism/Iterator>
#include <prism/Point>
#include <prism/Pointf>
#include <prism/OutOfBoundsException>
#include <prism/SharedPointer>
#include <prism/Fraction>
#include <prism/Mathf>
#include <prism/Size>
#include <prism/Rect>
#include <prism/Circle>
#include <prism/String>
#include <prism/Char>
#include <prism/algorithms>
#include <prism/Bitvector>
#include <prism/Time>


using namespace prism;
using namespace std;

bool isOdd(int n) { return n%2 == 1; }
bool isEven(int n) { return n%2 == 0; }
bool isNegative(int n) { return n<0; }
void print(int n) { cout << n << endl; }

String toString(chrono::system_clock::time_point &tp) {
	time_t t = chrono::system_clock::to_time_t(tp);
	String ts = ctime(&t);
	ts.chop(1);
	return ts;
}

int msToSec(int ms) { return ms/1000; }
int msToMin(int ms) { return ms/1000/60; }
int msToHour(int ms) { return ms/1000/60/60; }
int hourToMs(int hour) { return hour*60*60*1000; }
int minToMs(int min) { return min*60*1000; }
int secToMs(int sec) { return sec*1000; }

int main(int argc, char * argv[]) {
	// to run certain test cases use string with this format: "*Class1*:*Class2*:*ClassN*"
	// to run a single test within a test case use: "*Class.test*" e.g. "*Stack.pop*"
	::testing::GTEST_FLAG(filter) = "*Time*";
	::testing::InitGoogleTest(&argc, argv);

//	chrono::seconds twentySeconds(20);
//	chrono::seconds tenSeconds(10);
//	chrono::minutes oneMinute(1);
//	chrono::minutes result = oneMinute + chrono::duration_cast<chrono::minutes>(tenSeconds);
//
//	cout << result.count() << endl;
//
//
//	chrono::system_clock::time_point tp;
//	String s = toString(tp);
//	cout << s << endl;
//
//	tp = chrono::system_clock::now();
//	s = toString(tp);
//	cout << s << endl;

//	tp = chrono::system_clock::time_point::min();
//	s = toString(tp);
//	cout << s << endl;
//
//	tp = chrono::system_clock::time_point::max();
//	s = toString(tp);
//	cout << s << endl;

	/*
	 * clock_t is a number
	 * time_t is a number measured in seconds
	 * clock() returns ms since program launch
	 * time(time_t *) returns secs since 00:00 hours, Jan 1, 1970 UTC (UNIX timestamp)
	 * localtime(time_t) converts a time_t into a struct tm
	 * gmtime(time_t) converts a time into a struct tm
	 * struct tm creates an arbitrary point in time
			tm_sec	int	seconds after the minute	0-60*
			tm_min	int	minutes after the hour	0-59
			tm_hour	int	hours since midnight	0-23
			tm_mday	int	day of the month	1-31
			tm_mon	int	months since January	0-11
			tm_year	int	years since 1900
			tm_wday	int	days since Sunday	0-6
			tm_yday	int	days since January 1	0-365
			tm_isdst	int	Daylight Saving Time flag
	 * mktime(struct * tm) converts a struct tm into a time_t
	 * difftime(time2, time1) returns a double  that is the number of seconds between time2 and time1
	 */

//	clock_t time;
//	time = clock();
//
//	int j=0;
//	for (int i=0; i<1000000; i++, j++)
//		j = i * 2876 % 234;
//
//	time = clock() - time;
//	cout << "time " << (float)time/CLOCKS_PER_SEC << endl;

	// -----------

//	time_t now = time(NULL); // current time (secs since epoch)
//	cout << ctime(&now) << endl;
//
//
//	struct tm * midnight = localtime(&now);
//	midnight->tm_sec = 0;
//	midnight->tm_min = 0;
//	midnight->tm_hour = 0;
//
//	time_t tt2 = mktime(midnight);
//
//	double diff = difftime(now,tt2);
//	double ms = diff * 1000;
//	double sec = diff;
//	int min = sec/60;
//	int hour = min/60;
//	double day = hour/24;
//
////	cout.setf(std::ios::fixed, std::ios::floatfield);
//	cout << "diff (secs): " << diff << endl;
//	cout << "milliseconds since midnight: " << ms << endl;
//	cout  << "seconds since midnight: " << diff << endl;
//	cout  << "minutes since midnight: " << min << endl;
//	cout  << "hours since midnight: " << hour << endl;
//	cout  << "days since midnight: " << day << endl;
//
//	unsigned int msSinceMidnight = diff * 1000;
//	unsigned int currentHour = msToHour(msSinceMidnight);
//	unsigned int currentMin = msToMin(msSinceMidnight - hourToMs(currentHour));
//	unsigned int currentSec = msToSec(msSinceMidnight - hourToMs(currentHour) - minToMs(currentMin));
//	unsigned int currentMs = msSinceMidnight % 1000;
//	cout << msSinceMidnight << endl;
//
//	cout << currentHour << ":" << currentMin << ":" << currentSec << ":" << currentMs << endl;

	// -----------

//	chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();
//	time_t time = chrono::system_clock::to_time_t(now);
//
//	struct tm *midnight = localtime(&time);
//	midnight->tm_hour = 0;
//	midnight->tm_min = 0;
//	midnight->tm_sec = 0;
//
//	chrono::time_point<chrono::system_clock> md = chrono::system_clock::from_time_t(mktime(midnight));
//	chrono::system_clock::duration durationSinceMidnight = now-md;
//
//	chrono::hours 			hours = chrono::duration_cast<chrono::hours>(durationSinceMidnight);
//	chrono::minutes 		mins = chrono::duration_cast<chrono::minutes>(durationSinceMidnight-hours);
//	chrono::seconds 		secs = chrono::duration_cast<chrono::seconds>(durationSinceMidnight-hours-mins);
//	chrono::milliseconds 	ms = chrono::duration_cast<chrono::milliseconds>(durationSinceMidnight-hours-mins-secs);
//	chrono::milliseconds	msSinceMidnight = chrono::duration_cast<chrono::milliseconds>(durationSinceMidnight);
//	chrono::minutes			minsSinceMidnight = chrono::duration_cast<chrono::minutes>(durationSinceMidnight);
//
//	cout << hours.count() << " hours since midnight" << endl;
//	cout << mins.count() << " mins since midnight" << endl;
//	cout << secs.count() << " secs since midnight" << endl;
//	cout << ms.count() << " ms since midnight" << endl;
//	cout << "ms since midnight: " << msSinceMidnight.count() << endl;
//	cout << "mins since midnight: " << minsSinceMidnight.count() << endl;


	int i = Time::MS_PER_DAY + 6345;
	cout << i % Time::MS_PER_DAY << endl;



	return RUN_ALL_TESTS();
//	return 0;
}

















