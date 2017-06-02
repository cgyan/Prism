/*
 * ElapsedTimeMonitorFactory.h
 * v0.*
 *
 *  Created on: 21 Mar 2017
 *      Author: iainhemstock
 */

#ifndef PRISM_ELAPSED_TIME_MONITOR_FACTORY_H_
#define PRISM_ELAPSED_TIME_MONITOR_FACTORY_H_

#include <prism/global>
#include <prism/core/IElapsedTimeMonitor.h>
#include <memory>

PRISM_BEGIN_NAMESPACE

struct ElapsedTimeMonitorFactory {
	static std::shared_ptr<IElapsedTimeMonitor> create();
};

PRISM_END_NAMESPACE

#endif /* PRISM_ELAPSED_TIME_MONITOR_FACTORY_H_ */
