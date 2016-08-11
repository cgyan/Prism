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
#include <prism/UnequalSizeException>
#include <ostream>

namespace prism {
typedef unsigned long long int MemBlock;
/**
 * Creates a new Bitvector that contains by default 16 bits.
 */
Bitvector::Bitvector()
	: d(new BitvectorData)
{
	d->storage.nBits = sizeof(MemBlock) * 8;
	reserve(1);
	resetAll();
}

/**
 * Creates a new Bitvector that contains \em nBits. \n
 * More precisely the bitvector will contain enough bytes to represent the requested
 * number of bits. i.e. internally the storage is represented in unsigned long long ints
 * which are 64 bits each so its size will always be a multiple of 64. If a Bitvector
 * with 10 bits is requested then the Bitvector will reserve 64 bits but still a size of 10.
 */
Bitvector::Bitvector(const int nBits)
	: d(new BitvectorData)
{
	d->storage.nBits = nBits;
	reserve(numBytes(nBits));
	resetAll();
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
	resetAll();

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
	resetAll();
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
 * @return Returns true if all of the bits are set to 1.
 */
const bool Bitvector::all() const {
	for (int i=0; i<d->storage.nBits; i++)
		if (get(i) == 0) return false;
	return true;
}

/**
 * @return Returns true if any of the bits are set to 1.
 */
const bool Bitvector::any() const {
	for (int i=0; i<d->storage.nBits; i++)
		if (get(i)) return true;
	return false;

}

/**
 * @return Returns the number of bits that have been set to 1.
 */
const int Bitvector::count() const {
	int n=0;
	for (int i=0; i<d->storage.nBits; i++)
		if (get(i)) ++n;
	return n;

}

/**
 * Flips \em bit from zero to one or from one to zero.
 */
void Bitvector::flip(int bit) {
	int cell = bit / (8 * sizeof(MemBlock));
	bit = bit % (8 * sizeof(MemBlock));

	d->storage.start[cell] = d->storage.start[cell] ^ (1<<bit);
}

/**
 * Flips each bit converting zeros to ones and ones to zeros.
 */
void Bitvector::flipAll() {
	*this = ~(*this);
}

/**
 * @return Returns the value of the bit at position \em bit.
 * \code
 * Bitvector bv; 		// 0000
 * bv.set(3); 			// 1000
 * cout << bv.get(3); 	// output: 1
 * \endcode
 */
const bool Bitvector::get(int bit) const {
	if (!rangeCheck(bit))
		throw OutOfBoundsException(bit);

	int cell = bit / (8 * sizeof(MemBlock));
	bit = bit % (8 * sizeof(MemBlock));

	return ((d->storage.start[cell] & (1<<bit)) >> bit);
}

/**
 * @return Returns true if none of the bits are set to 1, false otherwise.
 */
const bool Bitvector::none() const {
	for (int i=0; i<d->storage.nBits; i++)
		if (get(i) == 1) return false;
	return true;
}

/**
 * Private method that returns the number of bytes needed to hold \em nBits.
 */
const int Bitvector::numBytes(const int nBits) const {
	int nBlockBits = sizeof(MemBlock) * 8;
	int nBytes;

	if (nBits % nBlockBits == 0) nBytes = nBits / nBlockBits;
	else nBytes = nBits / nBlockBits + 1;

	return nBytes;
}

/**
 * Private method that performs a bounds check on the index \em n.
 * Returns true if \em n is is within bounds and false if not.
 */
const bool Bitvector::rangeCheck(const int n) const {
	if (n < 0 || n >= d->storage.nBits) return false;
	return true;
}

/**
 * Resets all the bits in the Bitvector to 0.
 */
void Bitvector::resetAll() {
	MemBlock * it = d->storage.start;
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
		MemBlock * newStorage = new MemBlock[nBytes];
		prism::copy(d->storage.start, d->storage.finish, newStorage);

		delete []d->storage.start;
		d->storage.start = newStorage;
		d->storage.finish = d->storage.start + nBytes;

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

	int cell = bit / (8 * sizeof(MemBlock));
	bit = bit % (8 * sizeof(MemBlock));

	if (b) d->storage.start[cell] = d->storage.start[cell] | (1<<bit); 	// set bit to 1
	else d->storage.start[cell] = d->storage.start[cell] & ~(1<<bit);	// set bit to 0
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
	MemBlock * it = d->storage.start;
	while (it != d->storage.finish) {
		*it = ~(*it & 0);
		++it;
	}
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
 *
 */
MemBlock Bitvector::to_ull() const {
//	if (d->storage.nBits > sizeof(MemBlock) * 8)
//		return -1;
//
//	MemBlock * it = d->storage.start;
//	String s;
//
//	while (it != d->storage.finish) {
//		MemBlock mb = *it;
//		s += String::number(mb);
//	}
//
//	return
}

/**
 * @return Returns the value of the bit at position \em bit.
 */
bool Bitvector::operator [](const int bit) {
	return get(bit);
}

/**
 * @return Returns the value of the bit at position \em bit.
 */
const bool Bitvector::operator [](const int bit) const {
	return get(bit);
}

/**
 * @return Returns a copy of this Bitvector that has had all its bits shifted
 * to the left by \em pos positions.
 */
Bitvector Bitvector::operator <<(const int pos) const {

	Bitvector copy(this->size());

	int j = 0;
	for (int i=pos; i<copy.d->storage.nBits; i++, j++)
		copy.set(i, get(j));

	return copy;
}

/**
 * @return Returns a copy of this Bitvector that has had all its bits shifted
 * to the right by \em pos positions.
 */
Bitvector Bitvector::operator >>(const int pos) const {

	Bitvector copy(this->size());

	int j=0;
	for (int i=pos; i<copy.d->storage.nBits; i++, j++)
		copy.set(j, get(i));

	return copy;
}

/**
 * @return Returns a reference to this Bitvector which has had its bits
 * shifted to the left by \em pos positions.
 */
Bitvector & Bitvector::operator <<=(const int pos) {
	*this = *this << pos;
	return *this;
}

/**
 * @return Returns a reference to this Bitvector which has had its bits
 * shifted to the right by \em pos positions.
 */
Bitvector & Bitvector::operator >>=(const int pos) {
	*this = *this >> pos;
	return *this;
}

/**
 * Flips all the bits from zeros to ones or from ones to zeros. Equivalent to flipAll().
 * @return A copy of this Bitvector which has had all of its bits flipped.
 */
Bitvector Bitvector::operator ~() const {
	Bitvector copy(*this);
	MemBlock * blockIt = copy.d->storage.start;

	while (blockIt != copy.d->storage.finish) {
		*blockIt = ~*blockIt;
		++blockIt;
	}
	return copy;
}

/**
 * Performs a bitwise AND on this Bitvector and \em other.
 * @return Returns a reference to this Bitvector updated with the result of (this bitvector & other).
 */
Bitvector & Bitvector::operator &=(const Bitvector & other) {
	*this = *this & other;
	return *this;
}

/**
 * Performs a bitwise OR on this Bitvector and \em other.
 * @return Returns a reference to this Bitvector updated with the result of (this bitvector | other).
 */
Bitvector & Bitvector::operator |=(const Bitvector & other) {
	*this = *this | other;
	return *this;
}

/**
 * Performs a bitwise XOR on this Bitvector and \em other.
 * @return Returns a reference to this Bitvector updated with the result of (this bitvector & other).
 */
Bitvector & Bitvector::operator ^=(const Bitvector & other) {
	*this = *this ^ other;
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
 * Performs a bitwise AND on \em bv1 and \em bv2.
 * @return Returns a new Bitvector with the result of \em (bv1 & bv2).
 */
Bitvector operator&(const Bitvector & bv1, const Bitvector & bv2) {
	if (bv1.size() != bv2.size())
		throw UnequalSizeException(bv1.size(), bv2.size());

	Bitvector result(bv1.size());
	MemBlock * bv1It = bv1.d->storage.start;
	MemBlock * bv2It = bv2.d->storage.start;
	MemBlock * resultIt = result.d->storage.start;

	while (bv1It != bv1.d->storage.finish) {
		*resultIt = *bv1It & *bv2It;
		++bv1It;
		++bv2It;
		++resultIt;
	}

	return result;
}

/**
 * Performs a bitwise OR on \em bv1 and \em bv2.
 * @return Returns a new Bitvector with the result of \em (bv1 | bv2).
 */
Bitvector operator|(const Bitvector & bv1, const Bitvector & bv2) {
	if (bv1.size() != bv2.size())
		throw UnequalSizeException(bv1.size(), bv2.size());

	Bitvector result(bv1.size());
	MemBlock * bv1It = bv1.d->storage.start;
	MemBlock * bv2It = bv2.d->storage.start;
	MemBlock * resultIt = result.d->storage.start;

	while (bv1It != bv1.d->storage.finish) {
		*resultIt = *bv1It | *bv2It;
		++bv1It;
		++bv2It;
		++resultIt;
	}

	return result;
}

/**
 * Performs a bitwise XOR on \em bv1 and \em bv2.
 * @return Returns a new Bitvector with the result of \em (bv1 ^ bv2).
 */
Bitvector operator^(const Bitvector & bv1, const Bitvector & bv2) {
	if (bv1.size() != bv2.size())
		throw UnequalSizeException(bv1.size(), bv2.size());

	Bitvector result(bv1.size());
	MemBlock * bv1It = bv1.d->storage.start;
	MemBlock * bv2It = bv2.d->storage.start;
	MemBlock * resultIt = result.d->storage.start;

	while (bv1It != bv1.d->storage.finish) {
		*resultIt = *bv1It ^ *bv2It;
		++bv1It;
		++bv2It;
		++resultIt;
	}

	return result;
}

/**
 * @return Returns true if the two Bitvectors are equal to each other, false otherwise.
 */
const bool operator==(const Bitvector & bv1, const Bitvector & bv2) {
	if (bv1.size() != bv2.size())
		return false;
	return prism::equal(bv1.d->storage.start, bv1.d->storage.finish, bv2.d->storage.start);
}

/**
 * @return Returns true if the two Bitvectors are not equal to each other, flase otherwise.
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

















