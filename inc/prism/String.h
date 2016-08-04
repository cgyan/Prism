/*
 * String.h
 * v0.1
 *
 *  Created on: Jul 11, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_STRING_H_
#define PRISM_STRING_H_

#include <prism/Char>
#include <ostream>
#include <string>
#include <initializer_list>
#include <prism/Iterator>
#include <prism/Vector>

namespace prism {

/******************************************************************************
 * StringData
 *****************************************************************************/
/*! \cond DO_NOT_DOCUMENT */
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
	String(const char * str);
	String(const std::string & str);
	String(const char c);
	String(const int size, const char c);
	String(const String &copy);
	virtual ~String();

	String &		append(const String & str);
	String & 		append(const char c);
	String & 		append(const char *str);
	const char &	at(const int index) const;
	iterator		begin();
	const_iterator	begin() const;
	const int 		capacity() const;
	const_iterator	constBegin() const;
	const char *	constData() const;
	const_iterator	constEnd() const;
	void			chop(const int num);
	const bool		contains(const String & str) const;
	const bool		contains(const char c) const;
	const int		count(const char c) const;
	const int		count(const String & str) const;
	void			clear();
	char *			data();
	const char *	data() const;
	iterator		end();
	const_iterator	end() const;
	const bool		endsWith(const String & str) const;
	const bool		endsWith(const char c) const;
	String &		fill(const char c, const int size=-1);
	const int		indexOf(const String & str, const int from=0) const;
	const int		indexOf(const char c, const int from=0) const;
	String &		insert(const int position, const String & str);
	String &		insert(const int position, const char c);
	String &		insert(String::iterator insertBefore, const String & str);
	String &		insert(String::iterator insertBefore, const char c);
	const bool		isEmpty() const;
	const int		lastIndexOf(const char c, const int from=-1) const;
	const int		lastIndexOf(const String & str, const int from=-1) const;
	const int 		length() const;
	String &		prepend(const String & str);
	String & 		prepend(const char c);
	String & 		prepend(const char *str);
	void			push_back(const String & str);
	void			push_back(const char c);
	void			push_front(const String & str);
	void			push_front(const char c);
	String &		remove(const int position, const int nCharsToRemove);
	String &		remove(const char c);
	String &		remove(const String & str);
	String			repeated(int nTimes) const;
	String &		replace(const int position, const int nCharsToReplace, const String & newStr);
	String & 		replace(const int position, const int nCharsToReplace, const char c);
	String &		replace(String::iterator itBegin, String::iterator itEnd, const String & str);
	String &		replace(const String & oldStr, const String & newStr);
	String &		replace(const String & oldStr, const char c);
	String &		replace(const char oldc, const String & newStr);
	String &		replace(const char oldc, const char newc);
	void 			reserve(const int newCapacity);
	void			resize(const int newSize);
	String &		setNum(const int n);
	String &		setNum(const unsigned int n);
	String &		setNum(const long n);
	String &		setNum(const unsigned long n);
	String &		setNum(const float n, const int precision=6);
	String &		setNum(const double n, const int precision=6);
	String			simplified() const;
	const int 		size() const;
	Vector<String>	split(const String & delimeter) const;
	Vector<String>	split(const char delimeter) const;
	void			squeeze();
	const bool		startsWith(const String & str) const;
	const bool		startsWith(const char c) const;
	String			sub(const int startChar, int size=-1) const;
	String			sub(String::iterator first, String::iterator last) const;
	const double	toDouble() const;
	const float		toFloat() const;
	const int		toInt() const;
	String			toLower() const;
	std::string		toStdString() const;
	String			toUpper() const;
	String			trimmed() const;

	char & 			operator[](const int index);
	const char &	operator[](const int index) const;
	String &		operator=(const String &other);
	String &		operator=(const char * other);
	String &		operator=(const char c);
	String &		operator+=(const String & other);
	String &		operator+=(const char * other);
	String &		operator+=(const char c);

	// static
	static String	fromCharArray(const char * str);
	static String	fromStdString(const std::string & str);
	static String	number(const int n);
	static String	number(const unsigned int n);
	static String	number(const long n);
	static String	number(const unsigned long n);
	static String	number(const float n, const int precision=6);
	static String	number(const double n, const int precision=6);

	// related non-members
	friend const bool		operator==(const String & str1, const String & str2);
	friend const bool		operator!=(const String & str1, const String & str2);
	friend const String		operator+(const String & str1, const String & str2);
	friend const String		operator+(const String & str1, const char * str2);
	friend const String		operator+(const char * str1, const String & str2);
	friend const String		operator+(const char c, const String & str);
	friend const String		operator+(const String & str, const char c);
	friend std::ostream & 	operator<<(std::ostream & out, const String &s);

private:
	const bool 	rangeCheck(const int index) const;
};

} /* namespace prism */

#endif /* PRISM_STRING_H_ */
