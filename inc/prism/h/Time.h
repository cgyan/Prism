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
	enum Periods {
		MS_PER_SECOND 	= 1000,
		MS_PER_MINUTE 	= 60000,
		MS_PER_HOUR 	= 3600000,
		MS_PER_DAY 		= 86400000,
		SECS_PER_MINUTE	= 60,
		SECS_PER_HOUR	= 3600,
		SECS_PER_DAY	= 86400,
		MINS_PER_HOUR	= 60,
		MINS_PER_DAY	= 1440,
		HOURS_PER_DAY	= 24
	};
public:
	Time();
	Time(const int hour, const int min, const int sec=0, const int msec=0);
	virtual ~Time();

	const int	elapsed() const;
	const int 	hour() const;
	const int	hoursTo(const Time & time) const;
	const int 	min() const;
	const int	minsTo(const Time & time) const;
	const int	msec() const;
	const int	msecsTo(const Time &time) const;
	void 		reset();
	const int 	sec() const;
	const int	secsTo(const Time & time) const;
	void		set(const int hour, const int min, const int sec=0, const int msec=0);
	void		start();
	String		toString() const;

	static Time currentTime();
	static Time hours(const int nHours);
	static Time mins(const int nMins);
	static Time secs(const int nSecs);
	static Time msecs(const int nMsecs);

	const bool 	operator==(const Time & other) const;
	const bool 	operator!=(const Time & other) const;
	const bool 	operator<(const Time & other) const;
	const bool 	operator<=(const Time & other) const;
	const bool 	operator>(const Time & other) const;
	const bool 	operator>=(const Time & other) const;
	Time &		operator+=(const Time & other);
	Time &		operator-=(const Time & other);

	// related nonmembers
	friend Time operator+(const Time &t1, const Time & t2);
	friend Time operator-(const Time &t1, const Time & t2);
	friend std::ostream & operator<<(std::ostream & out, const Time & t);
};

} /* namespace prism */

#endif /* PRISM_TIME_H_ */
