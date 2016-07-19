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
	String(const Char & c);
	String(const int size, const char c);
	String(const String &copy);
	virtual ~String();

	String &		append(const String & str);
	String & 		append(const char c);
	String & 		append(const char *str);
	char &			at(const int index);
	const char &	at(const int index) const;
	iterator		begin();
	const_iterator	begin() const;
	const int 		capacity() const;
	const_iterator	cbegin() const;
	const_iterator	cend() const;
	void			chop(const int num);
	const bool		contains(const String & str) const;
	const bool		contains(const char c) const;
	const int		count(const char c) const;
	void			clear();
	char *			data();
	const char *	data() const;
	iterator		end();
	const_iterator	end() const;
	const bool		endsWith(const String & str) const;
	const bool		endsWith(const char c) const;
	String &		fill(const char c, const int size=-1);
//	const int		firstIndexOf(const String & str, const int from=0) const;
	const int		firstIndexOf(const char c, const int from=0) const;
	String &		insert(const int position, const String & str);
	String &		insert(const int position, const char c);
	String &		insert(String::iterator insertBefore, const String & str);
	String &		insert(String::iterator insertBefore, const char c);
	const bool		isEmpty() const;
	const int		lastIndexOf(const char c, const int from=-1) const;
	const int 		length() const;
	char & 			operator[](const int index);
	const char &	operator[](const int index) const;
	String &		operator=(const String &other);
	String &		operator+=(const String & other);
	String &		prepend(const String & str);
	String & 		prepend(const char c);
	String & 		prepend(const char *str);
	void			push_back(const String & str);
	void			push_back(const char c);
	void			push_front(const String & str);
	void			push_front(const char c);
	String &		replace(const int position, const int nChars, const String & str);
	void 			reserve(const int newCapacity);
	void			resize(const int newSize);
	const int 		size() const;
	const bool		startsWith(const String & str) const;
	const bool		startsWith(const char c) const;
	String			sub(const int startChar, int size=-1) const;
	String			sub(String::iterator first, String::iterator last) const;
	const int		toInt() const;
	String			toLower() const;
	std::string		toStdString() const;
	String			toUpper() const;

	// static
	static String	fromCharArray(const char * str);
	static String	fromStdString(const std::string & str);
//	static String	number(const int n);

	// related non-members
	friend const bool		operator==(const String & str1, const String & str2);
	friend const bool		operator!=(const String & str1, const String & str2);
	friend String			operator+(const String & str1, const String & str2);
	friend String			operator+(const String & str1, const char * str2);
	friend String			operator+(const char * str1, const String & str2);
	friend String			operator+(const char c, const String & str);
	friend String			operator+(const String & str, const char c);
	friend std::ostream & 	operator<<(std::ostream & out, const String &s);

private:
	const bool 	rangeCheck(const int index) const;
	void		convertCharToUpper(char &c);
};

} /* namespace prism */

#endif /* PRISM_STRING_H_ */