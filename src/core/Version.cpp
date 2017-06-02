/*
 * Version.cpp
 * v1
 *
 *  Created on: Oct 13, 2016
 *      Author: iainhemstock
 */

#include <prism/Version>
#include <initializer_list>

namespace prism {

//================================================================================
// VersionData
//================================================================================
struct VersionData {
	int 	m_major;
	int	 	m_minor;
	int 	m_patch;
	String 	m_name;

	/**
	 *
	 */
	VersionData()
	: m_major(0),
	  m_minor(0),
	  m_patch(0),
	  m_name()
	{}

	/**
	 *
	 */
	VersionData(const int major, const int minor, const int patch, const String& name)
	: m_major(major),
	  m_minor(minor),
	  m_patch(patch),
	  m_name(name)
	{}
};
//================================================================================
// Version
//================================================================================
/**
 *
 */
Version::
Version()
: d(new VersionData)
{}

/**
 *
 */
Version::
Version(const int major, const int minor, const int patch, const String& name)
: d(new VersionData(major,minor,patch,name))
{}

/**
 *
 */
Version::
Version(const Version& copy)
: d(copy.d)
{}

/**
 *
 */
Version&
Version::
operator =(const Version& rhs) {
	if (*this != rhs)
		d = rhs.d;
	return *this;
}

/**
 *
 */
Version::~Version()
{}

/**
 * Compares the major, minor and patch numbers.
 * Returns a negative number if \em *this is less than \em other.
 * Returns 0 if \em *this is equal to \em other.
 * Returns a positive number (greater than 0) if \em *this is greater than \em other.
 */
const int
Version::
compare(const Version& other) const {
	if (this->major() != other.major())
		return this->major() - other.major();
	else if (this->minor() != other.minor())
		return this->minor() - other.minor();
	else if (this->patch() != other.patch())
		return this->patch() - other.patch();
	return 0;
}

/**
 *
 */
const int
Version::
major() const
{ return d->m_major; }

/**
 *
 */
const int
Version::
minor() const
{ return d->m_minor; }

/**
 *
 */
const int
Version::
patch() const
{ return d->m_patch; }

/**
 *
 */
const String
Version::
name() const
{ return d->m_name; }

/**
 *
 */
const String
Version::
string() const {
	String s;
	s += String::number(d->m_major);
	s += ".";
	s += String::number(d->m_minor);
	s += ".";
	s += String::number(d->m_patch);
	if (!d->m_name.isEmpty()) {
		s += ".";
		s += d->m_name;
	}

	return s;
}

/**
 *
 */
const bool
operator==(const Version& lhs, const Version& rhs) {
	return lhs.compare(rhs) == 0;
}

/**
 *
 */
const bool
operator!=(const Version& lhs, const Version& rhs)
{ return !(lhs == rhs); }

/**
 *
 */
const bool
operator<(const Version& lhs, const Version& rhs) {
	return lhs.compare(rhs) < 0;
}

/**
 *
 */
const bool
operator<=(const Version& lhs, const Version& rhs) {
	return lhs < rhs || lhs == rhs;
}

/**
 *
 */
const bool
operator>(const Version& lhs, const Version& rhs) {
	return lhs.compare(rhs) > 0;
}

/**
 *
 */
const bool
operator>=(const Version& lhs, const Version& rhs) {
	return lhs > rhs || lhs == rhs;
}



} // end namespace prism
