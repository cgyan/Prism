/*
 * type.h
 * v1
 *
 *  Created on: Oct 29, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_TYPE_H_
#define PRISM_TYPE_H_

// https://howardhinnant.github.io/TypeHiearchy.pdf

// conditional_type<>
// IsFloatingPoint<>
// IsIntegral<>
// IsArithmetic<>
// IsFundamental<>
// IsSame<>

#include <cstddef> // for std::nullptr_t
#include <prism/h/global.h>

PRISM_BEGIN_NS
//============================================================================================
// IntegralConstant
// -- defines a compile time constant integral value
//============================================================================================
template <typename T, T v>
struct IntegralConstant {
	typedef T 						value_type;
	static constexpr value_type 	value = v;
	typedef IntegralConstant<T,v>	type;
};
typedef IntegralConstant<bool,true> 	TrueType;
typedef IntegralConstant<bool,false> 	FalseType;
//============================================================================================
// RemoveConst
//============================================================================================
template <typename T>
struct RemoveConst {
	typedef T type;
};
template <typename T>
struct RemoveConst<const T> {
	typedef T type;
};
//============================================================================================
// RemoveVolatile
//============================================================================================
template <typename T>
struct RemoveVolatile {
	typedef T type;
};
template <typename T>
struct RemoveVolatile<volatile T> {
	typedef T type;
};
//============================================================================================
// RemoveConstVolatile
//============================================================================================
template <typename T>
struct RemoveConstVolatile {
	typedef typename prism::RemoveVolatile<typename prism::RemoveConst<T>::type>::type type;
};
//============================================================================================
// conditional_type
//============================================================================================
// conditional_type is a struct that has a single member called type.
// If condition is true then type's data type is set to Type1's data type.
// If condition is false then type's data type is set to Type2's data type.
//
// prism::conditional_type<true, int, String>::type t; // type of t is int
// prism::conditional_type<false, int, String>::type t; // type of t is String
template <bool condition, class T1, class T2>
struct conditional_type {
	typedef T1 type;
};

template <class T1, class T2>
struct conditional_type<false, T1, T2> {
	typedef T2 type;
};
//============================================================================================
// Or
// -- B1 and B2 are templated type structs such as IsIntegral or IsVoid. If B1's value is
// -- true then the conditional_type will resolve to that struct as a base class (and if
// -- false will resolve to B2 as a base class). These structs are all subclasses of
// -- TrueType or FalseType.
//============================================================================================
template <typename B1, typename B2>
struct Or : public prism::conditional_type<B1::value, B1, B2>::type
{};
//============================================================================================
// IsFloatingPoint
//============================================================================================
PRISM_BEGIN_PRIV_NS
template <typename T>
struct IsFloatingPoint_aux : public FalseType
{};
template <>
struct IsFloatingPoint_aux<float> : public TrueType
{};
template <>
struct IsFloatingPoint_aux<double> : public TrueType
{};
template <>
struct IsFloatingPoint_aux<long double> : public TrueType
{};
PRISM_END_PRIV_NS
template <typename T>
struct IsFloatingPoint
		: public priv::IsFloatingPoint_aux<
			typename prism::RemoveConstVolatile<T>::type
			>::type
{};
//============================================================================================
// IsIntegral
//============================================================================================
PRISM_BEGIN_PRIV_NS
template <typename T>
struct IsIntegral_aux : public FalseType
{};
template <>
struct IsIntegral_aux<bool> : public TrueType
{};
template <>
struct IsIntegral_aux<char> : public TrueType
{};
template <>
struct IsIntegral_aux<signed char> : public TrueType
{};
template <>
struct IsIntegral_aux<unsigned char> : public TrueType
{};
template <>
struct IsIntegral_aux<short> : public TrueType
{};
template <>
struct IsIntegral_aux<unsigned short> : public TrueType
{};
template <>
struct IsIntegral_aux<int> : public TrueType
{};
template <>
struct IsIntegral_aux<unsigned int> : public TrueType
{};
template <>
struct IsIntegral_aux<long> : public TrueType
{};
template <>
struct IsIntegral_aux<unsigned long> : public TrueType
{};
template <>
struct IsIntegral_aux<long long> : public TrueType
{};
template <>
struct IsIntegral_aux<unsigned long long> : public TrueType
{};
PRISM_END_PRIV_NS
template <typename T>
struct IsIntegral
		: public priv::IsIntegral_aux <
		  	  typename prism::RemoveConstVolatile<T>::type
		  >::type
{};
//============================================================================================
// IsVoid
//============================================================================================
PRISM_BEGIN_PRIV_NS
template <typename T>
struct IsVoid_aux : public FalseType
{};
template <>
struct IsVoid_aux<void> : public TrueType
{};
PRISM_END_PRIV_NS
template <typename T>
struct IsVoid
		: public priv::IsVoid_aux<
		  	  typename prism::RemoveConstVolatile<T>::type
		  >::type
{};
//============================================================================================
// IsArithmetic
// -- Arithmetic types are any type that are integral or floating point
//============================================================================================
template <typename T>
struct IsArithmetic
		: public prism::Or<
		  	  prism::IsIntegral<T>,
		  	  prism::IsFloatingPoint<T>
		  >::type
{};
//============================================================================================
// FundamentalType
// -- a fundamental type is an arithmetic or void type as well as a nullptr_t type
//============================================================================================
template <typename T>
struct IsFundamental
	: public prism::Or<
	  	  prism::IsArithmetic<T>,
	  	  prism::IsVoid<T>
	  >::type
{};
//============================================================================================
// AreSame
//============================================================================================
PRISM_BEGIN_PRIV_NS
template <typename T, typename U>
struct AreSame_aux : public FalseType
{};
template <typename T>
struct AreSame_aux<T,T> : public TrueType
{};
PRISM_END_PRIV_NS
template <typename T, typename U>
struct AreSame
		: public priv::AreSame_aux<T,U>::type
{};

PRISM_END_NS



#endif /* PRISM_TYPE_H_ */

