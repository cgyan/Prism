///*
// * type.h
// * v1
// *
// *  Created on: Oct 29, 2016
// *      Author: iainhemstock
// */
//
#ifndef PRISM_TYPE_H_
#define PRISM_TYPE_H_
//
//// https://howardhinnant.github.io/TypeHiearchy.pdf
//
///*
//is_class
//is_enum
//is_lvalue_reference
//is_union
//is_compound
//is_object
//is_scalar
//
//is_abstract
//is_empty
//is_literal_type
//is_pod
//is_polymorphic
//is_signed
//is_standard_layout
//is_trivial
//is_trivially_copyable
//is_unsigned
//
// *
// */
//
#include <cstddef> // for std::nullptr_t
#include <prism/h/global.h>

PRISM_BEGIN_NAMESPACE
////============================================================================================
//// IntegralConstant
//// -- defines a compile time constant integral value
////============================================================================================
//template <typename T, T v>
//struct IntegralConstant {
//	typedef T 						value_type;
//	static constexpr value_type 	value = v;
//	typedef IntegralConstant<T,v>	type;
//};
//typedef IntegralConstant<bool,true> 	TrueType;
//typedef IntegralConstant<bool,false> 	FalseType;
////============================================================================================
//// RemoveConst
////============================================================================================
//template <typename T>
//struct RemoveConst {
//	typedef T type;
//};
//template <typename T>
//struct RemoveConst<const T> {
//	typedef T type;
//};
//template <typename T>
//using RemoveConst_t = typename prism::RemoveConst<T>::type;
////============================================================================================
//// RemoveVolatile
////============================================================================================
//template <typename T>
//struct RemoveVolatile {
//	typedef T type;
//};
//template <typename T>
//struct RemoveVolatile<volatile T> {
//	typedef T type;
//};
//template <typename T>
//using RemoveVolatile_t = typename prism::RemoveVolatile<T>::type;
////============================================================================================
//// RemoveConstVolatile
////============================================================================================
//template <typename T>
//struct RemoveConstVolatile {
//	typedef typename prism::RemoveVolatile<
//				typename prism::RemoveConst<T>::type
//			>::type type;
//};
//template <typename T>
//using RemoveConstVolatile_t = typename prism::RemoveConstVolatile<T>::type;
////============================================================================================
//// IsConst
////============================================================================================
//PRISM_BEGIN_PRIVATE_NAMESPACE
//template <typename T>
//struct IsConst_aux : public FalseType
//{};
//template <typename T>
//struct IsConst_aux<const T> : public TrueType
//{};
//PRISM_END_PRIVATE_NAMESPACE
//template <typename T>
//struct IsConst
//	: public prism_private::IsConst_aux<
//	  	  typename prism::RemoveVolatile<T>::type
//	  >::type
//{};
////============================================================================================
//// IsVolatile
////============================================================================================
//PRISM_BEGIN_PRIVATE_NAMESPACE
//template <typename T>
//struct IsVolatile_aux : public FalseType
//{};
//template <typename T>
//struct IsVolatile_aux<volatile T> : public TrueType
//{};
//PRISM_END_PRIVATE_NAMESPACE
//template <typename T>
//struct IsVolatile
//	: public prism_private::IsVolatile_aux<
//	  	  typename prism::RemoveConst<T>::type
//	  >::type
//{};
//============================================================================================
// ConditionalType
//============================================================================================
// conditional_type is a struct that has a single member called type.
// If condition is true then type's data type is set to Type1's data type.
// If condition is false then type's data type is set to Type2's data type.
//
// prism::conditional_type<true, int, String>::type t; // type of t is int
// prism::conditional_type<false, int, String>::type t; // type of t is String
template <bool condition, class T1, class T2>
struct ConditionalType {
	typedef T1 type;
};

template <class T1, class T2>
struct ConditionalType<false, T1, T2> {
	typedef T2 type;
};
template <bool condition, typename T1, typename T2>
using ConditionalType_t = typename prism::ConditionalType<condition,T1,T2>::type;
////============================================================================================
//// Or
//// -- TraitClass1 and TraitClass2 are templated type structs such as IsIntegral or IsVoid. If
//// -- TraitClass1's value is true then the conditional_type will resolve to that struct as a
//// -- base class (and if false will resolve to B2 as a base class). These structs are all
//// -- subclasses of TrueType or FalseType.
////============================================================================================
//template <typename TraitClass1, typename TraitClass2>
//struct Or
//	: public prism::ConditionalType<TraitClass1::value, TraitClass1, TraitClass2>::type
//{};
////============================================================================================
//// IsFloatingPoint
////============================================================================================
//PRISM_BEGIN_PRIVATE_NAMESPACE
//template <typename T>
//struct IsFloatingPoint_aux : public FalseType
//{};
//template <>
//struct IsFloatingPoint_aux<float> : public TrueType
//{};
//template <>
//struct IsFloatingPoint_aux<double> : public TrueType
//{};
//template <>
//struct IsFloatingPoint_aux<long double> : public TrueType
//{};
//PRISM_END_PRIVATE_NAMESPACE
//template <typename T>
//struct IsFloatingPoint
//		: public prism_private::IsFloatingPoint_aux<
//			typename prism::RemoveConstVolatile<T>::type
//			>::type
//{};
////============================================================================================
//// IsIntegral
////============================================================================================
//PRISM_BEGIN_PRIVATE_NAMESPACE
//template <typename T>
//struct IsIntegral_aux : public FalseType
//{};
//template <>
//struct IsIntegral_aux<bool> : public TrueType
//{};
//template <>
//struct IsIntegral_aux<char> : public TrueType
//{};
//template <>
//struct IsIntegral_aux<signed char> : public TrueType
//{};
//template <>
//struct IsIntegral_aux<unsigned char> : public TrueType
//{};
//template <>
//struct IsIntegral_aux<short> : public TrueType
//{};
//template <>
//struct IsIntegral_aux<unsigned short> : public TrueType
//{};
//template <>
//struct IsIntegral_aux<int> : public TrueType
//{};
//template <>
//struct IsIntegral_aux<unsigned int> : public TrueType
//{};
//template <>
//struct IsIntegral_aux<long> : public TrueType
//{};
//template <>
//struct IsIntegral_aux<unsigned long> : public TrueType
//{};
//template <>
//struct IsIntegral_aux<long long> : public TrueType
//{};
//template <>
//struct IsIntegral_aux<unsigned long long> : public TrueType
//{};
//PRISM_END_PRIVATE_NAMESPACE
//template <typename T>
//struct IsIntegral
//		: public prism_private::IsIntegral_aux <
//		  	  typename prism::RemoveConstVolatile<T>::type
//		  >::type
//{};
////============================================================================================
//// IsVoid
////============================================================================================
//PRISM_BEGIN_PRIVATE_NAMESPACE
//template <typename T>
//struct IsVoid_aux : public FalseType
//{};
//template <>
//struct IsVoid_aux<void> : public TrueType
//{};
//PRISM_END_PRIVATE_NAMESPACE
//template <typename T>
//struct IsVoid
//		: public prism_private::IsVoid_aux<
//		  	  typename prism::RemoveConstVolatile<T>::type
//		  >::type
//{};
////============================================================================================
//// IsArithmetic
//// -- Arithmetic types are any type that are integral or floating point
////============================================================================================
//template <typename T>
//struct IsArithmetic
//		: public prism::Or<
//		  	  prism::IsIntegral<T>,
//		  	  prism::IsFloatingPoint<T>
//		  >::type
//{};
////============================================================================================
//// FundamentalType
//// -- a fundamental type is an arithmetic or void type as well as a nullptr_t type
////============================================================================================
//template <typename T>
//struct IsFundamental
//	: public prism::Or<
//	  	  prism::IsArithmetic<T>,
//	  	  prism::IsVoid<T>
//	  >::type
//{};
////============================================================================================
//// IsSigned
////============================================================================================
//PRISM_BEGIN_PRIVATE_NAMESPACE
//template <typename T, bool = prism::IsArithmetic<T>::value>
//struct IsSigned_aux : public FalseType
//{};
//template <typename T>
//struct IsSigned_aux<T,true> : public prism::IntegralConstant<bool, T(-1) < T(0)>
//{};
//PRISM_END_PRIVATE_NAMESPACE
//template <typename T>
//struct IsSigned
//	: public prism_private::IsSigned_aux<T>::type
//{};
////============================================================================================
//// IsUnsigned
////============================================================================================
//PRISM_BEGIN_PRIVATE_NAMESPACE
//template <typename T, bool = prism::IsArithmetic<T>::value>
//struct IsUnsigned_aux : FalseType
//{};
//template <typename T>
//struct IsUnsigned_aux<T,true>
//	: public prism::IntegralConstant<bool, !prism::IsSigned<T>::value>::type
//{};
//PRISM_END_PRIVATE_NAMESPACE
//template <typename T>
//struct IsUnsigned
//	: public prism_private::IsUnsigned_aux<T>::type
//{};
////============================================================================================
//// AreSame
////============================================================================================
//PRISM_BEGIN_PRIVATE_NAMESPACE
//template <typename T, typename U>
//struct AreSame_aux : public FalseType
//{};
//template <typename T>
//struct AreSame_aux<T,T> : public TrueType
//{};
//PRISM_END_PRIVATE_NAMESPACE
//template <typename T, typename U>
//struct AreSame
//		: public prism_private::AreSame_aux<T,U>::type
//{};
////============================================================================================
//// IsPointer
////============================================================================================
//PRISM_BEGIN_PRIVATE_NAMESPACE
//template <typename T>
//struct IsPointer_aux : public FalseType
//{};
//template <typename T>
//struct IsPointer_aux<T*> : public TrueType
//{};
//PRISM_END_PRIVATE_NAMESPACE
//template <typename T>
//struct IsPointer
//		: public prism_private::IsPointer_aux<
//		  	  typename prism::RemoveConstVolatile<T>::type
//		  >::type
//{};
////============================================================================================
//// IsLValueReference
////============================================================================================
//PRISM_BEGIN_PRIVATE_NAMESPACE
//template <typename T>
//struct IsLValueReference_aux : public FalseType
//{};
//template <typename T>
//struct IsLValueReference_aux<T&> : public TrueType
//{};
//PRISM_END_PRIVATE_NAMESPACE
//template <typename T>
//struct IsLValueReference
//		: public prism_private::IsLValueReference_aux<
//		  	  typename prism::RemoveConstVolatile<T>::type
//		  >::type
//{};
////============================================================================================
//// IsRValueReference
////============================================================================================
//PRISM_BEGIN_PRIVATE_NAMESPACE
//template <typename T>
//struct IsRValueReference_aux : public FalseType
//{};
//template <typename T>
//struct IsRValueReference_aux<T&&> : public TrueType
//{};
//PRISM_END_PRIVATE_NAMESPACE
//template <typename T>
//struct IsRValueReference
//	: public prism_private::IsRValueReference_aux<
//	  	  typename prism::RemoveConstVolatile<T>::type
//	  >::type
//{};
////============================================================================================
//// IsReference
////============================================================================================
//template <typename T>
//struct IsReference
//	: public prism::Or<
//	  	  prism::IsLValueReference<T>,
//	  	  prism::IsRValueReference<T>
//	  >::type
//{};
////============================================================================================
//// IsArray
////============================================================================================
//PRISM_BEGIN_PRIVATE_NAMESPACE
//template <typename T>
//struct IsArray_aux : public FalseType
//{};
//template <typename T, size_t num>
//struct IsArray_aux<T[num]> : public TrueType
//{};
//template <typename T> // support for zero sized array
//struct IsArray_aux<T[]> : public TrueType
//{};
//PRISM_END_PRIVATE_NAMESPACE
//template <typename T>
//struct IsArray
//	: public prism_private::IsArray_aux<
//	  	  typename prism::RemoveConstVolatile<T>::type
//	  >::type
//{};
////============================================================================================
//// IsFunction
////============================================================================================
//PRISM_BEGIN_PRIVATE_NAMESPACE
//template <typename T>
//struct IsFunction_aux : public FalseType
//{};
//template <typename Ret, typename ...Args>
//struct IsFunction_aux<Ret(Args...)> : public TrueType
//{};
//PRISM_END_PRIVATE_NAMESPACE
//template <typename T>
//struct IsFunction
//	: public prism_private::IsFunction_aux<T>::type
//{};
////============================================================================================
//// IsMemberPointer
////============================================================================================
//PRISM_BEGIN_PRIVATE_NAMESPACE
//template <typename T>
//struct IsMemberPointer_aux : public FalseType
//{};
//template <typename T, typename C>
//struct IsMemberPointer_aux<T C::*> : public TrueType
//{};
//PRISM_END_PRIVATE_NAMESPACE
//template <typename T>
//struct IsMemberPointer
//	: public prism_private::IsMemberPointer_aux<
//	  	  typename prism::RemoveConstVolatile<T>::type
//	  >::type
//{};
////============================================================================================
//// IsMemberFunctionPointer
////============================================================================================
//PRISM_BEGIN_PRIVATE_NAMESPACE
//template <typename T>
//struct IsMemberFunctionPointer_aux : public FalseType
//{};
//template <typename T, typename C>
//struct IsMemberFunctionPointer_aux<T C::*>
//	: prism::IntegralConstant<bool, prism::IsFunction<T>::value>
//{};
//PRISM_END_PRIVATE_NAMESPACE
//template <typename T>
//struct IsMemberFunctionPointer
//	: public prism_private::IsMemberFunctionPointer_aux<
//	  	  typename prism::RemoveConstVolatile<T>::type
//	  >::type
//{};
////============================================================================================
//// IsMemberObjectPointer
////============================================================================================
//PRISM_BEGIN_PRIVATE_NAMESPACE
//template <typename T>
//struct IsMemberObjectPointer_aux : public FalseType
//{};
//template <typename T, typename C>
//struct IsMemberObjectPointer_aux<T C::*>
//	: prism::IntegralConstant<bool, !prism::IsFunction<T>::value>
//{};
//PRISM_END_PRIVATE_NAMESPACE
//template <typename T>
//struct IsMemberObjectPointer
//	: public prism_private::IsMemberObjectPointer_aux<
//	  	  typename prism::RemoveConstVolatile<T>::type
//	  >::type
//{};
//
PRISM_END_NAMESPACE



#endif /* PRISM_TYPE_H_ */
//
//
//
//
//
//
//
//
