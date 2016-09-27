/*
 * String.cpp
 * v1
 *
 *  Created on: Jul 11, 2016
 *      Author: iainhemstock
 */

#include <prism/h/String.h>
#include <prism/h/Char.h>
#include <prism/h/algorithms.h>
#include <prism/h/OutOfBoundsException.h>
#include <iostream>
#include <sstream>
#include <string>

namespace prism {

/**
 * Creates a new empty string i.e. ""
 */
String::String()
	: d(new StringData)
{}

/**
 * Creates a new string from the c-style string \em str. \n
 * In C a character array must be terminated with the null character
 * \code
 * char cs[15] = {'H', 'e', 'l', 'l', 'o', ' ', 'c', ' ', 's', 't', 'r', 'i', 'n', 'g', '\0'};
 * String s(cs);
 * \endcode
 * But if following the rule of array initialisation then the above can be written as
 * \code
 * char cs[] = "Hello c string";
 * String s(cs);
 * \endcode
 * Note that the compiler silently adds the null terminator to the end of the string above.
 */
String::String(const char * str)
	: d(new StringData)
{
	int size = -1;
	while (true) {
		if(str[++size] == '\0') break;
	}

	this->resize(size);
	prism::copy(str, str+size, this->d->storage.start);
}

/**
 * Creates a new string from a std::string.
 */
String::String(const std::string & str)
	: d(new StringData)
{
	int size = str.size();
	resize(size);
	prism::copy(str.begin(), str.end(), d->storage.start);
}

/**
 * Creates a string of size 1 initialised to the Char \em c.
 */
String::String(const char c)
	: d(new StringData)
{
	resize(1);
	prism::fill_n(d->storage.start, 1, c);
}

/**
 * Creates a string filled with \em size amount of the char \em c.
 */
String::String(const int size, const char c)
	: d(new StringData)
{
	reserve(size);
	prism::fill_n(d->storage.start, size, c);
	d->storage.end = d->storage.start + size;
}

/**
 * Creates a copy of this string.
 */
String::String(const String &copy)
	: d(new StringData)
{
	int size = copy.size();
	reserve(size);
	prism::copy(copy.begin(), copy.end(), d->storage.start);
	this->d->storage.end = this->d->storage.start + size;
}

/**
 * Destroys this string.
 */
String::~String() {
	delete d;
}

/**
 * @return Returns a reference to this string with \em str appended to the end.
 */
String & String::append(const String & str) {
	return insert(end(), str);
}

/**
 * @return Returns a reference to this string with \em c appended to the end.
 */
String & String::append(const char c) {
	return insert(end(), c);
}

/**
 * @return Returns a reference to this string with \em str appended to the end.
 */
String & String::append(const char * str) {
	return insert(end(), String(str));
}

/**
 * @return Returns a const reference to the char at \em index.
 * @throw Throws an OutOfBoundsException if \em index is out of bounds.
 */
const char & String::at(const int index) const {
	if (!rangeCheck(index))
		throw OutOfBoundsException(index);

	return this->operator [](index);
}

/**
 * @return Returns an iterator to the first character in the string.
 */
typename String::iterator String::begin() {
	return iterator(d->storage.start);
}

/**
 * @return Returns a const iterator to the first character in the string.
 */
typename String::const_iterator String::begin() const {
	return const_iterator(d->storage.start);
}

/**
 * @ return Returns the capacity of the underlying data storage.
 */
const int String::capacity() const {
	return d->storage.finish - d->storage.start;
}

/**
 * @return Returns a const iterator to the first character in the string.
 */
typename String::const_iterator String::constBegin() const {
	return const_iterator(d->storage.start);
}

/**
 * @return Returns a const pointer to the underlying data array.
 */
const char * String::constData() const {
	return d->storage.start;
}

/**
 * @return Returns a const iterator to the imaginary position one after the last character.
 */
typename String::const_iterator String::constEnd() const {
	return const_iterator(d->storage.end);
}

/**
 * Chops off (i.e. removes) \em num amount of characters from the end of the string.
 */
void String::chop(const int num) {
	d->storage.end -= num;
}

/**
 * @return Returns true if this string contains an occurrence of the String \em str.
 */
const bool String::contains(const String & str) const {
	const_iterator it = prism::search(begin(), end(), str.begin(), str.end());
	return (it == end()) ? false : true;
}

/**
 * @return Returns true if this string contains an occurrence of the char \em c.
 */
const bool String::contains(const char c) const {
	const_iterator it = prism::find(begin(), end(), c);
	return (it == end()) ? false : true;
}

/**
 * @return Returns the number of occurrences of the char \em c.
 */
const int String::count(const char c) const {
	return prism::count(d->storage.start, d->storage.end, c);
}

/**
 * @return Returns the number of (potentially overlapping) occurrences of the string \em str.
 */
const int String::count(const String & str) const {
	int ret = 0;

	const_iterator bit = constBegin();
	const_iterator eit = constEnd();

	while (bit != eit) {
		const_iterator result = prism::search(bit, eit, str.begin(), str.end());
		if (result != eit) {
			++ret;
			bit = result + 1;
		}
		else ++bit;
	}
	return ret;
}

/**
 * Clears the content of the string making size() = 0.
 */
void String::clear() {
	d->storage.end = d->storage.start;
}

/**
 * @return Returns a pointer to the underlying data array.
 */
char * String::data() {
	return d->storage.start;
}

/**
 * @return Returns a const pointer to the underlying data array.
 */
const char * String::data() const {
	return d->storage.start;
}

/**
 * @return Returns an iterator to the imaginary position after the last character.
 */
typename String::iterator String::end() {
	return iterator(d->storage.end);
}

/**
 * @return Returns a const iterator to the imaginary position after the last character.
 */
typename String::const_iterator String::end() const {
	return const_iterator(d->storage.end);
}

/**
 *
 */
const bool String::endsWith(const String & str) const {
	const_iterator bit = end() - str.size();
	const_iterator it = prism::search(bit, end(), str.begin(), str.end());

	if (it == end()) return false;
	else return true;
}

/**
 * @return Returns true if the string's last character is \em c, false otherwise.
 */
const bool String::endsWith(const char c) const {
	return at(size()-1) == c;
}

/**
 * Sets every character to \em c. If \em size is not equal to -1 (the deafult)
 * then the string gets resized to \em size first.
 */
String & String::fill(const char c, const int size) {
	if (size >= 0)
		resize(size);

	prism::fill(d->storage.start, d->storage.end, c);

	return *this;
}

/**
 * @return Returns the position of the first occurrence of \em str in the string searching forwards
 * from the position \em from (0 by default). If there is no occurrence then -1 is returned instead.
 */
const int String::indexOf(const String & str, const int from) const {
	int ret = -1;

	String::const_iterator result = prism::search(d->storage.start + from, d->storage.end,
													str.d->storage.start, str.d->storage.end);
	if (result != end())
		ret = result - d->storage.start;

	return ret;
}

/**
 * @return Returns the position of the first occurrence of \em c in the string searching forwards
 * from the position \em from (0 by default). If there is no occurrence then -1 is returned instead.
 */
const int String::indexOf(const char c, const int from) const {
	int ret = -1;

	String::const_iterator it = prism::find(d->storage.start + from, d->storage.end, c);
	if (it != end())
		ret = it - d->storage.start;

	return ret;

}

/**
 * Inserts a copy of \em str starting at the \em position index.
 * @return Returns a reference to this string.
 */
String & String::insert(const int position, const String & str) {
	iterator it = begin() + position;
	return insert(it, str);
}

/**
 *
 */
String & String::insert(const int position, const char c) {
	iterator it = begin() + position;
	return insert(it, String(c));
}

/**
 * Inserts a copy of \em str one character before the position represented by \em insertBefore.
 * @return Returns a reference to this string.
 */
String & String::insert(String::iterator insertBefore, const String & str) {

	int cap = capacity();
	int thisSize = size();
	int insertIndex = insertBefore - begin();

	// 1: increase capacity if necessary
	int reserveSize = thisSize + str.size();
	if (reserveSize > cap) {
		// if the capacity == 0 then set new capacity to the size of the new string
		// if the capacity > 0 then set the the new capacity to the size of the new
		// string multiplied by the exponent
		if (cap > 0)
			reserveSize = reserveSize * d->storage.exponent;
		reserve(reserveSize);
	}

	d->storage.end = d->storage.start + thisSize + str.size();

	// 2: if the string isn't empty shift up the chars after the
	// insertion point to make room for str.
	if (thisSize > 0)
		prism::copy_backward(d->storage.start+insertIndex,
							 d->storage.start+thisSize,
							 d->storage.end);

	// 3: copy new string in at insertion point
	prism::copy(str.begin(),
				str.end(),
				d->storage.start+insertIndex);


	return *this;
}

/**
 * Inserts a copy of \em c one character before the position represented by \em insertBefore.
 * @return Returns a reference to this string.
 */
String & String::insert(String::iterator insertBefore, const char c) {
	return insert(insertBefore, String(c));
}

/**
 * @return Returns true if the string has no content, false otherwise.
 */
const bool String::isEmpty() const {
	return size() == 0;
}

/**
 * @return Returns the index of the last occurrence of \em str searching backwards from
 * the index position \em from to the first character. \n
 * If \em from is -1 (the default) then the search will begin from the last character and if
 * it is set to -2 then the search begins at the second to last character and so on.
 * If there is no occurrence of \em c then -1 is returned instead.
 */
const int String::lastIndexOf(const String & str, const int from) const {
	int ret = -1;
	const_iterator bit = end() + from;
	const_iterator eit = end() + from + str.size();

	while (bit >= begin()) {
		const_iterator result = prism::search(bit, eit, str.d->storage.start, str.d->storage.end);
		if (result != eit) {
			ret = result - d->storage.start;
			break;
		}
		--bit;
	}

	return ret;
}

/**
 * @return Returns the index of the last occurrence of the char \em c
 * searching backwards from (and including) the position \em from to the first character.
 * If \em from is -1 (the default) then the search will begin from the last character and if
 * it is set to -2 then the search begins at the second to last character and so on.
 * If there is no occurrence of \em c then -1 is returned instead.
 */
const int String::lastIndexOf(const char c, const int from) const {

	const_iterator eit = (from == -1) ? d->storage.end : d->storage.end + from + 1;
	const_iterator result = prism::find_last(begin(), eit, c);

	return (result == 0) ? -1 : result - d->storage.start;
}

/**
 * @return Returns the length of the string. This method is identical to size().
 */
const int String::length() const {
	return d->storage.end - d->storage.start;
}

/**
 * @return Returns a reference to this string with \em str prepended to the beginning.
 */
String & String::prepend(const String & str) {
	return insert(begin(), str);
}

/**
 * @return Returns a reference to this string with \em c prepended to the beginning.
 */
String & String::prepend(const char c) {
	return insert(begin(), String(c));
}

/**
 * @return Returns a reference to this string with \em str prepended to the beginning.
 */
String & String::prepend(const char * str) {
	return insert(begin(), String(str));
}

/**
 *
 */
void String::push_back(const String & str) {
	append(str);
}

/**
 *
 */
void String::push_back(const char c) {
	append(c);
}

/**
 *
 */
void String::push_front(const String & str) {
	prepend(str);
}

/**
 *
 */
void String::push_front(const char c) {
	prepend(c);
}

/**
 * Performs a range check on \em index to ensure that 0 <= index < size().
 * @returns Returns true if \em index is within bounds, false otherwise.
 */
const bool String::rangeCheck(const int index) const {
	if (index < 0 || index >= size()) return false;
	return true;
}

/**
 * Removes \em nCharsToRemove starting from \em position (0-based).
 * @return Returns a reference to this string.
 */
String & String::remove(const int index, const int nCharsToRemove) {

	prism::copy(begin()+index+nCharsToRemove, end(), begin()+index);
	resize(size() - nCharsToRemove);

	return *this;
}

/**
 * Removes all occurrences of the Char \em c.
 * @return Returns a reference to this string.
 */
String & String::remove(const char c) {
	replace(c, "");
	return *this;
}

/**
 * Removes all occurrences of \em str.
 * @return Returns a reference to this string.
 */
String & String::remove(const String & str) {
	replace(str, "");
	return *this;
}

/**
 * @return Returns a new string which is composed of this string repeated \em nTimes.
 */
String String::repeated(int nTimes) const {
	String s;
	s.resize(size() * nTimes);

	while (--nTimes >= 0)
		prism::copy(begin(), end(), s.begin() + size()*nTimes);

	return s;
}

/**
 * Replaces \em nChars of characters starting at \em position (0-based) with \em str.
 * \code
 * // starting at position 5, replace 6 characters with the string "Bona"
 *
 * String s("Cala Millor in Majorca!");
 * s.replace(5, 6, "Bona");
 *
 * cout << s1; // outputs: "Cala Bona in Majorca!"
 * \endcode
 * @return Returns a reference to this string.
 */
String & String::replace(const int position, const int nCharsToReplace, const String & newStr) {

	int oldSize = size();

	// if new string is less than chars replaced
	// then proceeding characters need to shuffle down
	if (newStr.size() < nCharsToReplace) {
		String::iterator bit = this->begin() + position + nCharsToReplace;
		String::iterator eit = this->end();
		String::iterator obit = this->begin() + position + newStr.size();

		prism::copy(bit, eit, obit);
		prism::copy(newStr.begin(), newStr.end(), this->begin()+position);
		this->resize(oldSize - nCharsToReplace + newStr.size());
	}
	// else if new string is more than chars replaced
	// then the string needs to be resized to accommodate the new string
	else {
		this->resize(this->size() - nCharsToReplace + newStr.size());

		String::iterator bit = this->begin() + position + nCharsToReplace;
		String::iterator eit = this->begin() + oldSize;
		String::iterator oeit = this->end();

		prism::copy_backward(bit, eit, oeit);
		prism::copy(newStr.begin(), newStr.end(), this->begin() + position);
	}

	return *this;
}

/**
 * Replaces \em nCharsToReplace of characters starting at \em position (0-based) with \em c.
 */
String & String::replace(const int position, const int nCharsToReplace, const char c) {
	return replace(position, nCharsToReplace, String(c));
}

/**
 * Replaces the characters in the range \em [begin/end] with \em str. \n
 * The characters replaced are all the characters between \em begin and \em end including \em begin
 * but not \em end.
 * \code
 	String s("Cala Bona in Majorca");
	s.replace(s.begin()+5, s.begin()+9, "Millor");

	cout << s; // outputs: "Cala Millor in Majorca!"
 * \endcode
 * @return Returns a reference to this string.
 */
String & String::replace(String::iterator itBegin, String::iterator itEnd, const String & str) {
	return replace(itBegin - this->begin(), itEnd-itBegin, str);
}

/**
 * Replaces each occurrence of \em oldStr with \em newStr.
 * \code
 * String s("I see sea ships on the sea shore");
 * s.replace("sea", "ocean");

 * cout << s; // outputs: "I see ocean ships on the ocean shore"
 * \endcode
 * @return Returns a reference to this string.
 */
String & String::replace(const String & oldStr, const String & newStr) {
	String::iterator bit = begin();
	String::iterator eit = end();

	while (bit != eit) {
		int bitIndex = bit - begin();

		String::iterator currIt = prism::search(bit, eit, oldStr.begin(), oldStr.end());
		if (currIt == eit) break;
		else replace(currIt-begin(), oldStr.size(), newStr);

		// in case the iterators have been invalidated through reallocation ...
		bit = begin() + bitIndex + 1;
		eit = end();
	}

	return *this;
}

/**
 * Replaces each occurrence of \em oldStr with \em newChar.
 * @return Returns a reference to this string.
 */
String & String::replace(const String & oldStr, const char c) {
	return replace(oldStr, String(c));
}

/**
 * Replaces each occurrence of the char \em c with the string \em newStr.
 * @return Returns a reference to this string.
 */
String & String::replace(const char oldc, const String & newStr) {
	return replace(String(oldc), newStr);
}

/**
 * Replaces each occurrence of the char \em oldChar with the char \em newChar.
 * @return Returns a reference to this string.
 */
String & String::replace(const char oldc, const char newc) {
	return replace(String(oldc), String(newc));
}

/**
 * Reserves enough memory for the string to contain \em newCapacity characters
 * i.e. newCapacity * sizeof(char). The capacity can only grow and will not
 * lessen even if clear() or remove() is called. Only squeeze() can alter the
 * capacity to a lower amount. If \em newCapacity is less than or equal to the
 * current capacity then nothing changes. Any existing characters in the string
 * are not affected by this function.
 */
void String::reserve(const int newCapacity) {
	if (newCapacity <= capacity())
		return;

	char * newStorage = new char[newCapacity];
	int s = size();

	prism::copy(d->storage.start, d->storage.end, newStorage);

	delete [] d->storage.start;
	d->storage.start = newStorage;
	d->storage.end = d->storage.start + s;
	d->storage.finish = d->storage.start + newCapacity;
}

/**
 * Resizes the string to \em newSize. \n
 * If \em newSize is less than the current size then those characters are
 * removed from the end. If \em newSize is greater than the current size
 * then those new characters will be initialised to default constructed values i.e. " ".
 * The capacity will remain unchanged if the string is resized downwards but
 * may increase as necessary if the string is resized upwards.
 */
void String::resize(const int newSize) {
	if (newSize == size())
		return;
	if (newSize < size()) {
		d->storage.end = d->storage.start + newSize;
		return;
	}

	int oldSize = size();

	if (newSize > capacity()) {
		reserve(newSize);
	}

	prism::fill(d->storage.start+oldSize, d->storage.start+newSize, char(' '));
	d->storage.end = d->storage.start + newSize;
}

/**
 * Converts \em n to a string and sets it as the content of this string.
 * @return Returns a reference to this string.
 */
String & String::setNum(const int n) {
	std::ostringstream ss;
	ss << n;
	std::string stdStr = ss.str();
	resize(stdStr.size());
	prism::copy(stdStr.begin(), stdStr.end(), begin());

	return *this;
}

/**
 * This is an overloaded function.
 */
String & String::setNum(const unsigned int n) {
	std::ostringstream ss;
	ss << n;
	std::string stdStr = ss.str();
	resize(stdStr.size());
	prism::copy(stdStr.begin(), stdStr.end(), begin());

	return *this;
}

/**
 * This is an overloaded function.
 */
String & String::setNum(const long n) {
	std::ostringstream ss;
	ss << n;
	std::string stdStr = ss.str();
	resize(stdStr.size());
	prism::copy(stdStr.begin(), stdStr.end(), begin());

	return *this;
}

/**
 * This is an overloaded function.
 */
String & String::setNum(const unsigned long n) {
	std::ostringstream ss;
	ss << n;
	std::string stdStr = ss.str();
	resize(stdStr.size());
	prism::copy(stdStr.begin(), stdStr.end(), begin());

	return *this;
}

/**
 * This is an overloaded function.\n
 * Sets this string to the textual representation of the float \em n set to \em precision (6 by default).
 * @return Returns a reference to this string.
 */
String & String::setNum(const float n, const int precision) {
	std::ostringstream ss;
	ss.precision(precision);
	ss << n;
	std::string stdStr = ss.str();
	resize(stdStr.size());
	prism::copy(stdStr.begin(), stdStr.end(), begin());

	return *this;
}

/**
 * This is an overloaded function.\n
 * Sets this string to the textual representation of the double \em n set to \em precision (6 by default).
 * @return Returns a reference to this string.
 */
String & String::setNum(const double n, const int precision) {
	std::ostringstream ss;
	ss.precision(precision);
	ss << n;
	std::string stdStr = ss.str();
	resize(stdStr.size());
	prism::copy(stdStr.begin(), stdStr.end(), begin());

	return *this;
}

/**
 * Removes all whitespace characters from the start and end of the string and
 * replaces all whitespace between non-whitespace characters with a single space (' ').
 * Whitespace characters are those such that Char::isWhitespace is true. These are space (' '),
 * carriage return ('\\r'), tab ('\\t'), newline ('\\n'), vertical tab ('\\v') and formfeed ('\\f').
 * \code
 * String s("\n\t\t whitespace has\fbeen\vremoved!\n");
 * cout << s.simplified(); // outputs: "whitespace has been removed!"
 * \endcode
 * @return Returns a new string that has all whitespace stripped out and replacing internal whitespace
 * with a single space (' ').
 */
String String::simplified() const {
	String s = this->trimmed();

	iterator it = s.begin();
	while (it != s.end()) {
		if (Char::isWhitespace(*it))
			s.replace(*it, ' ');
		++it;
	}

	return s;
}

/**
 * @return Returns the size of the string. This method is identical to length().
 */
const int String::size() const {
	return d->storage.end - d->storage.start;
}

/**
 * Splits this string into substrings each time \em delimeter occurs.
 * @return Returns a List of strings. If \em delimeter does not occur then a List
 * containing one string (this string) will be returned instead.
 */
List<String> String::split(const char delimeter) const {
	List<String> list;
	const_iterator loopBit = constBegin();
	const_iterator loopEit = constEnd();
	const_iterator rangeBit = constBegin();

	String s;

	// the loop finds all the strings leading up to the last delimeter
	while (loopBit != loopEit) {
		if (*loopBit == delimeter) {
			s.resize(loopBit - rangeBit);
			prism::copy(rangeBit, loopBit, s.begin());
			list.append(s.trimmed());
			rangeBit = loopBit + 1;
		}
		++loopBit;
	}

	// this grabs the section of the string after the last delimeter
	s.resize(loopBit - rangeBit);
	prism::copy(rangeBit, loopBit, s.begin());
	list.append(s.trimmed());


	return list;
}

/**
 * Destroys any unused memory currently held by this string. For example, if the string has a capacity
 * of 10 and a size of 4, squeeze() will release the extra memory of the capacity resulting in a capacity and size of 4.
 * If size() and capacity() are already equal then nothing happens.
 */
void String::squeeze() {
	if (size() == capacity()) return;
	int s = size();

	char * newStorage = new char[s];
	prism::copy(d->storage.start, d->storage.end, newStorage);

	delete [] d->storage.start;
	d->storage.start = newStorage;
	d->storage.end = d->storage.start + s;
	d->storage.finish = d->storage.start + s;
}

/**
 * @return Returns true if the string start with \em str, false otherwise.
 */
const bool String::startsWith(const String & str) const {
	const_iterator eit = begin() + str.size();
	const_iterator it = prism::search(begin(), eit, str.begin(), str.end());

	if (it == eit) return false;
	else return true;
}

/**
 * @return Returns true if the string starts with \em c, false otherwise.
 */
const bool String::startsWith(const char c) const {
	return at(0) == c;
}

/**
 * @return Returns a new string copied from this string starting at \em startIndex
 * for \em nChars characters. If \em nChars is -1 (the default) then
 * the whole string from \em startIndex is copied.
 */
String String::sub(const int startIndex, int nChars) const {

	if ((startIndex == 0 && nChars == -1) ||
			(startIndex == 0 && nChars >= this->size())) {
		return *this;
	}

	char * b = d->storage.start + startIndex;
	if (nChars == -1 || b + nChars > d->storage.end)
		nChars = d->storage.end - b;

	String s;
	s.resize(nChars);
	prism::copy_n(b, nChars, s.d->storage.start);

	return s;
}

/**
 * @return Returns a new string copied from the range \em [first, last]. The
 * range copied is all characters between \em first and \em last, including \em first
 * but not \em last.
 */
String String::sub(iterator first, iterator last) const {
	String s;
	s.resize(last - first);
	prism::copy(first, last, s.begin());

	return s;
}

/**
 * @return Returns the string converted to an \em double.
 */
const double String::toDouble() const {
	std::string s = this->toStdString();
	return std::stod(s);
}

/**
 * @return Returns the string converted to an \em float.
 */
const float String::toFloat() const {
	std::string s = this->toStdString();
	return std::stof(s);
}

/**
 * @return Returns the string converted to an \em int.
 * \code
 * String s("123 Cherry Tree Lane");
 * String sub = s.sub(0,3); // sub == "123"
 * int nextDoor = sub.toInt() + 1;
 *
 * cout << nextDoor; // outputs: 124
 * \endcode
 */
const int String::toInt() const {
	int ret = 0;
	const_iterator bit = begin();

	while (isdigit(*bit)) {
		ret *= 10;
		ret += (int)(*bit-'0');
		++bit;
	}

	return ret;
}

/**
 * @return Returns a copy of this string where each character is lowercase.
 */
String String::toLower() const {
	String s(*this);
	iterator it = s.begin();

	while (it != s.end()) {
		Char c(*it);
		if (c.isLetter() && c.isUpper()) {
			c += 32;
			*it = c.tochar();
		}
		++it;
	}
	return s;
}

/**
 * @return Returns a copy of this string as a std::string.
 */
std::string String::toStdString() const {
	std::string ss;
	ss.reserve(this->size());
	prism::copy(begin(), end(), ss.begin());

	return ss;
}

/**
 * @return Returns a copy of this string where each character is uppercase.
 */
String String::toUpper() const {
	String s(*this);
	iterator it = s.begin();

	while (it != s.end()) {
		Char c(*it);
		if (c.isLetter() && c.isLower()) {
			c -= 32;
			*it = c.tochar();
		}
		++it;
	}
	return s;
}

/**
 * Trims the whitespace from the beginning and the end of the string. Characters which are whitespace
 * are such that Char.isWhitespace() would return true.
 * @return Returns a copy of this string with the whitespace trimmed off. If there is
 * no whitespace to remove then the string is returned unchanged.
 * \code
 * String s("     in the summer     ");
 * cout << s.trimmed(); // outputs: "in the summer"
 * \endcode
 */
String String::trimmed() const {

	const_iterator loopBit = constBegin();
	const_iterator loopEit = constEnd();
	const_iterator rangeBit = constBegin();
	const_iterator rangeEit = constEnd();

	while (loopBit != loopEit) {
		if (!Char::isWhitespace(*loopBit)) {
			rangeBit = loopBit;
			break;
		}
		++loopBit;
	}

	loopBit = constBegin();
	loopEit = constEnd() - 1;

	while (loopEit >= loopBit) {
		if (!Char::isWhitespace(*loopEit)) {
			rangeEit = loopEit + 1;
			break;
		}
		--loopEit;
	}

	String s;
	s.resize(rangeEit - rangeBit);
	prism::copy(rangeBit, rangeEit, s.begin());

	return s;
}

/**
 *
 */
char & String::operator [](const int index) {
	return d->storage.start[index];
}

/**
 *
 */
const char & String::operator [](const int index) const {
	return d->storage.start[index];
}

/**
 *
 */
String & String::operator =(const String & other) {
	if (*this != other) {
		int size = other.size();
		reserve(size);
		prism::copy(other.begin(), other.end(), d->storage.start);
		d->storage.end = d->storage.start + size;
	}

	return *this;
}

/**
 *
 */
String & String::operator =(const char * other) {
	*this = String(other);
	return *this;
}

/**
 *
 */
String & String::operator =(const char c) {
	*this = String(c);
	return *this;
}

/**
 *
 */
String & String::operator +=(const String & other) {
	return insert(end(), other);
}

/**
 *
 */
String & String::operator +=(const char * other) {
	return insert(end(), other);
}

/**
 *
 */
String & String::operator +=(const char c) {
	return insert(end(), c);
}
// ========================================================================
// Static
// ========================================================================
/**
 *
 */
String String::fromCharArray(const char * str) {
	return String(str);
}
/**
 *
 */
String String::fromStdString(const std::string & str) {
	return String(str);
}

/**
 *
 */
String String::number(const int n) {
	String s;
	s.setNum(n);

	return s;
}

/**
 *
 */
String String::number(const unsigned int n) {
	String s;
	s.setNum(n);

	return s;
}

/**
 *
 */
String String::number(const long n) {
	String s;
	s.setNum(n);

	return s;
}

/**
 *
 */
String String::number(const unsigned long n) {
	String s;
	s.setNum(n);

	return s;
}

/**
 *
 */
String String::number(const float n, const int precision) {
	String s;
	s.setNum(n, precision);

	return s;
}

/**
 *
 */
String String::number(const double n, const int precision) {
	String s;
	s.setNum(n, precision);

	return s;
}

/**
 *
 */
const bool operator==(const String & str1, const String & str2) {
	if (str1.length() != str2.length())
		return false;

	return prism::equal(str1.begin(), str1.end(), str2.begin());
}

/**
 *
 */
const bool operator!=(const String & str1, const String & str2) {
	return !(str1==str2);
}

/**
 *
 */
const String operator+(const String & str1, const String & str2) {
	String s(str1);
	return s.insert(s.end(), str2);
}

/**
 *
 */
const String operator+(const String & str1, const char * str2) {
	String s(str1);
	return s.insert(s.end(), str2);
}

/**
 *
 */
const String operator+(const char * str1, const String & str2) {
	String s(str1);
	return s.append(str2);
}

/**
 *
 */
const String operator+(const char c, const String & str) {
	String s(c);
	return s+str;
}

/**
 *
 */
const String operator+(const String & str, const char c) {
	return str + String(c);
}

/**
 * Allows an instance of String to be written to the ostream and returns a reference to the ostream.
 */
std::ostream & operator<<(std::ostream & out, const String &s) {
//	out << "String [" << &s << "] \"";
	for (int i=0; i<s.size(); i++) out << s.d->storage.start[i];
//	std::cout << "\"";
//	std::cout << "------ size=" << s.size() << ", capacity=" << s.capacity() << " ";

	return out;
}

} /* namespace prism */
