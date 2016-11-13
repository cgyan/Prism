/*
 * type_traits.h
 * v1
 *
 *  Created on: Oct 29, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_TYPE_TRAITS_H_
#define PRISM_TYPE_TRAITS_H_

// https://howardhinnant.github.io/TypeHiearchy.pdf

/*
is_union
is_enum

is_abstract
is_empty
is_literal_type
is_pod
is_polymorphic
is_standard_layout
is_trivial
is_trivially_copyable

 *
 */

#include <cstddef> // for std::nullptr_t
#include <prism/h/global.h>

PRISM_BEGIN_NAMESPACE
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
	typedef typename prism::RemoveVolatile<
				typename prism::RemoveConst<T>::type
			>::type type;
};
//============================================================================================
// IsConst
//============================================================================================
template <typename>
struct IsConst : public FalseType
{};
template <typename T>
struct IsConst<const T> : public TrueType
{};
//============================================================================================
// IsVolatile
//============================================================================================
template <typename>
struct IsVolatile : public FalseType
{};
template <typename T>
struct IsVolatile<volatile T> : public TrueType
{};
//============================================================================================
// ConditionalType
//============================================================================================
// conditional_type is a struct that has a single member called type.
// If condition is true then type's data type is set to Type1's data type.
// If condition is false then type's data type is set to Type2's data type.
//
// prism::conditional_type<true, int, String>::type t; // type of t is int
// prism::conditional_type<false, int, String>::type t; // type of t is String
template <bool condition, typename T1, typename T2>
struct ConditionalType {
	typedef T1 type;
};

template <typename T1, typename T2>
struct ConditionalType<false, T1, T2> {
	typedef T2 type;
};
//============================================================================================
// Or
// -- The base class's 'value' member will resolve to true if either MF1 or
// -- MF2's value is true and false otherwise
//============================================================================================
template <typename...>
struct Or;
template <>
struct Or<> : public FalseType
{};
template <typename MF1> // MetaFunction
struct Or<MF1>
	: public MF1
{};
template <typename MF1, typename MF2>
struct Or<MF1, MF2>
	: public prism::ConditionalType<MF1::value, MF1, MF2>::type
{};
template <typename MF1, typename MF2, typename MF3, typename ...MF_N>
struct Or<MF1,MF2,MF3,MF_N...>
	: public prism::ConditionalType<MF1::value, MF1, prism::Or<MF2, MF3, MF_N...>>::type
{};
//============================================================================================
// And
// -- The base class's 'value' member will resolve to true if both MF1 and
// -- MF2's values are true and false otherwise
//============================================================================================
template <typename...>
struct And;
template <>
struct And<> : public FalseType
{};
template <typename MF1> // MetaFunction
struct And<MF1>
	: public MF1
{};
template <typename MF1, typename MF2>
struct And<MF1,MF2>
	: public prism::ConditionalType<MF1::value, MF2, MF1>::type
{};
template <typename MF1, typename MF2, typename MF3, typename ...MF_N>
struct And<MF1,MF2,MF3,MF_N...>
	: public prism::ConditionalType<MF1::value, MF1, prism::And<MF2, MF3, MF_N...>>::type
{};
//============================================================================================
// IsFloatingPoint
//============================================================================================
PRISM_BEGIN_PRIVATE_NAMESPACE
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
PRISM_END_PRIVATE_NAMESPACE
template <typename T>
struct IsFloatingPoint
		: public prism_private::IsFloatingPoint_aux<
			typename prism::RemoveConstVolatile<T>::type
			>::type
{};
//============================================================================================
// IsIntegral
//============================================================================================
PRISM_BEGIN_PRIVATE_NAMESPACE
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
PRISM_END_PRIVATE_NAMESPACE
template <typename T>
struct IsIntegral
		: public prism_private::IsIntegral_aux <
		  	  typename prism::RemoveConstVolatile<T>::type
		  >::type
{};
//============================================================================================
// IsVoid
//============================================================================================
PRISM_BEGIN_PRIVATE_NAMESPACE
template <typename T>
struct IsVoid_aux : public FalseType
{};
template <>
struct IsVoid_aux<void> : public TrueType
{};
PRISM_END_PRIVATE_NAMESPACE
template <typename T>
struct IsVoid
		: public prism_private::IsVoid_aux<
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
template <>
struct IsFundamental<std::nullptr_t> : public TrueType
{};
//============================================================================================
// IsSigned
//============================================================================================
PRISM_BEGIN_PRIVATE_NAMESPACE
template <typename T, bool = prism::IsArithmetic<T>::value>
struct IsSigned_aux : public FalseType
{};
template <typename T>
struct IsSigned_aux<T,true> : public prism::IntegralConstant<bool, T(-1) < T(0)>
{};
PRISM_END_PRIVATE_NAMESPACE
template <typename T>
struct IsSigned
	: public prism_private::IsSigned_aux<T>::type
{};
//============================================================================================
// IsUnsigned
//============================================================================================
PRISM_BEGIN_PRIVATE_NAMESPACE
template <typename T, bool = prism::IsArithmetic<T>::value>
struct IsUnsigned_aux : FalseType
{};
template <typename T>
struct IsUnsigned_aux<T,true>
	: public prism::IntegralConstant<bool, !prism::IsSigned<T>::value>::type
{};
PRISM_END_PRIVATE_NAMESPACE
template <typename T>
struct IsUnsigned
	: public prism_private::IsUnsigned_aux<T>::type
{};
//============================================================================================
// IsSame
//============================================================================================
PRISM_BEGIN_PRIVATE_NAMESPACE
template <typename T, typename U>
struct IsSame_aux : public FalseType
{};
template <typename T>
struct IsSame_aux<T,T> : public TrueType
{};
PRISM_END_PRIVATE_NAMESPACE
template <typename T, typename U>
struct IsSame
		: public prism_private::IsSame_aux<T,U>::type
{};
//============================================================================================
// IsPointer
//============================================================================================
PRISM_BEGIN_PRIVATE_NAMESPACE
template <typename T>
struct IsPointer_aux : public FalseType
{};
template <typename T>
struct IsPointer_aux<T*> : public TrueType
{};
PRISM_END_PRIVATE_NAMESPACE
template <typename T>
struct IsPointer
		: public prism_private::IsPointer_aux<
		  	  typename prism::RemoveConstVolatile<T>::type
		  >::type
{};
//============================================================================================
// IsLValueReference
//============================================================================================
PRISM_BEGIN_PRIVATE_NAMESPACE
template <typename T>
struct IsLValueReference_aux : public FalseType
{};
template <typename T>
struct IsLValueReference_aux<T&> : public TrueType
{};
PRISM_END_PRIVATE_NAMESPACE
template <typename T>
struct IsLValueReference
		: public prism_private::IsLValueReference_aux<
		  	  typename prism::RemoveConstVolatile<T>::type
		  >::type
{};
//============================================================================================
// IsRValueReference
//============================================================================================
PRISM_BEGIN_PRIVATE_NAMESPACE
template <typename T>
struct IsRValueReference_aux : public FalseType
{};
template <typename T>
struct IsRValueReference_aux<T&&> : public TrueType
{};
PRISM_END_PRIVATE_NAMESPACE
template <typename T>
struct IsRValueReference
	: public prism_private::IsRValueReference_aux<
	  	  typename prism::RemoveConstVolatile<T>::type
	  >::type
{};
//============================================================================================
// IsReference
//============================================================================================
template <typename T>
struct IsReference
	: public prism::Or<
	  	  prism::IsLValueReference<T>,
	  	  prism::IsRValueReference<T>
	  >::type
{};
//============================================================================================
// IsReferenceable
//============================================================================================
template <typename T>
struct IsObject;
template <typename T>
struct IsFunction;

template <typename T>
struct IsReferenceable
	: public prism::Or<
	  	  prism::IsObject<T>,
	  	  prism::IsReference<T>,
	  	  prism::IsFunction<T>
	  >::type
{};
//============================================================================================
// IsArray
//============================================================================================
PRISM_BEGIN_PRIVATE_NAMESPACE
template <typename T>
struct IsArray_aux : public FalseType
{};
template <typename T, size_t num>
struct IsArray_aux<T[num]> : public TrueType
{};
template <typename T> // support for zero sized array
struct IsArray_aux<T[]> : public TrueType
{};
PRISM_END_PRIVATE_NAMESPACE
template <typename T>
struct IsArray
	: public prism_private::IsArray_aux<
	  	  typename prism::RemoveConstVolatile<T>::type
	  >::type
{};
//============================================================================================
// IsFunction
//============================================================================================
PRISM_BEGIN_PRIVATE_NAMESPACE
template <typename T>
struct IsFunction_aux : public FalseType
{};
template <typename Ret, typename ...Args>
struct IsFunction_aux<Ret(Args...)> : public TrueType
{};
PRISM_END_PRIVATE_NAMESPACE
template <typename T>
struct IsFunction
	: public prism_private::IsFunction_aux<T>::type
{};
//============================================================================================
// IsMemberFunctionPointer
//============================================================================================
PRISM_BEGIN_PRIVATE_NAMESPACE
template <typename T>
struct IsMemberFunctionPointer_aux : public FalseType
{};
template <typename T, typename C>
struct IsMemberFunctionPointer_aux<T C::*>
	: prism::IntegralConstant<bool, prism::IsFunction<T>::value>
{};
PRISM_END_PRIVATE_NAMESPACE
template <typename T>
struct IsMemberFunctionPointer
	: public prism_private::IsMemberFunctionPointer_aux<
	  	  typename prism::RemoveConstVolatile<T>::type
	  >::type
{};
//============================================================================================
// IsMemberObjectPointer
//============================================================================================
PRISM_BEGIN_PRIVATE_NAMESPACE
template <typename T>
struct IsMemberObjectPointer_aux : public FalseType
{};
template <typename T, typename C>
struct IsMemberObjectPointer_aux<T C::*>
	: prism::IntegralConstant<bool, !prism::IsFunction<T>::value>
{};
PRISM_END_PRIVATE_NAMESPACE
template <typename T>
struct IsMemberObjectPointer
	: public prism_private::IsMemberObjectPointer_aux<
	  	  typename prism::RemoveConstVolatile<T>::type
	  >::type
{};
//============================================================================================
// IsMemberPointer
//============================================================================================
PRISM_BEGIN_PRIVATE_NAMESPACE
template <typename T>
struct IsMemberPointer_aux : public FalseType
{};
template <typename T, typename C>
struct IsMemberPointer_aux<T C::*> : public TrueType
{};
PRISM_END_PRIVATE_NAMESPACE
template <typename T>
struct IsMemberPointer
	: public prism::Or<
	  	  	  	  prism::IsMemberFunctionPointer<T>,
	  	  	  	  prism::IsMemberObjectPointer<T>
			 >::type
{};
//============================================================================================
// IsClass
// todo currently IsClass returns true for unions when unions are not technically classes
// although are closely related
//============================================================================================
PRISM_BEGIN_PRIVATE_NAMESPACE
template <typename T>
struct IsClass_aux {
	typedef char One;
	typedef struct { char a[2]; } Two;

	template <typename C>
	static One test(int C::*);

	template <typename C>
	static Two test(...);

	static constexpr bool value = sizeof(IsClass_aux<T>::template test<T>(nullptr)) == 1;
};
PRISM_END_PRIVATE_NAMESPACE
template <typename T>
struct IsClass
	: public prism::ConditionalType<
	  	  prism_private::IsClass_aux<T>::value,
	  	  TrueType,
	  	  FalseType
	  >::type
{};
//============================================================================================
// IsEnum
//============================================================================================
//PRISM_BEGIN_PRIVATE_NAMESPACE
//struct SizeBiggerThanOne { char a[2]; };
//struct EnumChecks {
//	static char enum_check(bool);
//	static char enum_check(char);
//	static char enum_check(signed char);
//	static char enum_check(unsigned char);
//	static char enum_check(wchar_t);
//	static char enum_check(signed short);
//	static char enum_check(unsigned short);
//	static char enum_check(signed int);
//	static char enum_check(unsigned int);
//	static char enum_check(signed long);
//	static char enum_check(unsigned long);
//	static char enum_check(signed long long);
//	static char enum_check(unsigned long long);
//	static char enum_check(float);
//	static char enum_check(double);
//	static char enum_check(long double);
//	static SizeBiggerThanOne enum_check(...);
//};
//// this is instantiated for everything except functions and arrays
//template <typename T,
//	bool is_convertible = !prism::IsFunction<T>::value && !prism::IsArray<T>::value>
//struct IsEnum_aux {
//	operator T() const;
//};
//// this is instantiated for functions and arrays
//template <typename T>
//struct IsEnum_aux<T,false>
//{};
//// this is instantiated for void types
//template <bool is_convertible>
//struct IsEnum_aux<void, is_convertible>
//{};
//PRISM_END_PRIVATE_NAMESPACE
//template <typename T>
//struct IsEnum
//	: public prism::ConditionalType<
//			!prism::IsFundamental<T>::value && !prism::IsPointer<T>::value &&
//			!prism::IsReference<T>::value && !prism::IsMemberPointer<T>::value &&
//			sizeof(prism_private::EnumChecks::enum_check(prism_private::IsEnum_aux<T>())) == 1,
//		TrueType,
//		FalseType
//	  >::type
//{};

// todo this whole IsEnum<> metafunction is not working correctly so as a workaround it returns
// false for any type for now as a safety precaution
template <typename T>
struct IsEnum : public FalseType
{};
//============================================================================================
// IsCompound
//============================================================================================
template <typename T>
struct IsCompound
	: public prism::Or<
	  	  prism::IsFunction<T>,
	  	  prism::IsReference<T>,
	  	  prism::IsClass<T>,
	  	  prism::IsArray<T>,
	  	  prism::IsPointer<T>,
	  	  prism::IsMemberPointer<T>,
		  prism::IsEnum<T>
	  >::type
{};
//============================================================================================
// IsScalar
//============================================================================================
template <typename T>
struct IsScalar
	: public prism::Or<
	  	  prism::IsArithmetic<T>,
	  	  prism::IsMemberPointer<T>,
	  	  prism::IsPointer<T>,
		  prism::IsEnum<T>
	  >::type
{};
template <>
struct IsScalar<std::nullptr_t> : public TrueType
{};
//============================================================================================
// IsObject
//============================================================================================
template <typename T>
struct IsObject
	: public prism::Or<
	  	  prism::IsScalar<T>,
	  	  prism::IsArray<T>,
	  	  // todo add prism::IsUnion<T>,
	  	  prism::IsClass<T>
	  >::type
{};
template <>
struct IsObject<std::nullptr_t> : public TrueType
{};
//============================================================================================
// AddLValueReference
//============================================================================================
PRISM_BEGIN_PRIVATE_NAMESPACE
template <typename T, bool = prism::IsReferenceable<T>::value>
struct AddLValueReference_aux {
	typedef T type;
};
template <typename T>
struct AddLValueReference_aux<T,true> {
	typedef T& type;
};
PRISM_END_PRIVATE_NAMESPACE
template <typename T>
struct AddLValueReference
	: public prism_private::AddLValueReference_aux<T>
{};
//============================================================================================
// RemoveReference
//============================================================================================
template <typename T>
struct RemoveReference {
	typedef T type;
};
template <typename T>
struct RemoveReference<T&> {
	typedef T type;
};
template <typename T>
struct RemoveReference<T&&> {
	typedef T type;
};
//============================================================================================
// move
//============================================================================================
template <typename T>
typename prism::RemoveReference<T>::type&&
move(T&& param) noexcept {
	using ReturnType = typename prism::RemoveReference<T>::type&&;
	return static_cast<ReturnType>(param);
}
//============================================================================================
// forward
//============================================================================================
template <typename T>
T&
forward(typename prism::RemoveReference<T>::type& param) {
	return param;
}
//============================================================================================
// type aliases
//============================================================================================
template <typename T>
using RemoveConst_t = typename prism::RemoveConst<T>::type;
template <typename T>
using RemoveVolatile_t = typename prism::RemoveVolatile<T>::type;
template <typename T>
using RemoveConstVolatile_t = typename prism::RemoveConstVolatile<T>::type;
template <typename T>
using IsConst_t = typename prism::IsConst<T>::type;
template <typename T>
using IsVolatile_t = typename prism::IsVolatile<T>::type;
template <typename ...MF_N>
using Or_t = typename prism::Or<MF_N...>::type;
template <bool condition, typename T1, typename T2>
using ConditionalType_t = typename prism::ConditionalType<condition,T1,T2>::type;
template <typename ...MF_N>
using And_t = typename prism::And<MF_N...>::type;
template <typename T>
using IsFloatingPoint_t = typename prism::IsFloatingPoint<T>::type;
template <typename T>
using IsIntegral_t = typename prism::IsIntegral<T>::type;
template <typename T>
using IsVoid_t = typename prism::IsVoid<T>::type;
template <typename T>
using IsArithmetic_t = typename prism::IsArithmetic<T>::type;
template <typename T>
using IsFundamental_t = typename prism::IsFundamental<T>::type;
template <typename T>
using IsSigned_t = typename prism::IsSigned<T>::type;
template <typename T>
using IsUnsigned_t = typename prism::IsUnsigned<T>::type;
template <typename T, typename U>
using AreSame_t = typename prism::IsSame<T,U>::type;
template <typename T>
using IsPointer_t = typename prism::IsPointer<T>::type;
template <typename T>
using IsLValueReference_t = typename prism::IsLValueReference<T>::type;
template <typename T>
using IsRValueReference_t = typename prism::IsRValueReference<T>::type;
template <typename T>
using IsReference_t = typename prism::IsReference<T>::type;
template <typename T>
using IsArray_t = typename prism::IsArray<T>::type;
template <typename T>
using IsFunction_t = typename prism::IsFunction<T>::type;
template <typename T>
using IsMemberFunctionPointer_t = typename prism::IsMemberFunctionPointer<T>::type;
template <typename T>
using IsMemberObjectPointer_t = typename prism::IsMemberObjectPointer<T>::type;
template <typename T>
using IsMemberPointer_t = typename prism::IsMemberPointer<T>::type;
template <typename T>
using IsClass_t = typename prism::IsClass<T>::type;
template <typename T>
using IsEnum_t = typename prism::IsEnum<T>::type;
template <typename T>
using IsCompound_t = typename prism::IsCompound<T>::type;
template <typename T>
using IsScalar_t = typename prism::IsScalar<T>::type;
template <typename T>
using IsObject_t = typename prism::IsObject<T>::type;
//============================================================================================
// value aliases
// -- variable templates not supported until c++14
//============================================================================================
#if __cplusplus >= PRISM_CXX14
template <typename T>
constexpr bool IsConst_v = prism::IsConst<T>::value;
template <typename T>
constexpr bool IsVolatile_v = prism::IsVolatile<T>::value;
template <typename ...MF_N>
constexpr bool Or_v = prism::Or<MF_N...>::value;
template <typename ...MF_N>
constexpr bool And_v = prism::And<MF_N...>::value;
template <typename T>
constexpr bool IsFloatingPoint_v = prism::IsFloatingPoint<T>::value;
template <typename T>
constexpr bool IsIntegral_v = prism::IsIntegral<T>::value;
template <typename T>
constexpr bool IsVoid_v = prism::IsVoid<T>::value;
template <typename T>
constexpr bool IsArithmetic_v = prism::IsArithmetic<T>::value;
template <typename T>
constexpr bool IsFundamental_v = prism::IsFundamental<T>::value;
template <typename T>
constexpr bool IsSigned_v = prism::IsSigned<T>::value;
template <typename T>
constexpr bool IsUnsigned_v = prism::IsUnsigned<T>::value;
template <typename T, typename U>
constexpr bool AreSame_v = prism::AreSame<T,U>::value;
template <typename T>
constexpr bool IsPointer_v = prism::IsPointer<T>::value;
template <typename T>
constexpr bool IsLValueReference_v = prism::IsLValueReference<T>::value;
template <typename T>
constexpr bool IsRValueReference_v = prism::IsRValueReference<T>::value;
template <typename T>
constexpr bool IsReference_v = prism::IsReference<T>::value;
template <typename T>
constexpr bool IsArray_v = prism::IsArray<T>::value;
template <typename T>
constexpr bool IsFunction_v = prism::IsFunction<T>::value;
template <typename T>
constexpr bool IsMemberFunctionPointer_v = prism::IsMemberFunctionPointer<T>::value;
template <typename T>
constexpr bool IsMemberObjectPointer_v = prism::IsMemberObjectPointer<T>::value;
template <typename T>
constexpr bool IsMemberPointer_v = prism::IsMemberPointer<T>::value;
template <typename T>
constexpr bool IsClass_v = prism::IsClass<T>::value;
template <typename T>
constexpr bool IsEnum_v = prism::IsEnum<T>::value;
template <typename T>
constexpr bool IsCompound_v = prism::IsCompound<T>::value;
template <typename T>
constexpr bool IsScalar_v = prism::IsScalar<T>::value;
template <typename T>
constexpr bool IsObject_v = prism::IsObject<T>::value;
#endif // __cplusplus >= 201103L

PRISM_END_NAMESPACE



#endif /* PRISM_TYPE_TRAITS_H_ */







