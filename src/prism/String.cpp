/*
 * String.cpp
 * v0.1
 *
 *  Created on: Jul 11, 2016
 *      Author: iainhemstock
 */

#include <prism/String>
#include <prism/Algorithms>
#include <prism/OutOfBoundsException>
#include <iostream>

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
 * Creates a string of size 1 initialised to the char \em c.
 */
String::String(const char c)
	: d(new StringData)
{
	resize(1);
	prism::fill_n(d->storage.start, 1, c);
}

/**
 *
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
 * @return Returns a reference to the char at \em index.
 * @throw Throws an OutOfBoundsException if \em index is out of bounds.
 */
char & String::at(const int index) {
	if (!rangeCheck(index))
		throw OutOfBoundsException(index);

	return this->operator [](index);
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
typename String::const_iterator String::cbegin() const {
	return const_iterator(d->storage.start);
}

/**
 * @return Returns the number of occurrences of the char \em c.
 */
const int String::count(const char c) const {
	return prism::count(d->storage.start, d->storage.end, c);
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
 * @return Returns true if the string's last character is \em c, false otherwise.
 */
const bool String::endsWith(const char c) const {
	return *(d->storage.end-1) == c;
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
 * @return Returns the position of the first occurrence of the char \em c in the string searching forwards
 * from the position \em from (0 by default). If there is no occurrence then -1 is returned instead.
 */
const int String::firstIndexOf(const char c, const int from) const {
	int ret = -1;

	String::const_iterator it = prism::find(d->storage.start + from, d->storage.end, c);
	if (it != end())
		ret = it - d->storage.start;

	return ret;

}

/**
 * Inserts a copy of \em str one character before the position represented by \em insertAfter.
 */
String & String::insert(iterator insertBefore, const String & str) {
	// ===========================================================================================
	// Currently this method copies all the characters after the insertion point into
	// a temp buffer, inserts the new string and then copies the temp buffer
	// back onto the end of the string. This could be improved by not using the temp buffer
	// and instead just looping through the characters backwards and moving them one at a time
	// to their new location at the end of the string. The Vector::insert() method does this.
	// ===========================================================================================

	// 1: copy all the chars that will shift up to a temp buffer
	int startIndex = insertBefore - begin();
	iterator itBegin = begin() + startIndex;
	iterator itEnd = end();

	int nCharsToMove = itEnd - itBegin;
	String buffer;
	buffer.resize(nCharsToMove);
	prism::copy(itBegin, itEnd, buffer.begin());

	// 2: need more capacity?
	int newSize = size() + str.size();

	if (newSize > capacity())
		resize(newSize);

	// 3: copy the new string into this storage
	prism::copy(str.begin(), str.end(), d->storage.start + startIndex);

	// 4: copy the buffer back into this string
	startIndex = startIndex + str.size();
	prism::copy(buffer.begin(), buffer.end(), d->storage.start + startIndex);

	return (*this);
}

/**
 * @return Returns true if the string has no content, false otherwise.
 */
const bool String::isEmpty() const {
	return size() == 0;
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
 * Performs a range check on \em index to ensure that 0 <= index < size().
 * @returns Returns true if \em index is within bounds, false otherwise.
 */
const bool String::rangeCheck(const int index) const {
	if (index < 0 || index >= size()) return false;
	return true;
}

/**
 * Reserves enough memory for the string to contain \em newCapacity characters i.e. newCapacity * sizeof(char).
 * The capacity can only grow and will not lessen even if clear() or remove() is called. Only squeeze() can
 * alter the capacity to a lower amount. If \em newCapacity is less than or equal to the current capacity then
 * nothing changes. Any existing characters in the string are not affected by this function.
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
 * If \em newSize is less than the current size then those
 * characters are removed from the end. If \em newSize is greater than
 * the current size then those new characters will be initialised to
 * default constructed values i.e. " ".
 */
void String::resize(const int newSize) {
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
 * @return Returns the size of the string. This method is identical to length().
 */
const int String::size() const {
	return d->storage.end - d->storage.start;
}

/**
 * @return Returns a new string copied from this string starting at the character
 * at \em startChar for \em size characters.
 */
String String::sub(const int startChar, int size) const {
	if (size > this->size())
		return *this;

	if (size == -1)
		size = this->size();

	String s;
	s.resize(size);
	prism::copy_n(d->storage.start + startChar, size, s.begin());

	return s;
}

/**
 * @return Returns a new string copied from this string starting at the character
 * pointed to by the iterator \em first through to the character pointed at by the iterator \em last.
 */
String String::sub(iterator first, iterator last) const {
	String s;
	s.resize(last - first);
	prism::copy(first, last, s.begin());

	return s;
}

/**
 * @return Returns a copy of this string as a std::string.
 */
std::string String::toStdString() const {
	return std::string(d->storage.start);
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
	int size = other.size();
	reserve(size);
	prism::copy(other.begin(), other.end(), d->storage.start);
	d->storage.end = d->storage.start + size;

	return *this;
}

/**
 * Allows an instance of String to be written to the ostream and returns a reference to the ostream.
 */
std::ostream & operator<<(std::ostream & out, const String &s) {
	out << "String [" << &s << "] \"";
	for (int i=0; i<s.size(); i++) out << s.d->storage.start[i];
	std::cout << "\"\n";
	std::cout << "String -- size=" << s.size() << ", capacity=" << s.capacity() << " ";

	return out;
}

} /* namespace prism */
