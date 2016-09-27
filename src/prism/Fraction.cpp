/*
 * Fraction.cpp
 * v0.1
 *
 *  Created on: Jun 26, 2016
 *      Author: iainhemstock
 */

#include <prism/h/Fraction.h>
#include <prism/h/algorithms.h>

namespace prism {

/**
 * Creates a Fraction object and sets its numerator and denominator to 1.
 */
Fraction::Fraction(void)
	: m_n(1), m_d(1)
{
//	std::cout << "[Fraction::Fraction()] " << this << std::endl;

}

/**
 * Creates a Fraction object setting the numerator and denominator to the values passed in.
 * The class will attempt to simplify the fraction.
 * i.e.
 *  4           1
 * --- becomes ---
 *  8           2
 */
Fraction::Fraction(const int numerator, const int denominator)
	: m_n(numerator), m_d(denominator)
{
	simplify();

}

/**
 * Destroys this Fraction.
 */
Fraction::~Fraction(void) {}

/**
 * Returns this Fraction's denominator.
 */
const int Fraction::denominator() const {
	return m_d;
}

/**
 * Calculates and returns the greatest common factor of this Fraction.
 */
const int Fraction::greatestCommonFactor() {
	int gcf = 1;

	for (int i=1; i<=prism::min(m_n,m_d); i++) {
		if (m_n%i == 0 && m_d%i == 0)
			gcf = i;
	}

	return gcf;
}

/**
 * Returns this Fraction's numerator.
 */
const int Fraction::numerator() const {
	return m_n;
}

/**
 * Returns a new Fraction that is the reciprocal of this fraction.
 * i.e. the numerator and denominator are swapped around.
 *                    1      2
 * The reciprocal of --- is ---
 *                    2      1
 *  Any fraction multiplied by its own reciprocal will always equal 1.
 */
Fraction Fraction::reciprocal() const {
	return Fraction(m_d, m_n);
}

/**
 * Sets this Fraction's numerator to /em numerator.
 */
void Fraction::setNumerator(const int numerator) {
	m_n = numerator;
}

/**
 * Sets this Fraction's denominator to /em denominator.
 */
void Fraction::setDenominator(const int denominator) {
	m_d = denominator;
}

/**
 *  8
 * ---
 *  16
 */
Fraction& Fraction::simplify() {
	int gcf = greatestCommonFactor();

	m_n = m_n/gcf;
	m_d = m_d/gcf;

	return *this;
}

/**********************************************************************
Related non-members
**********************************************************************/
/**
 * Adds the fractions /em f1 and /em f2 together and returns a new Fraction.
 * If the two denominators are the same then the two numerators are added together
 * to form the new numerator and the original denominator is kept the same.
 * e.g.  1     1         2
 *      --- + ---   =   ---
 *       4     4         4
 * If the denominators are different then we alter the fractions in order to make
 * both denominators the same value. We make a whole fraction out of the second
 * fraction's denominator and multiply it by the first fraction. Then make a whole
 * fraction from the first fraction's denominator and multiply it by the second fraction.
 * Now we can simply add together the two numerators and keep the denominator the same.
 *  1     1        | 4     1 |   | 1     2 |        4     2     6         3
 * --- + ---   =   |--- x ---| + |--- x ---|   =   --- + --- = ---   =   ---
 *  2     4        | 4     2 |   | 4     2 |        8     8     8         4
 */
Fraction operator+(const Fraction &f1, const Fraction &f2) {
	if (f1.m_d == f2.m_d) {
		return Fraction(f1.m_n + f2.m_n, f1.m_d);
	}

	return Fraction(f2.m_d, f2.m_d) * f1 + f2 * Fraction(f1.m_d, f1.m_d);
}

/**
 * Subtracts the fractions /em f1 and /em f2 and returns a new Fraction.
 * If the two denominators are the same then the two numerators are subtracted
 * to form the new numerator and the original denominator is kept the same.
 * e.g.  3     1         2
 *      --- - ---   =   ---
 *       4     4         4
 * If the denominators are different then we alter the fractions in order to make
 * both denominators the same value. We make a whole fraction out of the second
 * fraction's denominator and multiply it by the first fraction. Then make a whole
 * fraction from the first fraction's denominator and multiply it by the second fraction.
 * Now we can simply subtract the two numerators and keep the denominator the same.
 *  3     1        | 2     3 |   | 1     4 |        6     4     2         1
 * --- - ---   =   |--- x ---| - |--- x ---|   =   --- - --- = ---   =   ---
 *  4     2        | 2     4 |   | 2     4 |        8     8     8         4
 */
Fraction operator-(const Fraction &f1, const Fraction &f2) {
	if (f1.m_d == f2.m_d) {
		return Fraction(f1.m_n - f2.m_n, f1.m_d);
	}

	return Fraction(f2.m_d, f2.m_d) * f1 - f2 * Fraction(f1.m_d, f1.m_d);
}

/**
 * Multiplies /em f1 and /em f2 together and returns a new Fraction.
 * Fraction multiplication is the easiest arithmetical operation.
 * Simply multiply the two numerators together to form the new numerator
 * and multiply the two denominators together to form the new denominator.
 * e.g.  2     8          2x8         16        4
 *      --- x ---    =    ---    =   ---   =   ---
 *       5     4          5x4         20        5
 */
Fraction operator*(const Fraction &f1, const Fraction &f2) {
	return Fraction(f1.m_n * f2.m_n, f1.m_d * f2.m_d);
}

/**
 * Multiplies the Fraction /em fraction by the whole number /em i.
 * Returns a new Fraction.
 */
Fraction operator*(const Fraction &fraction, const int i) {
	Fraction f1 = fraction;
	Fraction f2(i,1);
	return Fraction(f1.m_n * f2.m_n, f1.m_d * f2.m_d);
}

/**
 * Multiplies the whole number /em i by the Fraction /em fraction.
 * Returns a new Fraction.
 */
Fraction operator*(const int i, const Fraction &fraction) {
	return fraction * i;
}

/**
 * Divides /em f1 by /em f2 and returns a new Fraction.
 * Fraction division is achieved by taking the reciprocal of the second fraction
 * and multiplying it against the first fraction.
 * See /em Fraction::reciprocal() for more information.
 *  3     2         3     7         21
 * --- / ---   =   --- * ---   =   ---
 *  4     7         4     2          8
 */
Fraction operator/(const Fraction &f1, const Fraction &f2) {
	return f1 * f2.reciprocal();
}

/**
 * Returns true if /em f1 is less than /em f2, false otherwise.
 */
const bool operator<(const Fraction &f1, const Fraction &f2) {
	if (f1.m_d == f2.m_d) {
		bool b = f1.m_n < f2.m_n;
		return b;
	}

	int n1 = f1.m_n * f2.m_d;
	int n2 = f2.m_n * f1.m_d;

	return n1 < n2;
}

/**
 * Returns true if /em f1 is less than /em f2, false otherwise.
 */
const bool operator>(const Fraction &f1, const Fraction &f2) {
	return f2<f1;
}

/**
 * Returns true if /em f1 and /em f2 are equal in value.
 */
const bool operator==(const Fraction &f1, const Fraction &f2) {
	if (f1.m_n == f2.m_n && f1.m_d == f2.m_d)
		return true;

	int n1 = f1.m_n * f2.m_d;
	int n2 = f2.m_n * f1.m_d;

	return n1 == n2;
}

/**
 * Returns true if /em f1 does not equal /em f2 in value, false otherwise.
 */
const bool operator!=(const Fraction &f1, const Fraction &f2) {
	return !(f1==f2);
}

/**
 * Allows an instance of Fraction to be written to the ostream and returns a reference to the ostream.
 */
std::ostream & operator<<(std::ostream & out, const Fraction & f) {
	out << "Fraction [" << &f << "]: (numerator=" << f.m_n << ", denominator=" << f.m_d << ")";
	return out;
}


}


