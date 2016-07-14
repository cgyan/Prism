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
 *
 */
//String::String(const char * string)
//	: d(new StringData)
//{
//	// string passed in should end with \0
//}

/**
 * Creates a new string from a std::string.
 */
String::String(const std::string & string)
	: d(new StringData)
{
	reserve(string.size());
	prism::copy(string.begin(), string.end(), this->begin());
	d->storage.end = d->storage.start + string.size();
}

/**
 *
 */
String::String(const int size, const char c)
	: d(new StringData)
{
	reserve(size);
	prism::fill_n(begin(), size, c);
	d->storage.end = d->storage.start + size;
}

/**
 * Creates a copy of this string.
 */
String::String(const String &copy)
	: d(new StringData)
{
	reserve(copy.size());
	prism::copy(copy.begin(), copy.end(), this->begin());
	this->d->storage.end = this->d->storage.start + copy.size();
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
	return prism::count(begin(), end(), c);
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
	return *(end()-1) == c;
}

/**
 * Sets every character to \em c. If \em size is not equal to -1 (the deafult)
 * then the string gets resized to \em size first.
 */
String & String::fill(const char c, const int size) {
	if (size >= 0)
		resize(size);

	prism::fill(begin(), end(), c);

	return *this;
}

/**
 * @return Returns the position of the first occurrence of the char \em c in the string searching forwards
 * from the position \em from (0 by default). If there is no occurrence then -1 is returned instead.
 */
const int String::indexOf(const char c, const int from) const {
	int ret = -1;

	String::const_iterator it = prism::find(begin() + from, end(), c);
	if (it != end()) ret = it - begin();

	return ret;

}

/**
 * @return Returns true if the string has no content, false otherwise.
 */
const bool String::isEmpty() const {
	return size() == 0;
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

	prism::copy(this->begin(), this->end(), newStorage);

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

	prism::fill(begin()+oldSize, begin()+newSize, char(' '));
	d->storage.end = d->storage.start + newSize;
}

/**
 * @return Returns the size of the string. This method is identical to length().
 */
const int String::size() const {
	return d->storage.end - d->storage.start;
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
	reserve(other.size());
	prism::copy(other.begin(), other.end(), this->begin());
	d->storage.end = d->storage.start + other.size();

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
