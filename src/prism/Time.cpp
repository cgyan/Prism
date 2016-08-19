/*
 * Time.cpp
 * v1
 *
 *  Created on: Aug 15, 2016
 *      Author: iainhemstock
 */

#include <prism/Time>
#include <chrono>

namespace prism {

/**
 * Constructs a Time object set to midnight i.e. hour=min=sec=msec=0.
 */
Time::Time()
	: m_ms(0)
{

}

/**
 * Constructs a Time object set to \em hour, \em min, \em sec and \em msec.
 */
Time::Time(const int hour, const int min, const int sec, const int msec)
	: m_ms(hour*MS_PER_HOUR + min*MS_PER_MINUTE + sec*MS_PER_SECOND + msec)
{

}

/**
 * Destroys this Time object.
 */
Time::~Time() {

}

/**
 * @return Returns the hour part of the time (0-23).
 */
const int Time::hour() const {
	return m_ms / MS_PER_HOUR;
}

/**
 * @return Returns the minute part of the time (0-59).
 */
const int Time::min() const {
	return (m_ms % MS_PER_HOUR) / MS_PER_MINUTE;
}

/**
 * @return Returns the millisecond part of the time (0-999).
 */
const int Time::msec() const {
	return m_ms % 1000;
}

/**
 * Resets the time back to midnight i.e. hour=min=sec=msec=0.
 */
void Time::reset()
{
	m_ms = 0;
}

/**
 * @return Returns the second part of the time (0-59).
 */
const int Time::sec() const {
	return (m_ms / MS_PER_SECOND) % SECS_PER_MINUTE;
}

/**
 * @return Returns a string representation of the time in the form 00:00:00:000.
 */
String Time::toString() const {
	int h = hour();
	int m = min();
	int s = sec();
	int ms = msec();
	String ret;
	ret.reserve(12);

	if (h < 10) ret += String("0");
	ret += String::number(h);
	ret += String(":");
	if (m < 10) ret += String("0");
	ret += String::number(m);
	ret += String(":");
	if (s < 10) ret += String("0");
	ret += String::number(s);
	ret += String(":");
	if (ms < 100) ret += String("0");
	if (ms < 10) ret += String("0");
	ret += String::number(ms);

	return ret;
}

/**
 * @return Returns a Time object set to the current time as read from the system clock.
 */
Time Time::currentTime() {
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

	Time ret;
	ret.m_ms = msSinceMidnight.count();
	return ret;
}

/**
 * Static function that creates a Time object set to \em nHours.
 */
Time Time::hours(const int nHours) {
	return Time(nHours,0);
}

/**
 * @return Returns the number of hours between \em time and this object's time.
 */
const int Time::hoursTo(const Time & time) const {
	return time.m_ms/MS_PER_HOUR - this->m_ms/MS_PER_HOUR;
}

/**
 * Static function that creates a Time object set to \em nMins.
 */
Time Time::mins(const int nMins) {
	return Time(0,nMins);
}

/**
 * @return Returns the number of minutes between \em time and this object's time.
 */
const int Time::minsTo(const Time & time) const {
	return time.m_ms/MS_PER_MINUTE - this->m_ms/MS_PER_MINUTE;
}

/**
 * Static function that creates a Time object set to \em nMsecs.
 */
Time Time::msecs(const int nMsecs) {
	return Time(0,0,0, nMsecs);
}

/**
 * @return Returns the number of milliseconds between \em time and this object's time.
 */
const int Time::msecsTo(const Time & time) const {
	return time.m_ms-this->m_ms;
}

/**
 * Static function that creates a Time object set to \em nSsecs.
 */
Time Time::secs(const int nSecs) {
	return Time(0,0,nSecs);
}

/**
 * @return Returns the number of seconds between \em time and this object's time.
 */
const int Time::secsTo(const Time & time) const {
	return time.m_ms/MS_PER_SECOND - this->m_ms/MS_PER_SECOND;
}

/**
 * Sets this Time object to \em hour, \em min, \em sec and \em msec.
 */
void Time::set(const int hour, const int min, const int sec, const int msec) {
	m_ms = hour*MS_PER_HOUR + min*MS_PER_MINUTE + sec*MS_PER_SECOND + msec;
}

/**
 * @return Returns true if this object and \em other have the same time, false otherwise.
 */
const bool Time::operator ==(const Time &other) const {
	return m_ms == other.m_ms;
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
	return m_ms < other.m_ms;
}

/**
 * @return Returns true if this object's time is before or equal to \em other, false otherwise.
 */
const bool Time::operator <=(const Time &other) const {
	return m_ms <= other.m_ms;
}

/**
 * @return Returns true if this object's time is after \em other, false otherwise.
 */
const bool Time::operator >(const Time &other) const {
	return m_ms > other.m_ms;
}

/**
 * @return Returns true if this object's time is after or equal to \em other, false otherwise.
 */
const bool Time::operator >=(const Time &other) const {
	return m_ms >= other.m_ms;
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
	int ms = t1.m_ms + t2.m_ms;
	while (ms >= Time::MS_PER_DAY)
		ms %= Time::MS_PER_DAY;

	Time t;
	t.m_ms = ms;
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
	int ms = t1.m_ms - t2.m_ms;
	if (ms < 0) ms = Time::MS_PER_DAY + ms;

	Time t;
	t.m_ms = ms;
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
