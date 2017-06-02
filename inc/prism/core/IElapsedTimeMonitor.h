/*
 * ElapsedTimeMonitorAbstract.h
 * v0.*
 *
 *  Created on: 15 Mar 2017
 *      Author: iainhemstock
 */

#ifndef PRISM_IELAPSED_TIME_MONITOR_H_
#define PRISM_IELAPSED_TIME_MONITOR_H_

#include <prism/global>

PRISM_BEGIN_NAMESPACE

class IElapsedTimeMonitor {
public:
	virtual ~IElapsedTimeMonitor() {};
	virtual void start() = 0;
	virtual const int elapsed() const = 0;
};

PRISM_END_NAMESPACE

#endif /* PRISM_IELAPSED_TIME_MONITOR_H_ */
