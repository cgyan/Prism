#include <prism/Mathf>
#include <cmath>

namespace prism {

const float Mathf::PI = 3.141592f;

/**
 *
 */
void Mathf::correctFloatingPointError(float & num)
{
	float t = 0.00001f;
	//float r = 0.000;
	float numUp = ceilf(num);
	float numDown = floorf(num);

	float d1 = fabs(numDown-num);
	float d2 = fabs(numUp-num);

	if (d1 < t)
		num = numDown;
	else if (d2 < t)
		num = numUp;
}

/**
 * Converts the angle from degrees to radians and stores it in the reference angle.
 */
void Mathf::degreeToRadian(float & angle) {
	angle = angle * PI/180;
}

/**
 * Returns true if /em n is a prime number, false otherwise.
 * A prime number (or a prime) is a natural number greater than 1 that has
 * no positive divisors other than 1 and itself.
 */
const bool Mathf::isPrime(const int n) {
	if (n < 2) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;

	for(int i=3; (i*i)<=n; i+=2){
		if(n % i == 0 ) return false;
	}
	return true;
}

/**
 * Converts the angle from radians to degrees and stores it in the reference angle.
 */
void Mathf::radianToDegree(float & angle) {
	angle = angle * 180/PI;
}

/**
 * Rounds a float to the number of decimal places specified.
 */
const float Mathf::roundTo(const float f, const int decimalPlaces) {
	float n = 1 * pow(10, decimalPlaces);
	return (f*n)/n;
}

}
