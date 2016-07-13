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
	int s = string.size();
	reserve(s);

	for (int i=0; i<s; i++)
		d->storage.start[i] = string.at(i);

	d->storage.end = d->storage.start + s;
}

/**
 *
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
 *
 */
typename String::iterator String::begin() {
	return iterator(d->storage.start);
}

/**
 *
 */
typename String::const_iterator String::begin() const {
	return const_iterator(d->storage.start);
}

/**
 *
 */
const int String::capacity() const {
	return d->storage.finish - d->storage.start;
}

/**
 *
 */
typename String::const_iterator String::cbegin() const {
	return const_iterator(d->storage.start);
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
 *
 */
typename String::iterator String::end() {
	return iterator(d->storage.end);
}

/**
 *
 */
typename String::const_iterator String::end() const {
	return const_iterator(d->storage.end);
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
 *
 */
void String::reserve(const int newCapacity) {
	if (newCapacity <= capacity())
		return;

	char * newStorage = new char[newCapacity];
	int s = size();

	for (int i=0; i<s; i++) {
		newStorage[i] = d->storage.start[i];
	}

	delete [] d->storage.start;
	d->storage.start = newStorage;
	d->storage.end = d->storage.start + s;
	d->storage.finish = d->storage.start + newCapacity;
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
 * Allows an instance of String to be written to the ostream and returns a reference to the ostream.
 */
std::ostream & operator<<(std::ostream & out, const String &s) {
	out << "String [" << &s << "] ";
	for (int i=0; i<s.size(); i++) out << s.d->storage.start[i];
	std::cout << "\n";
	std::cout << "String -- size=" << s.size() << ", capacity=" << s.capacity() << " ";

	return out;
}

} /* namespace prism */
