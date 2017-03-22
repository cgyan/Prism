/*
 * ElapsedTimeMonitorFactory.cpp
 * v0.*
 *
 *  Created on: 22 Mar 2017
 *      Author: iainhemstock
 */

#include <prism/global>
#include <prism/h/priv/factories/ElapsedTimeMonitorFactory.h>
#include <prism/h/ElapsedTimeMonitor.h>

PRISM_BEGIN_NAMESPACE

std::shared_ptr<IElapsedTimeMonitor>
ElapsedTimeMonitorFactory::create() {
	return std::shared_ptr<IElapsedTimeMonitor>(new ElapsedTimeMonitor);
}


PRISM_END_NAMESPACE


