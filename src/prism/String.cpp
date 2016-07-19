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
#include <cctype>
#include <functional>

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
String::String(const Char & c)
	: d(new StringData)
{
	resize(1);
	prism::fill_n(d->storage.start, 1, c.tochar());
}

/**
 * Creates a string filled with \em size amount of the char \em c.
 */
String::String(const int size, const Char & c)
	: d(new StringData)
{
	reserve(size);
	prism::fill_n(d->storage.start, size, c.tochar());
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
 * @return Returns the number of occurrences of the string \em str.
 */
//const int String::count(const String & str) const {
//	int ret = 0;
//
//	const_iterator bit = constBegin();
//	const_iterator eit = constEnd();
//
//	while (bit != eit) {
//		const_iterator result = prism::search(bit, bit+str.size(), str.begin(), str.end());
//		if (result == eit) break;
//		else {
//			++ret;
//			++bit;
//		}
//	}
//	return ret;
//}

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
 *
 */
//const int String::firstIndexOf(const String & str, const int from) const {
//
//}

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
		resize(newSize * d->storage.exponent);

	// 3: copy the new string into this storage
	prism::copy(str.begin(), str.end(), d->storage.start + startIndex);

	// 4: copy the buffer back into this string
	startIndex = startIndex + str.size();
	prism::copy(buffer.begin(), buffer.end(), d->storage.start + startIndex);

	return (*this);
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
String & String::replace(const int position, const int nCharsToReplace, const Char & c) {
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
String & String::replace(const String & oldStr, const Char & newChar) {
	return replace(oldStr, String(newChar));
}

/**
 * Replaces each occurrence of the Char \em c with the string \em newStr.
 * @return Returns a reference to this string.
 */
String & String::replace(const Char & oldChar, const String & newStr) {
	return replace(String(oldChar), newStr);
}

/**
 * Replaces each occurrence of the Char \em oldChar with the Char \em newChar.
 * @return Returns a reference to this string.
 */
String & String::replace(const Char & oldChar, const Char & newChar) {
	return replace(String(oldChar), String(newChar));
}

/**
 * Removes \em nCharsToRemove starting from \em position (0-based).
 * @return Returns a reference to this string.
 */
String & String::remove(const int position, const int nCharsToRemove) {

	prism::copy(begin()+position+nCharsToRemove, end(), begin()+position);
	resize(size() - nCharsToRemove);

	return *this;
}

/**
 * Removes all occurrences of the Char \em c.
 * @retrn Returns a reference to this string.
 */
String & String::remove(const Char & c) {
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
		int s = capacity() + newSize;
		reserve(s);
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
 *
 */
const bool String::startsWith(const String & str) const {
	const_iterator eit = begin() + str.size();
	const_iterator it = prism::search(begin(), eit, str.begin(), str.end());

	if (it == eit) return false;
	else return true;
}

/**
 *
 */
const bool String::startsWith(const char c) const {
	return at(0) == c;
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
	const_iterator cit = s.constBegin();

	while (cit != s.constEnd()) {
		Char c(*cit);
		if (c.isLetter() && c.isUpper()) {
			c += 32;
			*cit = c.tochar();
		}
		++cit;
	}
	return s;
}

/**
 * @return Returns a copy of this string as a std::string.
 */
std::string String::toStdString() const {
	return std::string(d->storage.start);
}

/**
 * @return Returns a copy of this string where each character is uppercase.
 */
String String::toUpper() const {
	String s(*this);
	const_iterator cit = s.constBegin();

	while (cit != s.constEnd()) {
		Char c(*cit);
		if (c.isLetter() && c.isLower()) {
			c -= 32;
			*cit = c.tochar();
		}
		++cit;
	}
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
	int size = other.size();
	reserve(size);
	prism::copy(other.begin(), other.end(), d->storage.start);
	d->storage.end = d->storage.start + size;

	return *this;
}

/**
 *
 */
String & String::operator +=(const String & other) {
	return insert(end(), other);
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
//String String::number(const int n) {
//	char c = n;
//	return String(c);
//}

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
String operator+(const String & str1, const String & str2) {
	String s(str1);
	return s.insert(s.end(), str2);
}

/**
 *
 */
String operator+(const String & str1, const char * str2) {
	String s(str1);
	return s.insert(s.end(), str2);
}

/**
 *
 */
String operator+(const char * str1, const String & str2) {
	String s(str1);
	return s.append(str2);
}

/**
 *
 */
String operator+(const char c, const String & str) {
	String s(c);
	return s+str;
}

/**
 *
 */
String operator+(const String & str, const char c) {
	return str + String(c);
}

/**
 * Allows an instance of String to be written to the ostream and returns a reference to the ostream.
 */
std::ostream & operator<<(std::ostream & out, const String &s) {
	out << "String [" << &s << "] \"";
	for (int i=0; i<s.size(); i++) out << s.d->storage.start[i];
	std::cout << "\"\n";
	std::cout << "------ size=" << s.size() << ", capacity=" << s.capacity() << " ";

	return out;
}

} /* namespace prism */
