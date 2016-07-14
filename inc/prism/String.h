/*
 * String.h
 * v0.1
 *
 *  Created on: Jul 11, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_STRING_H_
#define PRISM_STRING_H_

#include <ostream>
#include <string>
#include <initializer_list>
#include <prism/Iterator>

namespace prism {

/******************************************************************************
 * StringData
 *****************************************************************************/
/*! \ifcond DO_NOT_DOCUMENT */
struct StringData {
	struct memory {
		char * start; 	// the start of the memory
		char * end; 	// one position after the last value
		char * finish;	 	// the end of the storage
		int exponent;
		memory() : start(0), end(0), finish(0), exponent(2) {}
		~memory() { delete [] start; start=0; end=0; finish=0; }
	};
	memory storage;
};
// \endcond
/******************************************************************************
 * String
 *****************************************************************************/
/*! This is the main description of the class String.
 */
class String {
private:
	StringData * d;

public:
	typedef RandomAccessIterator<char> 			iterator;
	typedef RandomAccessConstIterator<char>		const_iterator;
	typedef typename iterator::reference		reference;
	typedef typename const_iterator::reference	const_reference;
	typedef typename iterator::pointer			pointer;
	typedef typename const_iterator::pointer	const_pointer;
	typedef typename iterator::value_type		value_type;
	typedef typename iterator::difference_type	difference_type;
	typedef int									size_type;

public:
	String();
//	String(const char * string);
	String(const std::string & str);
	String(const int size, const char c);
	String(const String &copy);
	virtual ~String();

	char &			at(const int index);
	const char &	at(const int index) const;
	iterator		begin();
	const_iterator	begin() const;
	const int 		capacity() const;
	const_iterator	cbegin() const;
	const int		count(const char c) const;
	void			clear();
	char *			data();
	const char *	data() const;
	iterator		end();
	const_iterator	end() const;
	const bool		endsWith(const char c) const;
	String &		fill(const char c, const int size=-1);
	const int		indexOf(const char c, const int from=0) const;
	const bool		isEmpty() const;
	const int 		length() const;
	void 			reserve(const int newCapacity);
	void			resize(const int newSize);
	const int 		size() const;
	std::string		toStdString() const;

	// related non-members
	char & 			operator[](const int index);
	const char &	operator[](const int index) const;
	String &		operator=(const String &other);

	friend std::ostream & operator<<(std::ostream & out, const String &s);

private:
	const bool rangeCheck(const int index) const;
};

} /* namespace prism */

#endif /* PRISM_STRING_H_ */
