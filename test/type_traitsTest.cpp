/*
 * type_traitsTest.cpp
 * v1
 *
 *  Created on: Nov 2, 2016
 *      Author: iainhemstock
 *
 */

#include <gtest/gtest.h>
#include <prism/type_traits>

namespace prism {
namespace test {

class type_traitsTest : public ::testing::Test {
public:
	class C {};
	struct S {};
	union U {};
	enum E {};

	using ARRAY 							= int[1];
	using ARRAY_OF_POINTERS					= int*[1];
	using CHAR								= char;
	using CLASS								= C;
	using STRUCT							= S;
	using DOUBLE							= double;
	using LONG_DOUBLE						= long double;
	using ENUM 								= E;
	using CONST_ENUM 						= E const;
	using VOLATILE_ENUM 					= E volatile;
	using UNION 							= U;
	using CONST_UNION						= U const;
	using VOLATILE_UNION					= U volatile;
	using FLOATING_POINT					= float;
	using FLOAT 							= float;
	using CONST_FLOAT						= float const;
	using VOLATILE_FLOAT					= float volatile;
	using INTEGRAL 							= int;
	using CONST_INTEGRAL 					= int const;
	using VOLATILE_INTEGRAL					= int volatile;
	using CONST_VOLATILE_INTEGRAL			= int volatile const;
	using SIGNED_INTEGRAL					= signed int;
	using UNSIGNED_INTEGRAL					= unsigned int;
	using FUNCTION 							= int(int);
	using MEMBER_FUNCTION_POINTER 			= int (C::*)();
	using CONST_MEMBER_FUNCTION_POINTER 	= int (C::*)() const;
	using VOLATILE_MEMBER_FUNCTION_POINTER 	= int (C::*)() volatile;
	using MEMBER_OBJECT_POINTER 			= int C::*;
	using CONST_MEMBER_OBJECT_POINTER 		= int C::* const;
	using VOLATILE_MEMBER_OBJECT_POINTER 	= int C::* volatile;
	using LREF 								= int&;
	using CONST_LREF						= const int&;
	using VOLATILE_LREF						= volatile int&;
	using RREF 								= int&&;
	using CONST_RREF						= const int&&;
	using VOLATILE_RREF						= volatile int&&;
	using POINTER_TO_T						= int*;
	using CONST_POINTER_TO_T				= int* const;
	using CONST_POINTER_TO_CONST_T			= const int* const;
	using CONST_VOLATILE_POINTER_TO_T		= int* const volatile;
	using POINTER_TO_CONST_T				= const int*;
	using VOLATILE_POINTER_TO_T				= int* volatile;
	using VOLATILE_POINTER_TO_CONST_T		= const int* volatile;
	using VOLATILE_POINTER_TO_VOLATILE_T	= volatile int* volatile;
	using POINTER_TO_VOLATILE_T				= volatile int*;
	using VOID								= void;

	using IntConstant						= prism::IntegralConstant<int,42>;
};

/**
 * Test: AddLValueReference<>
 */
//TEST_F(type_traitsTest, AddLValueReference) {
//	using Type = prism::AddLValueReference<int>::type;
//	ASSERT_EQ(typeid(Type), typeid(int&));
//}

/**
 * Test: And<>
 */
TEST_F(type_traitsTest, And) {

	// both true
	using BothConditionsTrue1 =
			prism::And<
				prism::IsConst<CONST_INTEGRAL>,	 	// true
				prism::IsIntegral<CONST_INTEGRAL>	// true
			>::type;

	// first true, second false
	using BothConditionsTrue2 =
			prism::And<
				prism::IsConst<CONST_INTEGRAL>, 		// true
				prism::IsFloatingPoint<CONST_INTEGRAL>// false
			>::type;

	// first false, second true
	using BothConditionsTrue3 =
			prism::And<
				prism::IsFloatingPoint<CONST_INTEGRAL>,// false
				prism::IsConst<CONST_INTEGRAL> 		// true
			>::type;

	// both false
	using BothConditionsFalse =
			prism::And<
				prism::IsFloatingPoint<CONST_INTEGRAL>,	// false
				prism::IsVoid<CONST_INTEGRAL>		// also false
			>::type;

	// multiple parameters (all true)
	using AllConditionsTrue =
			prism::And<
				prism::IsIntegral<INTEGRAL>,
				prism::IsFloatingPoint<FLOAT>,
				prism::IsConst<CONST_INTEGRAL>,
				prism::IsVolatile<VOLATILE_INTEGRAL>,
				prism::IsReference<LREF>
			>::type;

	// multiple parameters (all false)
	using AllConditionsFalse =
			prism::And<
				prism::IsIntegral<FLOAT>,
				prism::IsFloatingPoint<INTEGRAL>,
				prism::IsConst<INTEGRAL>,
				prism::IsVolatile<INTEGRAL>,
				prism::IsReference<POINTER_TO_T>
			>::type;

	ASSERT_TRUE(BothConditionsTrue1::value);
	ASSERT_FALSE(BothConditionsTrue2::value);
	ASSERT_FALSE(BothConditionsTrue3::value);
	ASSERT_FALSE(BothConditionsFalse::value);
	ASSERT_TRUE(AllConditionsTrue::value);
	ASSERT_FALSE(AllConditionsFalse::value);
}

/**
 * Test: AreSame<>
 */
TEST_F(type_traitsTest, AreSame) {
	using BothSame = prism::AreSame<INTEGRAL,INTEGRAL>::type;
	using Different1 = prism::AreSame<LREF,INTEGRAL>::type;
	using Different2 = prism::AreSame<POINTER_TO_T,INTEGRAL>::type;
	using Different3 = prism::AreSame<LREF,INTEGRAL>::type;
	using Different4 = prism::AreSame<RREF,INTEGRAL>::type;

	ASSERT_TRUE(BothSame::value);
	ASSERT_FALSE(Different1::value);
	ASSERT_FALSE(Different2::value);
	ASSERT_FALSE(Different3::value);
	ASSERT_FALSE(Different4::value);
}

/*
 * Test: conditional_type<>
 * -- using two fundamental types
 */
TEST_F(type_traitsTest, conditional_type_fundamental) {
	typedef int	T1;
	typedef char T2;
	typename prism::ConditionalType_t<true, T1, T2> IntType;
	typename prism::ConditionalType_t<false, T1, T2> CharType;

	ASSERT_TRUE(typeid(IntType) 	== typeid(int));
	ASSERT_TRUE(typeid(CharType) 	== typeid(char));
	ASSERT_FALSE(typeid(CharType) 	== typeid(int));
	ASSERT_FALSE(typeid(IntType) 	== typeid(char));
}

/*
 * Test: conditional_type<>
 * -- using two non member pointer types
 */
TEST_F(type_traitsTest, conditional_type_nonmember_pointers) {
	typedef int* T1;
	typedef char* T2;
	typename prism::ConditionalType_t<true,T1,T2> IntPtrType;
	typename prism::ConditionalType_t<false,T1,T2> CharPtrType;

	ASSERT_TRUE(typeid(IntPtrType) == typeid(int*));
	ASSERT_TRUE(typeid(CharPtrType) == typeid(char*));
	ASSERT_FALSE(typeid(CharPtrType) == typeid(int*));
	ASSERT_FALSE(typeid(IntPtrType) == typeid(char*));
}

/*
 * Test: conditional_type<>
 * -- using two union types
 */
TEST_F(type_traitsTest, conditional_type_unions) {
	union U1 {};
	union U2 {};
	typename prism::ConditionalType_t<true,U1,U2> UType1;
	typename prism::ConditionalType_t<false,U1,U2> UType2;

	ASSERT_TRUE(typeid(UType1) == typeid(U1));
	ASSERT_TRUE(typeid(UType2) == typeid(U2));
	ASSERT_FALSE(typeid(UType2) == typeid(U1));
	ASSERT_FALSE(typeid(UType1) == typeid(U2));
}

/*
 * Test: conditional_type<>
 * -- using two enum types
 */
TEST_F(type_traitsTest, conditional_type_enums) {
	enum E1 {};
	enum E2 {};
	typename prism::ConditionalType_t<true,E1,E2> EType1;
	typename prism::ConditionalType_t<false,E1,E2> EType2;

	ASSERT_TRUE(typeid(EType1) == typeid(E1));
	ASSERT_TRUE(typeid(EType2) == typeid(E2));
	ASSERT_FALSE(typeid(EType2) == typeid(E1));
	ASSERT_FALSE(typeid(EType1) == typeid(E2));
}

/*
 * Test: conditional_type<>
 * -- using two member pointer types
 * -- TMemPtr and UMemPtr are pointer types to member functions (T::x() and
 * -- U::x() respectively).
 */
TEST_F(type_traitsTest, conditional_type_member_pointers) {
	class T { public: int x() {return 1;}; };
	class U { public: int x() {return 2;}; };
	typedef int (T::*TMemPtr)(void);
	typedef int (U::*UMemPtr)(void);
	T t;
	U u;

	typedef typename prism::ConditionalType_t<true,TMemPtr,UMemPtr> P1;
	typedef typename prism::ConditionalType_t<false,TMemPtr,UMemPtr> P2;

	P1 p1 = &T::x; // p1 == pointer to member function T::x()
	P2 p2 = &U::x; // p2 == pointer to member function U::x()

	ASSERT_EQ(1, (t.*p1)());
	ASSERT_EQ(2, (u.*p2)());
	ASSERT_TRUE(typeid(TMemPtr) == typeid(P1));
	ASSERT_TRUE(typeid(UMemPtr) == typeid(P2));
	ASSERT_FALSE(typeid(UMemPtr) == typeid(P1));
	ASSERT_FALSE(typeid(TMemPtr) == typeid(P2));
}

/*
 * Test: conditional_type<>
 * -- using two array types
 */
TEST_F(type_traitsTest, conditional_type_arrays) {
	typedef prism::ConditionalType_t<true, char[1],int[1]> CharArrayType;
	typedef prism::ConditionalType_t<false, char[1],int[1]> IntArrayType;

	// CharTypeArray holds 1 char so should be the size of 1 char
	// IntTypeArray holds 1 int so should be the size of 1 int
	ASSERT_EQ(sizeof(CharArrayType), sizeof(char));
	ASSERT_EQ(sizeof(IntArrayType), sizeof(int));
}

/**
 * Test: IntegralConstant<>
 */
TEST_F(type_traitsTest, IntegralConstant) {
	ASSERT_TRUE(prism::TrueType::value);
	ASSERT_FALSE(prism::FalseType::value);
	ASSERT_TRUE(IntConstant::value == 42);
}

/**
 * Test: isArithmetic<>
 */
TEST_F(type_traitsTest, IsArithmetic) {
	// true assertations
	ASSERT_TRUE(prism::IsArithmetic<float>::value);
	ASSERT_TRUE(prism::IsArithmetic<double>::value);
	ASSERT_TRUE(prism::IsArithmetic<long double>::value);
	ASSERT_TRUE(prism::IsArithmetic<bool>::value);
	ASSERT_TRUE(prism::IsArithmetic<char>::value);
	ASSERT_TRUE(prism::IsArithmetic<unsigned char>::value);
	ASSERT_TRUE(prism::IsArithmetic<short>::value);
	ASSERT_TRUE(prism::IsArithmetic<unsigned short>::value);
	ASSERT_TRUE(prism::IsArithmetic<int>::value);
	ASSERT_TRUE(prism::IsArithmetic<unsigned int>::value);
	ASSERT_TRUE(prism::IsArithmetic<long>::value);
	ASSERT_TRUE(prism::IsArithmetic<unsigned long>::value);
	ASSERT_TRUE(prism::IsArithmetic<long long>::value);
	ASSERT_TRUE(prism::IsArithmetic<unsigned long long>::value);

	// false assertations
	ASSERT_FALSE(prism::IsArithmetic<ARRAY>::value);
	ASSERT_FALSE(prism::IsArithmetic<CLASS>::value);
	ASSERT_FALSE(prism::IsArithmetic<ENUM>::value);
	ASSERT_FALSE(prism::IsArithmetic<UNION>::value);
	ASSERT_FALSE(prism::IsArithmetic<FUNCTION>::value);
	ASSERT_FALSE(prism::IsArithmetic<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_FALSE(prism::IsArithmetic<MEMBER_OBJECT_POINTER>::value);
	ASSERT_FALSE(prism::IsArithmetic<LREF>::value);
	ASSERT_FALSE(prism::IsArithmetic<RREF>::value);
	ASSERT_FALSE(prism::IsArithmetic<POINTER_TO_T>::value);
	ASSERT_FALSE(prism::IsArithmetic<VOID>::value);
}

/**
 * Test: IsArray<>
 */
TEST_F(type_traitsTest, IsArray) {
	ASSERT_TRUE(prism::IsArray<ARRAY>::value);
	ASSERT_TRUE(prism::IsArray<ARRAY_OF_POINTERS>::value);

	ASSERT_FALSE(prism::IsArray<CLASS>::value);
	ASSERT_FALSE(prism::IsArray<ENUM>::value);
	ASSERT_FALSE(prism::IsArray<UNION>::value);
	ASSERT_FALSE(prism::IsArray<FLOATING_POINT>::value);
	ASSERT_FALSE(prism::IsArray<INTEGRAL>::value);
	ASSERT_FALSE(prism::IsArray<FUNCTION>::value);
	ASSERT_FALSE(prism::IsArray<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_FALSE(prism::IsArray<MEMBER_OBJECT_POINTER>::value);
	ASSERT_FALSE(prism::IsArray<LREF>::value);
	ASSERT_FALSE(prism::IsArray<RREF>::value);
	ASSERT_FALSE(prism::IsArray<POINTER_TO_T>::value);
	ASSERT_FALSE(prism::IsArray<VOID>::value);
}

/**
 * Test: IsClass<>
 */
TEST_F(type_traitsTest, IsClass) {
	ASSERT_TRUE(prism::IsClass<CLASS>::value);
	ASSERT_TRUE(prism::IsClass<STRUCT>::value);
	ASSERT_TRUE(prism::IsClass<UNION>::value);

	ASSERT_FALSE(prism::IsClass<ARRAY>::value);
	ASSERT_FALSE(prism::IsClass<FLOATING_POINT>::value);
	ASSERT_FALSE(prism::IsClass<INTEGRAL>::value);
	ASSERT_FALSE(prism::IsClass<FUNCTION>::value);
	ASSERT_FALSE(prism::IsClass<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_FALSE(prism::IsClass<MEMBER_OBJECT_POINTER>::value);
	ASSERT_FALSE(prism::IsClass<LREF>::value);
	ASSERT_FALSE(prism::IsClass<RREF>::value);
	ASSERT_FALSE(prism::IsClass<POINTER_TO_T>::value);
	ASSERT_FALSE(prism::IsClass<VOID>::value);
}

/**
 * Test: IsCompound<>
 */
TEST_F(type_traitsTest, IsCompound) {
	ASSERT_TRUE(prism::IsCompound<ARRAY>::value);
	ASSERT_TRUE(prism::IsCompound<CLASS>::value);
	ASSERT_TRUE(prism::IsCompound<UNION>::value);
	ASSERT_TRUE(prism::IsCompound<FUNCTION>::value);
	ASSERT_TRUE(prism::IsCompound<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_TRUE(prism::IsCompound<MEMBER_OBJECT_POINTER>::value);
	ASSERT_TRUE(prism::IsCompound<LREF>::value);
	ASSERT_TRUE(prism::IsCompound<RREF>::value);
	ASSERT_TRUE(prism::IsCompound<POINTER_TO_T>::value);

	//================================================================
	// todo this assertion should indeed be TRUE but currently fails as
	// IsEnum<T> is not properly implemented and always returns false
	//================================================================
	ASSERT_TRUE(prism::IsCompound<ENUM>::value);
	//================================================================

	ASSERT_FALSE(prism::IsCompound<FLOATING_POINT>::value);
	ASSERT_FALSE(prism::IsCompound<INTEGRAL>::value);
	ASSERT_FALSE(prism::IsCompound<VOID>::value);
}

/**
 * Test: IsConst<>
 */
TEST_F(type_traitsTest, IsConst) {
	ASSERT_TRUE(	prism::IsConst_v<	CONST_INTEGRAL>);
	ASSERT_TRUE(	prism::IsConst_v<	CONST_VOLATILE_INTEGRAL>);

	ASSERT_TRUE(	prism::IsConst_v<	CONST_POINTER_TO_T>);
	ASSERT_TRUE(	prism::IsConst_v<	CONST_POINTER_TO_CONST_T>);
	ASSERT_TRUE(	prism::IsConst_v<	CONST_FLOAT>);
	ASSERT_TRUE(	prism::IsConst_v<	CONST_MEMBER_OBJECT_POINTER>);
	ASSERT_TRUE(	prism::IsConst_v<	CONST_ENUM>);
	ASSERT_TRUE(	prism::IsConst_v<	CONST_UNION>);

	ASSERT_FALSE(	prism::IsConst_v<	INTEGRAL>);
	ASSERT_FALSE(	prism::IsConst_v<	FLOAT>);
	ASSERT_FALSE(	prism::IsConst_v<	MEMBER_OBJECT_POINTER>);
	ASSERT_FALSE(	prism::IsConst_v<	MEMBER_FUNCTION_POINTER>);
	ASSERT_FALSE(	prism::IsConst_v<	POINTER_TO_T>);
	ASSERT_FALSE(	prism::IsConst_v<	POINTER_TO_CONST_T>);
	ASSERT_FALSE(	prism::IsConst_v<	RREF>);
	ASSERT_FALSE(	prism::IsConst_v<	LREF>);
	ASSERT_FALSE(	prism::IsConst_v<	ENUM>);
	ASSERT_FALSE(	prism::IsConst_v<	ARRAY>);
	ASSERT_FALSE(	prism::IsConst_v<	UNION>);
	ASSERT_FALSE(	prism::IsConst_v<	FUNCTION>);
}

/**
 * Test: IsEnum<>
 */
TEST_F(type_traitsTest, IsEnum) {
	ASSERT_FALSE(prism::IsEnum<ARRAY>::value);
	ASSERT_FALSE(prism::IsEnum<CLASS>::value);
	ASSERT_FALSE(prism::IsEnum<UNION>::value);
	ASSERT_FALSE(prism::IsEnum<FLOATING_POINT>::value);
	ASSERT_FALSE(prism::IsEnum<INTEGRAL>::value);
	ASSERT_FALSE(prism::IsEnum<FUNCTION>::value);
	ASSERT_FALSE(prism::IsEnum<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_FALSE(prism::IsEnum<MEMBER_OBJECT_POINTER>::value);
	ASSERT_FALSE(prism::IsEnum<LREF>::value);
	ASSERT_FALSE(prism::IsEnum<RREF>::value);
	ASSERT_FALSE(prism::IsEnum<POINTER_TO_T>::value);
	ASSERT_FALSE(prism::IsEnum<VOID>::value);

	//================================================================
	// todo this assertion should indeed be TRUE but currently fails as
	// IsEnum<T> is not properly implemented and always returns false
	//================================================================
	ASSERT_TRUE(prism::IsEnum<ENUM>::value);
	//================================================================
}

/**
 * Test: IsFloatingPoint<>
 */
TEST_F(type_traitsTest, isFloatingPoint) {
	// true assertations
	ASSERT_TRUE(prism::IsFloatingPoint<FLOAT>::value);
	ASSERT_TRUE(prism::IsFloatingPoint<DOUBLE>::value);
	ASSERT_TRUE(prism::IsFloatingPoint<LONG_DOUBLE>::value);

	// false assertations
	ASSERT_FALSE(prism::IsFloatingPoint<ARRAY>::value);
	ASSERT_FALSE(prism::IsFloatingPoint<CHAR>::value);
	ASSERT_FALSE(prism::IsFloatingPoint<CLASS>::value);
	ASSERT_FALSE(prism::IsFloatingPoint<ENUM>::value);
	ASSERT_FALSE(prism::IsFloatingPoint<UNION>::value);
	ASSERT_FALSE(prism::IsFloatingPoint<INTEGRAL>::value);
	ASSERT_FALSE(prism::IsFloatingPoint<FUNCTION>::value);
	ASSERT_FALSE(prism::IsFloatingPoint<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_FALSE(prism::IsFloatingPoint<MEMBER_OBJECT_POINTER>::value);
	ASSERT_FALSE(prism::IsFloatingPoint<LREF>::value);
	ASSERT_FALSE(prism::IsFloatingPoint<RREF>::value);
	ASSERT_FALSE(prism::IsFloatingPoint<POINTER_TO_T>::value);
	ASSERT_FALSE(prism::IsFloatingPoint<VOID>::value);
}

/**
 * Test: IsFunction<>
 */
TEST_F(type_traitsTest, IsFunction) {
	ASSERT_TRUE(prism::IsFunction<FUNCTION>::value);

	ASSERT_FALSE(prism::IsFunction<ARRAY>::value);
	ASSERT_FALSE(prism::IsFunction<CLASS>::value);
	ASSERT_FALSE(prism::IsFunction<ENUM>::value);
	ASSERT_FALSE(prism::IsFunction<UNION>::value);
	ASSERT_FALSE(prism::IsFunction<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_FALSE(prism::IsFunction<MEMBER_OBJECT_POINTER>::value);
	ASSERT_FALSE(prism::IsFunction<LREF>::value);
	ASSERT_FALSE(prism::IsFunction<RREF>::value);
	ASSERT_FALSE(prism::IsFunction<POINTER_TO_T>::value);
	ASSERT_FALSE(prism::IsFunction<VOID>::value);
}

/**
 * Test: IsFundamental<>
 */
TEST_F(type_traitsTest, IsFundamental) {
	ASSERT_TRUE(prism::IsFundamental<float>::value);
	ASSERT_TRUE(prism::IsFundamental<double>::value);
	ASSERT_TRUE(prism::IsFundamental<long double>::value);
	ASSERT_TRUE(prism::IsFundamental<bool>::value);
	ASSERT_TRUE(prism::IsFundamental<char>::value);
	ASSERT_TRUE(prism::IsFundamental<unsigned char>::value);
	ASSERT_TRUE(prism::IsFundamental<short>::value);
	ASSERT_TRUE(prism::IsFundamental<unsigned short>::value);
	ASSERT_TRUE(prism::IsFundamental<int>::value);
	ASSERT_TRUE(prism::IsFundamental<unsigned int>::value);
	ASSERT_TRUE(prism::IsFundamental<long>::value);
	ASSERT_TRUE(prism::IsFundamental<unsigned long>::value);
	ASSERT_TRUE(prism::IsFundamental<long long>::value);
	ASSERT_TRUE(prism::IsFundamental<unsigned long long>::value);
	ASSERT_TRUE(prism::IsFundamental<VOID>::value);
	ASSERT_TRUE(prism::IsFundamental<std::nullptr_t>::value);

	ASSERT_FALSE(prism::IsFundamental<ARRAY>::value);
	ASSERT_FALSE(prism::IsFundamental<CLASS>::value);
	ASSERT_FALSE(prism::IsFundamental<ENUM>::value);
	ASSERT_FALSE(prism::IsFundamental<UNION>::value);
	ASSERT_FALSE(prism::IsFundamental<FUNCTION>::value);
	ASSERT_FALSE(prism::IsFundamental<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_FALSE(prism::IsFundamental<MEMBER_OBJECT_POINTER>::value);
	ASSERT_FALSE(prism::IsFundamental<LREF>::value);
	ASSERT_FALSE(prism::IsFundamental<RREF>::value);
	ASSERT_FALSE(prism::IsFundamental<POINTER_TO_T>::value);
}

/**
 * Test: IsIntegral<>
 */
TEST_F(type_traitsTest, isIntegral) {
	// true assertations
	ASSERT_TRUE(prism::IsIntegral<bool>::value);
	ASSERT_TRUE(prism::IsIntegral<char>::value);
	ASSERT_TRUE(prism::IsIntegral<signed char>::value);
	ASSERT_TRUE(prism::IsIntegral<unsigned char>::value);
	ASSERT_TRUE(prism::IsIntegral<short>::value);
	ASSERT_TRUE(prism::IsIntegral<unsigned short>::value);
	ASSERT_TRUE(prism::IsIntegral<int>::value);
	ASSERT_TRUE(prism::IsIntegral<unsigned int>::value);
	ASSERT_TRUE(prism::IsIntegral<long>::value);
	ASSERT_TRUE(prism::IsIntegral<unsigned long>::value);
	ASSERT_TRUE(prism::IsIntegral<long long>::value);
	ASSERT_TRUE(prism::IsIntegral<unsigned long long>::value);

	// false assertations
	ASSERT_FALSE(prism::IsIntegral<ARRAY>::value);
	ASSERT_FALSE(prism::IsIntegral<CLASS>::value);
	ASSERT_FALSE(prism::IsIntegral<DOUBLE>::value);
	ASSERT_FALSE(prism::IsIntegral<ENUM>::value);
	ASSERT_FALSE(prism::IsIntegral<UNION>::value);
	ASSERT_FALSE(prism::IsIntegral<FLOAT>::value);
	ASSERT_FALSE(prism::IsIntegral<FUNCTION>::value);
	ASSERT_FALSE(prism::IsIntegral<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_FALSE(prism::IsIntegral<MEMBER_OBJECT_POINTER>::value);
	ASSERT_FALSE(prism::IsIntegral<LREF>::value);
	ASSERT_FALSE(prism::IsIntegral<RREF>::value);
	ASSERT_FALSE(prism::IsIntegral<POINTER_TO_T>::value);
	ASSERT_FALSE(prism::IsIntegral<VOID>::value);
}

/**
 * Test: IsLValueReference<>
 */
TEST_F(type_traitsTest, IsLValueReference) {
	ASSERT_TRUE(prism::IsLValueReference<LREF>::value);
	ASSERT_TRUE(prism::IsLValueReference<CONST_LREF>::value);
	ASSERT_TRUE(prism::IsLValueReference<VOLATILE_LREF>::value);

	ASSERT_FALSE(prism::IsLValueReference<ARRAY>::value);
	ASSERT_FALSE(prism::IsLValueReference<CLASS>::value);
	ASSERT_FALSE(prism::IsLValueReference<ENUM>::value);
	ASSERT_FALSE(prism::IsLValueReference<UNION>::value);
	ASSERT_FALSE(prism::IsLValueReference<FLOATING_POINT>::value);
	ASSERT_FALSE(prism::IsLValueReference<INTEGRAL>::value);
	ASSERT_FALSE(prism::IsLValueReference<FUNCTION>::value);
	ASSERT_FALSE(prism::IsLValueReference<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_FALSE(prism::IsLValueReference<MEMBER_OBJECT_POINTER>::value);
	ASSERT_FALSE(prism::IsLValueReference<RREF>::value);
	ASSERT_FALSE(prism::IsLValueReference<POINTER_TO_T>::value);
	ASSERT_FALSE(prism::IsLValueReference<VOID>::value);
}

/**
 * Test: IsMemberFunctionPointer<>
 */
TEST_F(type_traitsTest, IsMemberFunctionPointer) {
	ASSERT_TRUE(prism::IsMemberFunctionPointer<MEMBER_FUNCTION_POINTER>::value);

	ASSERT_FALSE(prism::IsMemberFunctionPointer<ARRAY>::value);
	ASSERT_FALSE(prism::IsMemberFunctionPointer<CLASS>::value);
	ASSERT_FALSE(prism::IsMemberFunctionPointer<ENUM>::value);
	ASSERT_FALSE(prism::IsMemberFunctionPointer<UNION>::value);
	ASSERT_FALSE(prism::IsMemberFunctionPointer<FLOATING_POINT>::value);
	ASSERT_FALSE(prism::IsMemberFunctionPointer<INTEGRAL>::value);
	ASSERT_FALSE(prism::IsMemberFunctionPointer<FUNCTION>::value);
	ASSERT_FALSE(prism::IsMemberFunctionPointer<MEMBER_OBJECT_POINTER>::value);
	ASSERT_FALSE(prism::IsMemberFunctionPointer<LREF>::value);
	ASSERT_FALSE(prism::IsMemberFunctionPointer<RREF>::value);
	ASSERT_FALSE(prism::IsMemberFunctionPointer<POINTER_TO_T>::value);
	ASSERT_FALSE(prism::IsMemberFunctionPointer<VOID>::value);
}

/**
 * Test: IsMemberObjectPointer<>
 */
TEST_F(type_traitsTest, IsMemberObjectPointer) {
	ASSERT_TRUE(prism::IsMemberObjectPointer<MEMBER_OBJECT_POINTER>::value);

	ASSERT_FALSE(prism::IsMemberObjectPointer<ARRAY>::value);
	ASSERT_FALSE(prism::IsMemberObjectPointer<CLASS>::value);
	ASSERT_FALSE(prism::IsMemberObjectPointer<ENUM>::value);
	ASSERT_FALSE(prism::IsMemberObjectPointer<UNION>::value);
	ASSERT_FALSE(prism::IsMemberObjectPointer<FLOATING_POINT>::value);
	ASSERT_FALSE(prism::IsMemberObjectPointer<INTEGRAL>::value);
	ASSERT_FALSE(prism::IsMemberObjectPointer<FUNCTION>::value);
	ASSERT_FALSE(prism::IsMemberObjectPointer<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_FALSE(prism::IsMemberObjectPointer<LREF>::value);
	ASSERT_FALSE(prism::IsMemberObjectPointer<RREF>::value);
	ASSERT_FALSE(prism::IsMemberObjectPointer<POINTER_TO_T>::value);
	ASSERT_FALSE(prism::IsMemberObjectPointer<VOID>::value);
}

/**
 * Test: IsMemberPointer<>
 */
TEST_F(type_traitsTest, IsMemberPointer) {
	ASSERT_TRUE(prism::IsMemberPointer<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_TRUE(prism::IsMemberPointer<MEMBER_OBJECT_POINTER>::value);

	ASSERT_FALSE(prism::IsMemberPointer<ARRAY>::value);
	ASSERT_FALSE(prism::IsMemberPointer<CLASS>::value);
	ASSERT_FALSE(prism::IsMemberPointer<ENUM>::value);
	ASSERT_FALSE(prism::IsMemberPointer<UNION>::value);
	ASSERT_FALSE(prism::IsMemberPointer<FLOATING_POINT>::value);
	ASSERT_FALSE(prism::IsMemberPointer<INTEGRAL>::value);
	ASSERT_FALSE(prism::IsMemberPointer<FUNCTION>::value);
	ASSERT_FALSE(prism::IsMemberPointer<LREF>::value);
	ASSERT_FALSE(prism::IsMemberPointer<RREF>::value);
	ASSERT_FALSE(prism::IsMemberPointer<POINTER_TO_T>::value);
	ASSERT_FALSE(prism::IsMemberPointer<VOID>::value);
}

/**
 * Test: IsPointer<>
 */
TEST_F(type_traitsTest, IsPointer) {
	ASSERT_TRUE(prism::IsPointer<POINTER_TO_T>::value);
	ASSERT_TRUE(prism::IsPointer<POINTER_TO_CONST_T>::value);
	ASSERT_TRUE(prism::IsPointer<POINTER_TO_VOLATILE_T>::value);
	ASSERT_TRUE(prism::IsPointer<CONST_POINTER_TO_T>::value);
	ASSERT_TRUE(prism::IsPointer<CONST_POINTER_TO_CONST_T>::value);
	ASSERT_TRUE(prism::IsPointer<VOLATILE_POINTER_TO_T>::value);
	ASSERT_TRUE(prism::IsPointer<VOLATILE_POINTER_TO_VOLATILE_T>::value);
	ASSERT_TRUE(prism::IsPointer<VOLATILE_POINTER_TO_CONST_T>::value);

	ASSERT_FALSE(prism::IsPointer<ARRAY>::value);
	ASSERT_FALSE(prism::IsPointer<CHAR>::value);
	ASSERT_FALSE(prism::IsPointer<CLASS>::value);
	ASSERT_FALSE(prism::IsPointer<FLOATING_POINT>::value);
	ASSERT_FALSE(prism::IsPointer<ENUM>::value);
	ASSERT_FALSE(prism::IsPointer<UNION>::value);
	ASSERT_FALSE(prism::IsPointer<INTEGRAL>::value);
	ASSERT_FALSE(prism::IsPointer<FUNCTION>::value);
	ASSERT_FALSE(prism::IsPointer<MEMBER_OBJECT_POINTER>::value);
	ASSERT_FALSE(prism::IsPointer<LREF>::value);
	ASSERT_FALSE(prism::IsPointer<RREF>::value);
	ASSERT_FALSE(prism::IsPointer<VOID>::value);
}

/**
 * Test: IsObject<>
 */
TEST_F(type_traitsTest, IsObject) {
	ASSERT_TRUE(prism::IsObject<ARRAY>::value);
	ASSERT_TRUE(prism::IsObject<CLASS>::value);
	ASSERT_TRUE(prism::IsObject<UNION>::value);
	ASSERT_TRUE(prism::IsObject<FLOATING_POINT>::value);
	ASSERT_TRUE(prism::IsObject<INTEGRAL>::value);
	ASSERT_TRUE(prism::IsObject<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_TRUE(prism::IsObject<MEMBER_OBJECT_POINTER>::value);
	ASSERT_TRUE(prism::IsObject<POINTER_TO_T>::value);
	ASSERT_TRUE(prism::IsObject<std::nullptr_t>::value);

	ASSERT_FALSE(prism::IsObject<FUNCTION>::value);
	ASSERT_FALSE(prism::IsObject<LREF>::value);
	ASSERT_FALSE(prism::IsObject<RREF>::value);
	ASSERT_FALSE(prism::IsObject<VOID>::value);

	//================================================================
	// todo this assertion should indeed be TRUE but currently fails as
	// IsEnum<T> is not properly implemented and always returns false
	//================================================================
	ASSERT_TRUE(prism::IsObject<ENUM>::value);
	//================================================================
}

/**
 * Test: IsReferenceable<>
 * -- an object or reference is referenceable
 */
TEST_F(type_traitsTest, IsReferenceable) {
	ASSERT_TRUE(prism::IsReferenceable<ARRAY>::value);
	ASSERT_TRUE(prism::IsReferenceable<CLASS>::value);
	ASSERT_TRUE(prism::IsReferenceable<FLOATING_POINT>::value);
	ASSERT_TRUE(prism::IsReferenceable<INTEGRAL>::value);
	ASSERT_TRUE(prism::IsReferenceable<FUNCTION>::value);
	ASSERT_TRUE(prism::IsReferenceable<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_TRUE(prism::IsReferenceable<MEMBER_OBJECT_POINTER>::value);
	ASSERT_TRUE(prism::IsReferenceable<LREF>::value);
	ASSERT_TRUE(prism::IsReferenceable<RREF>::value);

	ASSERT_FALSE(prism::IsReferenceable<VOID>::value);

	//================================================================
	// todo this assertion should indeed be TRUE but currently fails as
	// IsEnum<T> is not properly implemented and always returns false.
	//================================================================
	ASSERT_TRUE(prism::IsReferenceable<ENUM>::value);
	//================================================================
}

/**
 * Test: IsReference<>
 */
TEST_F(type_traitsTest, IsReference) {
	ASSERT_TRUE(prism::IsReference<LREF>::value);
	ASSERT_TRUE(prism::IsReference<RREF>::value);

	ASSERT_FALSE(prism::IsReference<ARRAY>::value);
	ASSERT_FALSE(prism::IsReference<CLASS>::value);
	ASSERT_FALSE(prism::IsReference<ENUM>::value);
	ASSERT_FALSE(prism::IsReference<UNION>::value);
	ASSERT_FALSE(prism::IsReference<FLOATING_POINT>::value);
	ASSERT_FALSE(prism::IsReference<INTEGRAL>::value);
	ASSERT_FALSE(prism::IsReference<FUNCTION>::value);
	ASSERT_FALSE(prism::IsReference<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_FALSE(prism::IsReference<MEMBER_OBJECT_POINTER>::value);
	ASSERT_FALSE(prism::IsReference<POINTER_TO_T>::value);
	ASSERT_FALSE(prism::IsReference<VOID>::value);
}

/**
 * Test: IsRValueReference<>
 */
TEST_F(type_traitsTest, IsRValueReference) {
	ASSERT_TRUE(prism::IsRValueReference<RREF>::value);
	ASSERT_TRUE(prism::IsRValueReference<CONST_RREF>::value);
	ASSERT_TRUE(prism::IsRValueReference<VOLATILE_RREF>::value);

	ASSERT_FALSE(prism::IsRValueReference<ARRAY>::value);
	ASSERT_FALSE(prism::IsRValueReference<CLASS>::value);
	ASSERT_FALSE(prism::IsRValueReference<ENUM>::value);
	ASSERT_FALSE(prism::IsRValueReference<UNION>::value);
	ASSERT_FALSE(prism::IsRValueReference<FLOATING_POINT>::value);
	ASSERT_FALSE(prism::IsRValueReference<INTEGRAL>::value);
	ASSERT_FALSE(prism::IsRValueReference<FUNCTION>::value);
	ASSERT_FALSE(prism::IsRValueReference<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_FALSE(prism::IsRValueReference<MEMBER_OBJECT_POINTER>::value);
	ASSERT_FALSE(prism::IsRValueReference<LREF>::value);
	ASSERT_FALSE(prism::IsRValueReference<POINTER_TO_T>::value);
	ASSERT_FALSE(prism::IsRValueReference<VOID>::value);
}

/**
 * Test: IsScalar<>
 */
TEST_F(type_traitsTest, IsScalar) {
	ASSERT_TRUE(prism::IsScalar<FLOATING_POINT>::value);
	ASSERT_TRUE(prism::IsScalar<INTEGRAL>::value);
	ASSERT_TRUE(prism::IsScalar<std::nullptr_t>::value);
	ASSERT_TRUE(prism::IsScalar<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_TRUE(prism::IsScalar<MEMBER_OBJECT_POINTER>::value);
	ASSERT_TRUE(prism::IsScalar<POINTER_TO_T>::value);

	ASSERT_FALSE(prism::IsScalar<ARRAY>::value);
	ASSERT_FALSE(prism::IsScalar<CLASS>::value);
	ASSERT_FALSE(prism::IsScalar<UNION>::value);
	ASSERT_FALSE(prism::IsScalar<FUNCTION>::value);
	ASSERT_FALSE(prism::IsScalar<LREF>::value);
	ASSERT_FALSE(prism::IsScalar<RREF>::value);
	ASSERT_FALSE(prism::IsScalar<VOID>::value);

	//================================================================
	// todo this assertion should indeed be TRUE but currently fails as
	// IsEnum<T> is not properly implemented and always returns false
	//================================================================
	ASSERT_TRUE(prism::IsScalar<ENUM>::value);
	//================================================================
}

/**
 * Test: IsSigned<>
 */
TEST_F(type_traitsTest, IsSigned) {
	ASSERT_TRUE(prism::IsSigned<INTEGRAL>::value);
	ASSERT_TRUE(prism::IsSigned<SIGNED_INTEGRAL>::value);

	ASSERT_FALSE(prism::IsSigned<UNSIGNED_INTEGRAL>::value);
	ASSERT_FALSE(prism::IsSigned<ARRAY>::value);
	ASSERT_FALSE(prism::IsSigned<CLASS>::value);
	ASSERT_FALSE(prism::IsSigned<ENUM>::value);
	ASSERT_FALSE(prism::IsSigned<UNION>::value);
	ASSERT_FALSE(prism::IsSigned<FUNCTION>::value);
	ASSERT_FALSE(prism::IsSigned<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_FALSE(prism::IsSigned<MEMBER_OBJECT_POINTER>::value);
	ASSERT_FALSE(prism::IsSigned<LREF>::value);
	ASSERT_FALSE(prism::IsSigned<RREF>::value);
	ASSERT_FALSE(prism::IsSigned<POINTER_TO_T>::value);
	ASSERT_FALSE(prism::IsSigned<VOID>::value);
}

/**
 * Test: IsUnsigned<>
 */
TEST_F(type_traitsTest, IsUnsigned) {
	ASSERT_TRUE(prism::IsUnsigned<UNSIGNED_INTEGRAL>::value);

	ASSERT_FALSE(prism::IsUnsigned<INTEGRAL>::value);
	ASSERT_FALSE(prism::IsUnsigned<SIGNED_INTEGRAL>::value);
	ASSERT_FALSE(prism::IsUnsigned<ARRAY>::value);
	ASSERT_FALSE(prism::IsUnsigned<CLASS>::value);
	ASSERT_FALSE(prism::IsUnsigned<ENUM>::value);
	ASSERT_FALSE(prism::IsUnsigned<UNION>::value);
	ASSERT_FALSE(prism::IsUnsigned<FUNCTION>::value);
	ASSERT_FALSE(prism::IsUnsigned<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_FALSE(prism::IsUnsigned<MEMBER_OBJECT_POINTER>::value);
	ASSERT_FALSE(prism::IsUnsigned<LREF>::value);
	ASSERT_FALSE(prism::IsUnsigned<RREF>::value);
	ASSERT_FALSE(prism::IsUnsigned<POINTER_TO_T>::value);
	ASSERT_FALSE(prism::IsUnsigned<VOID>::value);
}

/**
 * Test: IsVoid
 */
TEST_F(type_traitsTest, IsVoid) {
	ASSERT_TRUE(prism::IsVoid<VOID>::value);

	ASSERT_FALSE(prism::IsVoid<void*>::value);
	ASSERT_FALSE(prism::IsVoid<ARRAY>::value);
	ASSERT_FALSE(prism::IsVoid<CLASS>::value);
	ASSERT_FALSE(prism::IsVoid<ENUM>::value);
	ASSERT_FALSE(prism::IsVoid<UNION>::value);
	ASSERT_FALSE(prism::IsVoid<FUNCTION>::value);
	ASSERT_FALSE(prism::IsVoid<MEMBER_FUNCTION_POINTER>::value);
	ASSERT_FALSE(prism::IsVoid<MEMBER_OBJECT_POINTER>::value);
	ASSERT_FALSE(prism::IsVoid<LREF>::value);
	ASSERT_FALSE(prism::IsVoid<RREF>::value);
	ASSERT_FALSE(prism::IsVoid<POINTER_TO_T>::value);
}

/**
 * Test: IsVolatile<>
 */
TEST_F(type_traitsTest, IsVolatile) {
	ASSERT_TRUE(	prism::IsVolatile_v<	VOLATILE_INTEGRAL>);
	ASSERT_TRUE(	prism::IsVolatile_v<	CONST_VOLATILE_INTEGRAL>);

	ASSERT_TRUE(	prism::IsVolatile_v<	VOLATILE_POINTER_TO_T>);
	ASSERT_TRUE(	prism::IsVolatile_v<	VOLATILE_POINTER_TO_CONST_T>);
	ASSERT_TRUE(	prism::IsVolatile_v<	VOLATILE_FLOAT>);
	ASSERT_TRUE(	prism::IsVolatile_v<	VOLATILE_MEMBER_OBJECT_POINTER>);
	ASSERT_TRUE(	prism::IsVolatile_v<	VOLATILE_ENUM>);
	ASSERT_TRUE(	prism::IsVolatile_v<	VOLATILE_UNION>);

	ASSERT_FALSE(	prism::IsVolatile_v<	INTEGRAL>);
	ASSERT_FALSE(	prism::IsVolatile_v<	FLOAT>);
	ASSERT_FALSE(	prism::IsVolatile_v<	MEMBER_OBJECT_POINTER>);
	ASSERT_FALSE(	prism::IsVolatile_v<	MEMBER_FUNCTION_POINTER>);
	ASSERT_FALSE(	prism::IsVolatile_v<	POINTER_TO_T>);
	ASSERT_FALSE(	prism::IsVolatile_v<	POINTER_TO_CONST_T>);
	ASSERT_FALSE(	prism::IsVolatile_v<	LREF>);
	ASSERT_FALSE(	prism::IsVolatile_v<	RREF>);
	ASSERT_FALSE(	prism::IsVolatile_v<	ENUM>);
	ASSERT_FALSE(	prism::IsVolatile_v<	ARRAY>);
	ASSERT_FALSE(	prism::IsVolatile_v<	UNION>);
	ASSERT_FALSE(	prism::IsVolatile_v<	FUNCTION>);
}



/**
 * Test: Or<>
 */
TEST_F(type_traitsTest, Or) {
	// first true, second false
	using EitherConditionTrue1 =
			prism::Or<
				prism::IsFloatingPoint<FLOAT>, 	// true
				prism::IsIntegral<FLOAT> 		// false
			>::type;

	// first false, second true
	using EitherConditionTrue2 =
			prism::Or<
				prism::IsFloatingPoint<CHAR>, 	// false
				prism::IsIntegral<CHAR> 		// true
			>::type;

	// both false
	using BothConditionsFalse =
			prism::Or<
				prism::IsFloatingPoint<void>, 	// false
				prism::IsIntegral<void> 		// false
			>::type;

	// both true
	using BothConditionsTrue =
			prism::Or<
				prism::IsFloatingPoint<FLOAT>,	// true
				prism::IsArithmetic<FLOAT>		// also true
			>::type;

	// multiple parameters, all true
	using AllConditionsTrue =
			prism::Or<
				prism::IsIntegral<INTEGRAL>,
				prism::IsFloatingPoint<FLOAT>,
				prism::IsConst<CONST_FLOAT>,
				prism::IsRValueReference<RREF>
			>::type;

	// multiple parameters, all false
	using AllConditionsFalse =
			prism::Or<
				prism::IsIntegral<FLOAT>,
				prism::IsFloatingPoint<INTEGRAL>,
				prism::IsConst<FLOAT>,
				prism::IsRValueReference<POINTER_TO_T>
			>::type;

	ASSERT_TRUE(EitherConditionTrue1::value);
	ASSERT_TRUE(EitherConditionTrue2::value);
	ASSERT_FALSE(BothConditionsFalse::value);
	ASSERT_TRUE(BothConditionsTrue::value);
	ASSERT_TRUE(AllConditionsTrue::value);
	ASSERT_FALSE(AllConditionsFalse::value);
}

/**
 * Test: RemoveConst<>
 */
TEST_F(type_traitsTest, RemoveConst) {
	using T1 = prism::RemoveConst<CONST_FLOAT>::type;
	ASSERT_TRUE(typeid(T1) == typeid(FLOAT));

	using T2 = prism::RemoveConst<CONST_POINTER_TO_T>::type;
	ASSERT_TRUE(typeid(T2) == typeid(POINTER_TO_T));

	using T3 = prism::RemoveConst<CONST_POINTER_TO_CONST_T>::type;
	ASSERT_TRUE(typeid(T3) == typeid(POINTER_TO_CONST_T));

	using T4 = prism::RemoveConst<POINTER_TO_CONST_T>::type;
	ASSERT_TRUE(typeid(T4) == typeid(POINTER_TO_CONST_T));
}

/**
 * Test: RemoveConstVolatile<>
 */
TEST_F(type_traitsTest, RemoveConstVolatile) {
	using T1 = prism::RemoveConstVolatile<CONST_VOLATILE_POINTER_TO_T>::type;
	ASSERT_TRUE(typeid(T1) == typeid(POINTER_TO_T));

	using T2 = prism::RemoveConstVolatile<CONST_POINTER_TO_T>::type;
	ASSERT_TRUE(typeid(T2) == typeid(POINTER_TO_T));

	using T3 = prism::RemoveConstVolatile<VOLATILE_POINTER_TO_T>::type;
	ASSERT_TRUE(typeid(T3) == typeid(POINTER_TO_T));

	using T4 = prism::RemoveConstVolatile<CONST_INTEGRAL>::type;
	ASSERT_TRUE(typeid(T4) == typeid(INTEGRAL));

	using T5 = prism::RemoveConstVolatile<VOLATILE_INTEGRAL>::type;
	ASSERT_TRUE(typeid(T5) == typeid(INTEGRAL));

}

/**
 * Test: RemoveVolatile<>
 */
TEST_F(type_traitsTest, RemoveVolatile) {
	using T1 = prism::RemoveVolatile<VOLATILE_FLOAT>::type;
	ASSERT_TRUE(typeid(T1) == typeid(FLOAT));

	using T2 = prism::RemoveVolatile<VOLATILE_POINTER_TO_T>::type;
	ASSERT_TRUE(typeid(T2) == typeid(POINTER_TO_T));

	using T3 = prism::RemoveVolatile<VOLATILE_POINTER_TO_CONST_T>::type;
	ASSERT_TRUE(typeid(T3) == typeid(POINTER_TO_CONST_T));

	using T4 = prism::RemoveVolatile<POINTER_TO_VOLATILE_T>::type;
	ASSERT_TRUE(typeid(T4) == typeid(POINTER_TO_VOLATILE_T));
}

} // end namespace test
} // end namespace prism













