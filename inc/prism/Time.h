/*
 * Time.h
 * v1
 *
 *  Created on: Aug 15, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_TIME_H_
#define PRISM_TIME_H_

#include <prism/String>
#include <ostream>

namespace prism {

/*! This is the detailed description of Time.
 *
 */
class Time {
private:
	// num of ms since midnight i.e. now-midnight
	unsigned int m_ms;
public:
	enum {
		MS_PER_SECOND 	= 1000,
		MS_PER_MINUTE 	= 60000,
		MS_PER_HOUR 	= 3600000,
		MS_PER_DAY 		= 86400000,
		SEC_PER_MINUTE	= 60,
		SEC_PER_HOUR	= 3600,
		SEC_PER_DAY		= 86400,
		MIN_PER_HOUR	= 60,
		MIN_PER_DAY		= 1440,
		HOUR_PER_DAY	= 24
	};
public:
	Time();
	Time(const int hour, const int min, const int sec=0, const int msec=0);
	virtual ~Time();

	static Time currentTime();
	const int 	hour() const;
	const int 	min() const;
	const int	msec() const;
	void 		reset();
	const int 	sec() const;
	String		toString() const;

	friend std::ostream & operator<<(std::ostream & out, const Time & t);
};

} /* namespace prism */

#endif /* PRISM_TIME_H_ */
