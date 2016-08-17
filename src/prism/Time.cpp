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
 * Constructs an empty Time object set to midnight.
 */
Time::Time()
	: m_ms(0)
{

}

/**
 *
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
 *
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
 * Resets the time back to midnight i.e. hour=min=sec=ms=0.
 */
void Time::reset()
{
	m_ms = 0;
}

/**
 * @return Returns the second part of the time (0-59).
 */
const int Time::sec() const {
	return (m_ms / MS_PER_SECOND) % SEC_PER_MINUTE;
}

/**
 *
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
 *
 */
std::ostream & operator<<(std::ostream & out, const Time & t) {
	out << "Time [" << &t << "] ms since midnight: " << t.m_ms;
	return out;
}

} /* namespace prism */
