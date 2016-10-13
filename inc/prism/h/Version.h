/*
 * Version.h
 * v1
 *
 *  Created on: Oct 13, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_VERSION_H_
#define PRISM_VERSION_H_

#include <prism/h/SharedPointer.h>
#include <prism/h/String.h>

namespace prism {

struct VersionData;

class Version {
private:
	SharedPointer<VersionData> d;
public:
	Version();
	Version(const int major, const int minor=0, const int patch=0, const String& name="");
	Version(const Version& copy);
	Version& operator=(const Version& rhs);
	~Version();

	const int				compare(const Version& other) const;
	const int 				major() const;
	const int 				minor() const;
	const String 			name() const;
	const int 				patch() const;
	const String			string() const;

	friend const bool 		operator==(const Version& lhs, const Version& rhs);
	friend const bool 		operator!=(const Version& lhs, const Version& rhs);
	friend const bool 		operator<(const Version& lhs, const Version& rhs);
	friend const bool 		operator<=(const Version& lhs, const Version& rhs);
	friend const bool 		operator>(const Version& lhs, const Version& rhs);
	friend const bool 		operator>=(const Version& lhs, const Version& rhs);

	friend std::ostream&	operator<<(std::ostream& out, const Version& v)
	{ return out << v.string(); }
};

} // end namespace prism



#endif /* PRISM_VERSION_H_ */
