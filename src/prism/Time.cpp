/*
 * Time.cpp
 * v1
 *
 *  Created on: Aug 15, 2016
 *      Author: iainhemstock
 */

#include <prism/h/priv/TimeUtility.h>
#include <prism/h/Time.h>
#include <prism/h/String.h>

namespace prism {
//=============================================================================================
// TimeStringBuilder
//=============================================================================================
struct TimeStringBuilder {
	String ret;

	void
	appendHours(const int h) {
		if (h < 10) ret += String("0");
		ret += String::number(h);
		ret += String(":");
	}

	void
	appendMins(const int m) {
		if (m < 10) ret += String("0");
		ret += String::number(m);
		ret += String(":");
	}

	void
	appendSecs(const int s) {
		if (s < 10) ret += String("0");
		ret += String::number(s);
		ret += String(":");
	}

	void
	appendMsecs(const int ms) {
		if (ms < 100) ret += String("0");
		if (ms < 10) ret += String("0");
		ret += String::number(ms);
	}

	String
	toString() {
		return ret;
	}
};

//=============================================================================================
// ElapsedTimeMonitor
//=============================================================================================
struct ElapsedTimeMonitor : public IElapsedTimeMonitor {
	unsigned long int ms{};

	void
	start() override {
		ms = TimeUtility::msSinceMidnight();
	}

	const int
	elapsed() const override {
		const unsigned long int now = TimeUtility::msSinceMidnight();
		int msElapsed = now - ms;
		if (msElapsed < 0)
			msElapsed += 86400000;
		return msElapsed;
	}
};

//=============================================================================================
// TimeImpl
//=============================================================================================
struct Time::TimeImpl {
	unsigned long int ms{}; // num of ms since midnight i.e. now-midnight
	std::shared_ptr<IElapsedTimeMonitor> etm;

	TimeImpl()
	: ms{},
	  etm{}
	{}

	TimeImpl(const int hour, const int min, const int sec, const int msec)
	: ms(hour * MS_PER_HOUR +
			min * MS_PER_MINUTE +
			sec * MS_PER_SECOND +
			msec),
	  etm{}
	{}

	TimeImpl(const TimeImpl& rhs)
	: ms{rhs.ms},
	  etm{rhs.etm}
	{}

	void
	setEtm(std::shared_ptr<IElapsedTimeMonitor> etm) {
		this->etm = etm;
	}
};
//=============================================================================================
// Time
//=============================================================================================
/**
 * Constructs a Time object set to midnight i.e. hour=min=sec=msec=0.
 */
Time::Time()
: impl{new TimeImpl}
{
	impl->setEtm(std::make_shared<ElapsedTimeMonitor>());
}

/**
 * Constructs a Time object set to \em hour, \em min, \em sec and \em msec.
 */
Time::Time(const int hour, const int min, const int sec, const int msec)
: impl{new TimeImpl(hour, min, sec, msec)}
{
	impl->setEtm(std::make_shared<ElapsedTimeMonitor>());
}

/**
 *
 */
Time::Time(const Time& rhs)
: impl{new TimeImpl(*rhs.impl.get())}
{}

/**
 * Destroys this Time object.
 */
Time::~Time()
{}

/**
 *
 */
Time& Time::operator=(const Time& rhs) {
	impl.reset(new TimeImpl{rhs.hour(), rhs.min(), rhs.sec(), rhs.msec()});
	return *this;
}

/**
 *
 */
void Time::setEtm(ETM etm) {
	impl->setEtm(etm);
}

/**
 * @return Returns a Time object set to the current time as read from the system clock.
 */
Time Time::currentTime() {
	Time t;
	t.set(TimeUtility::msSinceMidnight());
	return t;
}

/**
 * @return Returns the hour part of the time (0-23).
 */
const int Time::hour() const {
	return impl->ms / MS_PER_HOUR;
}

/**
 * @return Returns the minute part of the time (0-59).
 */
const int Time::min() const {
	return (impl->ms % MS_PER_HOUR) / MS_PER_MINUTE;
}

/**
 * @return Returns the second part of the time (0-59).
 */
const int Time::sec() const {
	return (impl->ms / MS_PER_SECOND) % SECS_PER_MINUTE;
}

/**
 * @return Returns the millisecond part of the time (0-999).
 */
const int Time::msec() const {
	return impl->ms % 1000;
}

/**
 * Static function that creates a Time object set to \em nHours.
 */
Time Time::hours(const int nHours) {
	return Time(nHours,0);
}

/**
 * Static function that creates a Time object set to \em nMins.
 */
Time Time::mins(const int nMins) {
	return Time(0,nMins);
}

/**
 * Static function that creates a Time object set to \em nSsecs.
 */
Time Time::secs(const int nSecs) {
	return Time(0,0,nSecs);
}

/**
 * Static function that creates a Time object set to \em nMsecs.
 */
Time Time::msecs(const int nMsecs) {
	return Time(0,0,0, nMsecs);
}

/**
 * @return Returns the number of hours between \em time and this object's time.
 */
const int Time::hoursTo(const Time & time) const {
	return time.impl->ms / MS_PER_HOUR - impl->ms / MS_PER_HOUR;
}

/**
 * @return Returns the number of minutes between \em time and this object's time.
 */
const int Time::minsTo(const Time & time) const {
	return time.impl->ms / MS_PER_MINUTE - impl->ms / MS_PER_MINUTE;
}

/**
 * @return Returns the number of seconds between \em time and this object's time.
 */
const int Time::secsTo(const Time & time) const {
	return time.impl->ms / MS_PER_SECOND - impl->ms / MS_PER_SECOND;
}

/**
 * @return Returns the number of milliseconds between \em time and this object's time.
 */
const int Time::msecsTo(const Time & time) const {
	return time.impl->ms - impl->ms;
}

/**
 * Resets the time back to midnight i.e. hour=min=sec=msec=0.
 */
void Time::reset() {
	impl->ms = 0;
}

/**
 *
 */
void Time::set(const unsigned long int msec) {
	impl->ms = msec;
}

/**
 * Sets this Time object to \em hour, \em min, \em sec and \em msec.
 */
void Time::set(const int hour, const int min, const int sec, const int msec) {
	impl->ms = hour * MS_PER_HOUR +
			min * MS_PER_MINUTE +
			sec * MS_PER_SECOND +
			msec;
}

/**
 * Sets the time to the current time. Time can then be measured by calling elapsed()
 * at some later point.
 * \code
 * Time t;
 * t.start();
 * doSomethingIntensive();
 * int ms = t.elapsed(); // number of milliseconds since t.start() was called
 * \endcode
 */
void Time::start() {
	impl->etm->start();
}

/**
 * Used in conjunction with start(), time can be measured by calling elapsed().
 * \code
 * Time t;
 * t.start();
 * doSomethingIntensive();
 * int ms = t.elapsed(); // number of milliseconds since t.start() was called
 * \endcode
 * @return Returns the number of milliseconds since start() was called.
 */
const int Time::elapsed() const {
	return impl->etm->elapsed();
}

/**
 * @return Returns a string representation of the time in the form 00:00:00:000.
 */
String Time::toString() const {
	TimeStringBuilder sb;
	sb.appendHours(hour());
	sb.appendMins(min());
	sb.appendSecs(sec());
	sb.appendMsecs(msec());
	return sb.toString();
}

/**
 * @return Returns true if this object and \em other have the same time, false otherwise.
 */
const bool Time::operator ==(const Time &other) const {
	return impl->ms == other.impl->ms;
}

/**
 * @return Returns true if this object and \em other have different times, false otherwise.
 */
const bool Time::operator !=(const Time &other) const {
	return !(*this == other);
}

/**
 * @return Returns true if this object's time is before \em other, false otherwise.
 */
const bool Time::operator <(const Time &other) const {
	return impl->ms < other.impl->ms;
}

/**
 * @return Returns true if this object's time is before or equal to \em other, false otherwise.
 */
const bool Time::operator <=(const Time &other) const {
	return impl->ms <= other.impl->ms;
}

/**
 * @return Returns true if this object's time is after \em other, false otherwise.
 */
const bool Time::operator >(const Time &other) const {
	return impl->ms > other.impl->ms;
}

/**
 * @return Returns true if this object's time is after or equal to \em other, false otherwise.
 */
const bool Time::operator >=(const Time &other) const {
	return impl->ms >= other.impl->ms;
}

/**
 * Adds the time from \em other to this time. If the new time would be
 * later than midnight then the time wraps round.
 */
Time & Time::operator +=(const Time & other) {
	*this = *this + other;
	return *this;
}

/**
 * Subtracts the time from \em other from this time. If the new time would be
 * earlier than midnight then the time wraps round.
 */
Time & Time::operator -=(const Time & other) {
	*this = *this - other;
	return *this;
}

/**
 * Adds the two Time objects together to produce a new Time object. If the new time would be
 * later than midnight then the time wraps round.
 * \code
 * Time time(20,0); // 8pm
 * Time offset1 = Time::hour(2);
 * Time offset2 = Time::hour(5);
 *
 * Time result;
 *
 * result = time+offset1; // Time object set to 22:00:00:000
 * result = time+offset2; // Time object set to 01:00:00:000
 * \endcode
 */
Time operator +(const Time &t1, const Time &t2)
{
	int ms = t1.impl->ms + t2.impl->ms;
	while (ms >= Time::MS_PER_DAY)
		ms %= Time::MS_PER_DAY;

	Time t;
	t.set(ms);
	return t;
}

/**
 * Subtracts the Time object \em t2 from \em t1 to produce a new Time object. If the new time would be
 * before midnight then the time wraps round.
 * \code
 * Time time(5,0); // 5am
 * Time offset1 = Time::hour(2);
 * Time offset2 = Time::hour(7);
 *
 * Time result;
 *
 * result = time-offset1; // Time object set to 03:00:00:000 (3am)
 * result = time-offset2; // Time object set to 22:00:00:000 (10pm)
 * \endcode
 */
Time operator-(const Time &t1, const Time & t2) {
	int ms = t1.impl->ms - t2.impl->ms;
	if (ms < 0) ms = Time::MS_PER_DAY + ms;

	Time t;
	t.set(ms);
	return t;
}

/**
 * Allows an instance of Time to be written to the ostream and returns a reference to the ostream.
 */
std::ostream & operator<<(std::ostream & out, const Time & t) {
	out << "Time [" << &t << "] " << t.toString();
	return out;
}

} /* namespace prism */
