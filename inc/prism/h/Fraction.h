/*
 * Fraction.h
 * v1
 *
 *  Created on: Jun 26, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_FRACTION_H_
#define PRISM_FRACTION_H_

#include <ostream>

namespace prism {

class Fraction {
private:
	int m_n; // numerator
	int m_d; // denominator

public:
	Fraction(void);
	Fraction(const int numerator, const int denominator);
	virtual ~Fraction(void);

	const int 	denominator() const;
	const int 	numerator() const;
	Fraction 	reciprocal() const;
	void 		setNumerator(const int numerator);
	void 		setDenominator(const int denominator);
	Fraction& 	simplify();

	// related non-members
	friend Fraction operator+(const Fraction &f1, const Fraction &f2);
	friend Fraction operator-(const Fraction &f1, const Fraction &f2);
	friend Fraction operator*(const Fraction &f1, const Fraction &f2);
	friend Fraction operator*(const Fraction &fraction, const int i);
	friend Fraction operator*(const int i, const Fraction &fraction);
	friend Fraction operator/(const Fraction &f1, const Fraction &f2);
	friend const bool operator<(const Fraction &f1, const Fraction &f2);
	friend const bool operator>(const Fraction &f1, const Fraction &f2);
	friend const bool operator==(const Fraction &f1, const Fraction &f2);
	friend const bool operator!=(const Fraction &f1, const Fraction &f2);
	friend std::ostream & operator<<(std::ostream & out, const Fraction & f);

private:
	const int greatestCommonFactor();
};

}




#endif /* PRISM_FRACTION_H_ */
