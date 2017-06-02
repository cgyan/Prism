/*
 * ElapsedTimeMonitor.h
 * v0.*
 *
 *  Created on: 20 Mar 2017
 *      Author: iainhemstock
 */

#ifndef PRISM_ELAPSED_TIME_MONITOR_H_
#define PRISM_ELAPSED_TIME_MONITOR_H_

#include <prism/global>
#include <prism/core/IElapsedTimeMonitor.h>
#include <prism/core/priv/TimeUtility.h>

PRISM_BEGIN_NAMESPACE

//=============================================================================================
// ElapsedTimeMonitor
//=============================================================================================
struct ElapsedTimeMonitor : public IElapsedTimeMonitor {
	unsigned long int msStart{};
	enum { MS_PER_DAY = 86400000 };

	void
	start() override {
		msStart = TimeUtility::msSinceMidnight();
	}

	const int
	elapsed() const override {
		const int msEnd = TimeUtility::msSinceMidnight();
		int msElapsed = msEnd - msStart;
		if (msElapsed < 0)
			msElapsed += MS_PER_DAY;
		return msElapsed;
	}
};

PRISM_END_NAMESPACE

#endif /* PRISM_ELAPSED_TIME_MONITOR_H_ */
