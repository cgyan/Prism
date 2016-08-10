/*
 * Bitvector.cpp
 * v1
 *
 *  Created on: Aug 9, 2016
 *      Author: iainhemstock
 */

#include <prism/Bitvector.h>
#include <prism/Char>
#include <prism/algorithms>
#include <prism/OutOfBoundsException>
#include <iostream>
using namespace std;//todo remove this

namespace prism {

/**
 * Creates a new Bitvector that contains by default 16 bits.
 */
Bitvector::Bitvector()
	: d(new BitvectorData)
{
	d->storage.nBits = sizeof(unsigned short int) * 8; // 16 bits
	reserve(1);
}

/**
 * Creates a new Bitvector that contains \em nBits. \n
 * More precisely the bitvector will contain enough bytes to represent the requested
 * number of bits. i.e. internally the storage is represented in unsigned short ints
 * which are 16 bits each so its size will always be a multiple of 16. If a Bitvector
 * with 10 bits is requested then the Bitvector will have a size of 16, if 23 bits
 * are requested then Bitvector will have a size of 32 etc.
 */
Bitvector::Bitvector(const int nBits)
	: d(new BitvectorData)
{
	d->storage.nBits = nBits;
	reserve(numBytes(nBits));
}

/**
 * Creates a new Bitvector from the string \em bitString.
 * \code
 * 	String s = "11101110";
 *	Bitvector bv(s);
 *	cout << bv.toString(); // output: 11101110
 * \endcode
 */
Bitvector::Bitvector(const String & bitString)
	: d(new BitvectorData)
{
	d->storage.nBits = bitString.size();
	int nBytes = numBytes(d->storage.nBits);
	reserve(nBytes);

	String bs(bitString);

	for (int i=0; i<d->storage.nBits; i++) {
		if (*(bs.end()-1) == Char('1'))
			set(i);
		bs.chop(1);
	}
}

/**
 * Creates a copy of \em other.
 */
Bitvector::Bitvector(const Bitvector & other)
	: d(new BitvectorData)
{
	reserve(other.d->storage.finish-other.d->storage.start);
	prism::copy(other.d->storage.start, other.d->storage.finish, this->d->storage.start);
	d->storage.nBits = other.d->storage.nBits;
}

/**
 * Destroys this Bitvector
 */
Bitvector::~Bitvector() {
	delete d;
}

/**
 * @return Returns the value of the bit at position \em bit.
 * \code
 * Bitvector bv;
 * bv.set(4);
 * cout << bv.get(4); // output: 1
 * \endcode
 */
const bool Bitvector::get(int bit) const {
	if (!rangeCheck(bit))
		throw OutOfBoundsException(bit);

	int cell = bit / (8 * sizeof(unsigned short int));
	bit = bit % (8 * sizeof(unsigned short int));

	return ((d->storage.start[cell] & (1<<bit)) >> bit);
}

/**
 * Private method that returns the number of bytes needed to hold \em nBits.
 */
const int Bitvector::numBytes(const int nBits) const {
	int usiBits = sizeof(unsigned short int) * 8;
	int nBytes;

	if (nBits % usiBits == 0) nBytes = nBits / usiBits;
	else nBytes = nBits / usiBits + 1;

	return nBytes;
}

/**
 * Private method that performs a bounds check on the index \em n.
 * Returns true if \em n is is within bounds and false if not.
 */
const bool Bitvector::rangeCheck(const int n) const {
	if (n < 0 || n > d->storage.nBits) return false;
	return true;
}

/**
 * Resets all the bits in the Bitvector to 0.
 */
void Bitvector::resetAll() {
	unsigned short int * it = d->storage.start;
	while (it != d->storage.finish) {
		*it = *it & 0;
		++it;
	}
}

/**
 * Private method that reserves enough memory to contain the bits required.
 */
void Bitvector::reserve(const int nBytes) {
	if (nBytes > d->storage.finish - d->storage.start) {
		unsigned short int * newStorage = new unsigned short int[nBytes];
		prism::copy(d->storage.start, d->storage.finish, newStorage);

		delete []d->storage.start;
		d->storage.start = newStorage;
		d->storage.finish = d->storage.start + nBytes;

	}
}

/**
 * Sets all the bits in the Bitvector to 1.
 * \code
 * Bitvector bv(8);
 * bv.setAll();
 * cout << bv.toString(); // output: "11111111"
 * \endcode
 */
void Bitvector::setAll() {
	unsigned short int * it = d->storage.start;
	while (it != d->storage.finish) {
		*it = ~(*it & 0);
		++it;
	}
}

/**
 * Sets the specified bit at index \em bit to 1 or 0 depending on \em b.
 * If \em b is not supplied then the bit is set to 1.
 * \code
 * Bitvector bv;
 * bv.set(0); 			// sets the first bit to 1
 * bv.set(0, false); 	// sets the first bit back to 0
 * \endcode
 */
void Bitvector::set(int bit, const bool b) {
	if (!rangeCheck(bit))
		throw OutOfBoundsException(bit);

	int cell = bit / (8 * sizeof(unsigned short int));
	bit = bit % (8 * sizeof(unsigned short int));

	if (b) d->storage.start[cell] = d->storage.start[cell] | (1<<bit); 	// set bit to 1
	else d->storage.start[cell] = d->storage.start[cell] & ~(1<<bit);	// set bit to 0
}

/**
 * @return Returns the number of bits in the Bitvector.
 */
const int Bitvector::size() const {
	return d->storage.nBits;
}

/**
 * @return Returns a String representation of the bits in the Bitvector.
 * The least significant bit is the one to the far right and most significant bit
 * is to the far left.
 * \code
 * Bitvector bv(4);
 * bv.set(0);
 * bv.set(2);
 * cout << bv.toString(); // output: "0101"
 * \endcode
 */
String Bitvector::toString() const {
	String s;
	s.reserve(d->storage.nBits);

	for (int i=d->storage.nBits-1; i>=0; i--)
		s += String::number(get(i));

	return s;
}

/**
 * Shifts all the bits in the Bitvector to the left by \em pos places.
 * @return Returns a reference to this Bitvector.
 */
Bitvector Bitvector::operator <<(const int pos) const {

	Bitvector copy(this->size());

	int j = 0;
	for (int i=pos; i<copy.d->storage.nBits; i++, j++)
		copy.set(i, get(j));

	return copy;
}

/**
 * Shifts all the bits in the Bitvector to the left by \em pos places.
 * @return Returns a reference to this Bitvector.
 */
Bitvector Bitvector::operator >>(const int pos) const {

	Bitvector copy(this->size());

	int j=0;
	for (int i=pos; i<copy.d->storage.nBits; i++, j++)
		copy.set(j, get(i));

	return copy;
}

/**
 *
 */
Bitvector & Bitvector::operator <<=(const int pos) {
	*this = *this << pos;
	return *this;
}

/**
 *
 */
Bitvector & Bitvector::operator >>=(const int pos) {
	*this = *this >> pos;
	return *this;
}

/**
 * Assigns \em other to this Bitvector.
 */
Bitvector & Bitvector::operator =(const Bitvector & other) {
	if (*this == other) return *this;

	reserve(numBytes(d->storage.nBits));
	prism::copy(other.d->storage.start, other.d->storage.finish, this->d->storage.start);
	d->storage.finish = d->storage.start + other.size();

	return *this;
}

/**
 *
 */
const bool operator==(const Bitvector & bv1, const Bitvector & bv2) {
	if (bv1.size() != bv2.size())
		return false;
	return prism::equal(bv1.d->storage.start, bv1.d->storage.finish, bv2.d->storage.start);
}

/**
 *
 */
const bool operator!=(const Bitvector & bv1, const Bitvector & bv2) {
	return !(bv1==bv2);
}

/**
 * Allows an instance of Bitvector to be written to the ostream and returns a reference to the ostream.
 */
std::ostream & operator<<(std::ostream & out, const Bitvector & bv) {
	out << "Bitvector [" << &bv << "] (size:" << bv.size() << " bits) ";
	for (int bit=bv.d->storage.nBits-1; bit>=0; bit--) {
		out << bv.get(bit);
	}

	return out;
}

} /* namespace prism */

















