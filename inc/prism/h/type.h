/*
 * type.h
 * v1
 *
 *  Created on: Oct 29, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_TYPE_H_
#define PRISM_TYPE_H_

#include <cstddef> // for std::nullptr_t

namespace prism {

// https://howardhinnant.github.io/TypeHiearchy.pdf

//============================================================================================
// conditional_type
//============================================================================================
/*
 * conditional_type is a struct that has a single member called type.
 * If condition is true then type's data type is set to Type1's data type.
 * If condition is false then type's data type is set to Type2's data type.
 *
 * prism::conditional_type<true, int, String>::type t; // type of t is int
 * prism::conditional_type<false, int, String>::type t; // type of t is String
 */
template <bool condition, class T1, class T2>
struct conditional_type {
	typedef T1 type;
};

template <class T1, class T2>
struct conditional_type<false, T1, T2> {
	typedef T2 type;
};
//============================================================================================
// IsFloatingPoint
//============================================================================================
template <typename T>
struct IsFloatingPoint {
	enum { YES=0, NO=1 };
};

#define PRISM_MAKE_IS_FLOATING_POINT(T) 	\
template <> 								\
struct IsFloatingPoint<T> { 				\
	enum { YES=1, NO=0 }; 					\
};

PRISM_MAKE_IS_FLOATING_POINT(float)
PRISM_MAKE_IS_FLOATING_POINT(double)
PRISM_MAKE_IS_FLOATING_POINT(long double)
#undef PRISM_MAKE_IS_FLOATING_POINT

//============================================================================================
// IsIntegral
//============================================================================================
template <typename T>
struct IsIntegral {
	enum { YES=0, NO=1 };
};

#define PRISM_MAKE_IS_INTEGRAL(T) 		\
template <>								\
struct IsIntegral<T> {					\
	enum { YES=1, NO=0 };				\
};
PRISM_MAKE_IS_INTEGRAL(bool)
PRISM_MAKE_IS_INTEGRAL(char)
PRISM_MAKE_IS_INTEGRAL(signed char)
PRISM_MAKE_IS_INTEGRAL(unsigned char)
PRISM_MAKE_IS_INTEGRAL(short)
PRISM_MAKE_IS_INTEGRAL(unsigned short)
PRISM_MAKE_IS_INTEGRAL(int)
PRISM_MAKE_IS_INTEGRAL(unsigned)
PRISM_MAKE_IS_INTEGRAL(long)
PRISM_MAKE_IS_INTEGRAL(unsigned long)
PRISM_MAKE_IS_INTEGRAL(long long)
PRISM_MAKE_IS_INTEGRAL(unsigned long long)
#undef PRISM_MAKE_IS_INTEGRAL

//============================================================================================
// IsArithmetic
// -- Arithmetic types are any type that are integral or floating point
//============================================================================================
template <typename T>
struct IsArithmetic {
	enum {
		YES = 	bool(prism::IsIntegral<T>::YES) 		||
				bool(prism::IsFloatingPoint<T>::YES),
		NO = !YES
	};
};
//============================================================================================
// FundamentalType
// -- a fundamental type is an arithmetic or void type as well as a nullptr_t type
//============================================================================================
template <typename T>
struct IsFundamental {
	enum {
		YES = bool(prism::IsArithmetic<T>::YES),
		NO = !YES
	};
};
#define PRISM_MAKE_IS_FUNDAMENTAL(T) 		\
template <>									\
struct IsFundamental<T> {					\
	enum { YES = 1, NO = 0 };				\
};
PRISM_MAKE_IS_FUNDAMENTAL(void)
PRISM_MAKE_IS_FUNDAMENTAL(std::nullptr_t)
#undef PRISM_MAKE_IS_FUNDAMENTAL

} // end namespace prism



#endif /* PRISM_TYPE_H_ */

