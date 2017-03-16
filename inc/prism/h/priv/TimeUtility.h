/*
 * TimeProvider.h
 * v0.*
 *
 *  Created on: 16 Mar 2017
 *      Author: iainhemstock
 */

#ifndef PRISM_TIME_PROVIDER_PRIV_H_
#define PRISM_TIME_PROVIDER_PRIV_H_

#include <prism/global>
#include <chrono>

PRISM_BEGIN_NAMESPACE

//=============================================================================================
// TimeProvider
//=============================================================================================
struct TimeUtility {

	static
	const unsigned long int
	msSinceMidnight() {
		using namespace std;

		chrono::time_point<chrono::system_clock> now = chrono::system_clock::now();
		time_t time = chrono::system_clock::to_time_t(now);

		struct tm *midnight = localtime(&time);
		midnight->tm_hour = 0;
		midnight->tm_min = 0;
		midnight->tm_sec = 0;

		chrono::time_point<chrono::system_clock> md = chrono::system_clock::from_time_t(mktime(midnight));
		chrono::system_clock::duration durationSinceMidnight = now-md;

		chrono::milliseconds msSinceMidnight = chrono::duration_cast<chrono::milliseconds>(durationSinceMidnight);

		return msSinceMidnight.count();
	}
};

PRISM_END_NAMESPACE

#endif /* PRISM_TIME_PROVIDER_PRIV_H_ */
