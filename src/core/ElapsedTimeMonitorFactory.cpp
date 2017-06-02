/*
 * ElapsedTimeMonitorFactory.cpp
 * v0.*
 *
 *  Created on: 22 Mar 2017
 *      Author: iainhemstock
 */

#include <prism/global>
#include <prism/core/priv/factories/ElapsedTimeMonitorFactory.h>
#include <prism/core/ElapsedTimeMonitor.h>

PRISM_BEGIN_NAMESPACE

std::shared_ptr<IElapsedTimeMonitor>
ElapsedTimeMonitorFactory::create() {
	return std::shared_ptr<IElapsedTimeMonitor>(new ElapsedTimeMonitor);
}


PRISM_END_NAMESPACE
