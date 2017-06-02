#ifndef PRISM_MATHF_H
#define PRISM_MATHF_H

namespace prism {

class Mathf {
public:
	static const float PI;

public:
	static void 		correctFloatingPointError(float & num);
	static void 		degreeToRadian(float & angle);
	static const bool 	isPrime(const int n);
	static void 		radianToDegree(float & angle);
	static const float	roundTo(const float f, const int decimalPlaces);

};

}

#endif // PRISM_MATHF_H
