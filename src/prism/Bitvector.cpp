/*
 * Bitvector.cpp
 * v1
 *
 *  Created on: Aug 9, 2016
 *      Author: iainhemstock
 */

#include <prism/h/Bitvector.h>
#include <prism/h/String.h>
#include <prism/h/Char.h>
#include <prism/h/algorithm.h>
#include <prism/h/OutOfBoundsException.h>
#include <prism/h/UnequalSizeException.h>
#include <prism/h/OverflowException.h>
#include <cmath>

namespace prism {

/**
 * Creates a new Bitvector that contains by default 64 bits.
 */
Bitvector::Bitvector()
	: d(new BitvectorData)
{
	d->storage.nBits = sizeof(unsigned long long int) * 8;
	reserve(1);
	resetAll();
}

/**
 * Creates a new Bitvector that contains \em nBits. \n
 * More precisely the bitvector will contain enough bytes to represent the requested
 * number of bits. i.e. internally the storage is represented in unsigned long long ints
 * which are 64 bits each so its size will always be a multiple of 64. If a Bitvector
 * with 10 bits is requested then the Bitvector will reserve 64 bits but will still have a size of 10.
 */
Bitvector::Bitvector(const int nBits)
	: d(new BitvectorData)
{
	d->storage.nBits = nBits;
	reserve(numChunks(nBits));
	resetAll();
}

/**
 * Creates a new Bitvector from the string \em bitString.
 * \code
 * 	String s = "11101110";
 *	Bitvector bv(s);
 *	cout << bv.string(); // output: 11101110
 * \endcode
 */
Bitvector::Bitvector(const String & bitString)
	: d(new BitvectorData)
{
	d->storage.nBits = bitString.size();
	int nChunks = numChunks(d->storage.nBits);
	reserve(nChunks);
	resetAll();

	String bs(bitString);

	for (int i=0; i<d->storage.nBits; i++) {
		if (*(bs.end()-1) == Char('1')) set(i);
		else set(i, false);
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
	int cell = bit / (8 * sizeof(unsigned long long int));
	bit = bit % (8 * sizeof(unsigned long long int));

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

	int cell = bit / (8 * sizeof(unsigned long long int));
	bit = bit % (8 * sizeof(unsigned long long int));

	unsigned long long int mask = 1;

	return (d->storage.start[cell] & (mask<<bit)) >> bit;
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
 * Private method that returns the number of chunks needed to hold \em nBits.
 */
const int Bitvector::numChunks(const int nBits) const {
	int nBitsInChunk = sizeof(unsigned long long int) * 8;
	int nChunks;

	if (nBits % nBitsInChunk == 0) nChunks = nBits / nBitsInChunk;
	else nChunks = nBits / nBitsInChunk + 1;

	return nChunks;
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
	unsigned long long int * chunkIt = d->storage.start;
	while (chunkIt != d->storage.finish) {
		*chunkIt = *chunkIt & 0;
		++chunkIt;
	}
}

/**
 * Private method that reserves enough memory to contain the bits required.
 */
void Bitvector::reserve(const int nChunks) {
	if (nChunks > d->storage.finish - d->storage.start) {
		unsigned long long int * newChunks = new unsigned long long int[nChunks];
		prism::copy(d->storage.start, d->storage.finish, newChunks);

		delete []d->storage.start;
		d->storage.start = newChunks;
		d->storage.finish = d->storage.start + nChunks;

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

	int cell = bit / (8 * sizeof(unsigned long long int));
	bit = bit % (8 * sizeof(unsigned long long int));

	unsigned long long int mask = 1;

	if (b) d->storage.start[cell] = d->storage.start[cell] | (mask<<bit); 	// set bit to 1
	else d->storage.start[cell] = d->storage.start[cell] & ~(mask<<bit);	// set bit to 0
}

/**
 * Sets all the bits in the Bitvector to 1.
 * \code
 * Bitvector bv(8);
 * bv.setAll();
 * cout << bv.string(); // output: "11111111"
 * \endcode
 */
void Bitvector::setAll() {
	unsigned long long int * chunkIt = d->storage.start;
	while (chunkIt != d->storage.finish) {
		*chunkIt = ~(*chunkIt & 0);
		++chunkIt;
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
 * cout << bv.string(); // output: "0101"
 * \endcode
 */
String Bitvector::string() const {
	String s;
	s.reserve(d->storage.nBits);

	for (int i=d->storage.nBits-1; i>=0; i--)
		s += String::number(get(i));

	return s;
}

/**
 * @return Returns an unsigned long long int with the integer value that has
 * the same bits set as the Bitvector.
 * \note If the binary value is more than an unsigned long long int can represent
 * then an OverflowException is thrown.
 */
unsigned long long int Bitvector::ull() const {
	if (d->storage.nBits > sizeof(unsigned long long int) * 8) {
		throw OverflowException();
	}

	unsigned long long int result = 0;

	for (int i=0; i<d->storage.nBits; i++)
		if (get(i)) {
			unsigned long long int n = pow(2, i);
			result += n;
		}

	return result;
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
	unsigned long long int * chunkIt = copy.d->storage.start;

	while (chunkIt != copy.d->storage.finish) {
		*chunkIt = ~*chunkIt;
		++chunkIt;
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
 * @return Returns a reference to this Bitvector updated with the result of (this bitvector ^ other).
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

	reserve(numChunks(d->storage.nBits));
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
	unsigned long long int * bv1It = bv1.d->storage.start;
	unsigned long long int * bv2It = bv2.d->storage.start;
	unsigned long long int * resultIt = result.d->storage.start;

	while (bv1It != bv1.d->storage.finish) {
		*resultIt = *bv1It & *bv2It;
		++bv1It; ++bv2It; ++resultIt;
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
	unsigned long long int * bv1It = bv1.d->storage.start;
	unsigned long long int * bv2It = bv2.d->storage.start;
	unsigned long long int * resultIt = result.d->storage.start;

	while (bv1It != bv1.d->storage.finish) {
		*resultIt = *bv1It | *bv2It;
		++bv1It; ++bv2It; ++resultIt;
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
	unsigned long long int * bv1It = bv1.d->storage.start;
	unsigned long long int * bv2It = bv2.d->storage.start;
	unsigned long long int * resultIt = result.d->storage.start;

	while (bv1It != bv1.d->storage.finish) {
		*resultIt = *bv1It ^ *bv2It;
		++bv1It; ++bv2It; ++resultIt;
	}

	return result;
}

/**
 * @return Returns true if the two Bitvectors are equal to each other, false otherwise.
 * The Bitvectors are considered equal if they are the same size and each corresponding bit
 * is set to the same value.
 */
const bool operator==(const Bitvector & bv1, const Bitvector & bv2) {
	if (bv1.size() != bv2.size())
		return false;
	return prism::equal(bv1.d->storage.start, bv1.d->storage.finish, bv2.d->storage.start);
}

/**
 * @return Returns true if the two Bitvectors are not equal to each other, false otherwise.
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

















