/*
 * type_traitsTest.cpp
 * v1
 *
 *  Created on: Nov 2, 2016
 *      Author: iainhemstock
 *
 */

#include <gtest/gtest.h>
#include <prism/h/type_traits.h>

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

	int getInt() { return 22; }
};

/**
 * Test: AddLValueReference<>
 */
TEST_F(type_traitsTest, AddLValueReference) {
	EXPECT_EQ(
			typeid(prism::AddLValueReference<INTEGRAL>::type),
			typeid(INTEGRAL&)
	);
	EXPECT_EQ(
			typeid(prism::AddLValueReference<INTEGRAL&&>::type),
			typeid(INTEGRAL&)
	);
	EXPECT_EQ(
			typeid(prism::AddLValueReference<INTEGRAL&>::type),
			typeid(INTEGRAL&)
	);
	EXPECT_EQ(
			typeid(prism::AddLValueReference<VOID>::type),
			typeid(VOID)
	);
	EXPECT_EQ(
			typeid(prism::AddLValueReference<FUNCTION>::type),
			typeid(FUNCTION&)
	);
}

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

	EXPECT_TRUE(BothConditionsTrue1::value);
	EXPECT_FALSE(BothConditionsTrue2::value);
	EXPECT_FALSE(BothConditionsTrue3::value);
	EXPECT_FALSE(BothConditionsFalse::value);
	EXPECT_TRUE(AllConditionsTrue::value);
	EXPECT_FALSE(AllConditionsFalse::value);
}

/**
 * Test: AreSame<>
 */
TEST_F(type_traitsTest, IsSame) {
	using BothSame = prism::IsSame<INTEGRAL,INTEGRAL>::type;
	using Different1 = prism::IsSame<LREF,INTEGRAL>::type;
	using Different2 = prism::IsSame<POINTER_TO_T,INTEGRAL>::type;
	using Different3 = prism::IsSame<LREF,INTEGRAL>::type;
	using Different4 = prism::IsSame<RREF,INTEGRAL>::type;

	EXPECT_TRUE(BothSame::value);
	EXPECT_FALSE(Different1::value);
	EXPECT_FALSE(Different2::value);
	EXPECT_FALSE(Different3::value);
	EXPECT_FALSE(Different4::value);
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

	EXPECT_TRUE(typeid(IntType) 	== typeid(int));
	EXPECT_TRUE(typeid(CharType) 	== typeid(char));
	EXPECT_FALSE(typeid(CharType) 	== typeid(int));
	EXPECT_FALSE(typeid(IntType) 	== typeid(char));
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

	EXPECT_TRUE(typeid(IntPtrType) == typeid(int*));
	EXPECT_TRUE(typeid(CharPtrType) == typeid(char*));
	EXPECT_FALSE(typeid(CharPtrType) == typeid(int*));
	EXPECT_FALSE(typeid(IntPtrType) == typeid(char*));
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

	EXPECT_TRUE(typeid(UType1) == typeid(U1));
	EXPECT_TRUE(typeid(UType2) == typeid(U2));
	EXPECT_FALSE(typeid(UType2) == typeid(U1));
	EXPECT_FALSE(typeid(UType1) == typeid(U2));
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

	EXPECT_TRUE(typeid(EType1) == typeid(E1));
	EXPECT_TRUE(typeid(EType2) == typeid(E2));
	EXPECT_FALSE(typeid(EType2) == typeid(E1));
	EXPECT_FALSE(typeid(EType1) == typeid(E2));
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

	EXPECT_EQ(1, (t.*p1)());
	EXPECT_EQ(2, (u.*p2)());
	EXPECT_TRUE(typeid(TMemPtr) == typeid(P1));
	EXPECT_TRUE(typeid(UMemPtr) == typeid(P2));
	EXPECT_FALSE(typeid(UMemPtr) == typeid(P1));
	EXPECT_FALSE(typeid(TMemPtr) == typeid(P2));
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
	EXPECT_EQ(sizeof(CharArrayType), sizeof(char));
	EXPECT_EQ(sizeof(IntArrayType), sizeof(int));
}

/**
 * Test: forward()
 */
TEST_F(type_traitsTest, forward) {
	// need to write some unit tests for forward
	EXPECT_TRUE(false);
}

/**
 * Test: IntegralConstant<>
 */
TEST_F(type_traitsTest, IntegralConstant) {
	EXPECT_TRUE(prism::TrueType::value);
	EXPECT_FALSE(prism::FalseType::value);
	EXPECT_TRUE(IntConstant::value == 42);
}

/**
 * Test: isArithmetic<>
 */
TEST_F(type_traitsTest, IsArithmetic) {
	// true EXPECTations
	EXPECT_TRUE(prism::IsArithmetic<float>::value);
	EXPECT_TRUE(prism::IsArithmetic<double>::value);
	EXPECT_TRUE(prism::IsArithmetic<long double>::value);
	EXPECT_TRUE(prism::IsArithmetic<bool>::value);
	EXPECT_TRUE(prism::IsArithmetic<char>::value);
	EXPECT_TRUE(prism::IsArithmetic<unsigned char>::value);
	EXPECT_TRUE(prism::IsArithmetic<short>::value);
	EXPECT_TRUE(prism::IsArithmetic<unsigned short>::value);
	EXPECT_TRUE(prism::IsArithmetic<int>::value);
	EXPECT_TRUE(prism::IsArithmetic<unsigned int>::value);
	EXPECT_TRUE(prism::IsArithmetic<long>::value);
	EXPECT_TRUE(prism::IsArithmetic<unsigned long>::value);
	EXPECT_TRUE(prism::IsArithmetic<long long>::value);
	EXPECT_TRUE(prism::IsArithmetic<unsigned long long>::value);

	// false EXPECTations
	EXPECT_FALSE(prism::IsArithmetic<ARRAY>::value);
	EXPECT_FALSE(prism::IsArithmetic<CLASS>::value);
	EXPECT_FALSE(prism::IsArithmetic<ENUM>::value);
	EXPECT_FALSE(prism::IsArithmetic<UNION>::value);
	EXPECT_FALSE(prism::IsArithmetic<FUNCTION>::value);
	EXPECT_FALSE(prism::IsArithmetic<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_FALSE(prism::IsArithmetic<MEMBER_OBJECT_POINTER>::value);
	EXPECT_FALSE(prism::IsArithmetic<LREF>::value);
	EXPECT_FALSE(prism::IsArithmetic<RREF>::value);
	EXPECT_FALSE(prism::IsArithmetic<POINTER_TO_T>::value);
	EXPECT_FALSE(prism::IsArithmetic<VOID>::value);
}

/**
 * Test: IsArray<>
 */
TEST_F(type_traitsTest, IsArray) {
	EXPECT_TRUE(prism::IsArray<ARRAY>::value);
	EXPECT_TRUE(prism::IsArray<ARRAY_OF_POINTERS>::value);

	EXPECT_FALSE(prism::IsArray<CLASS>::value);
	EXPECT_FALSE(prism::IsArray<ENUM>::value);
	EXPECT_FALSE(prism::IsArray<UNION>::value);
	EXPECT_FALSE(prism::IsArray<FLOATING_POINT>::value);
	EXPECT_FALSE(prism::IsArray<INTEGRAL>::value);
	EXPECT_FALSE(prism::IsArray<FUNCTION>::value);
	EXPECT_FALSE(prism::IsArray<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_FALSE(prism::IsArray<MEMBER_OBJECT_POINTER>::value);
	EXPECT_FALSE(prism::IsArray<LREF>::value);
	EXPECT_FALSE(prism::IsArray<RREF>::value);
	EXPECT_FALSE(prism::IsArray<POINTER_TO_T>::value);
	EXPECT_FALSE(prism::IsArray<VOID>::value);
}

/**
 * Test: IsDefaultConstructible<>
 */
TEST_F(type_traitsTest, IsDefaultConstructible) {
	EXPECT_FALSE(prism::IsDefaultConstructible<void>::value);
	EXPECT_FALSE(prism::IsDefaultConstructible<LREF>::value);
	EXPECT_FALSE(prism::IsDefaultConstructible<RREF>::value);
	EXPECT_FALSE(prism::IsDefaultConstructible<FUNCTION>::value);

	EXPECT_TRUE(prism::IsDefaultConstructible<int>::value);
	EXPECT_TRUE(prism::IsDefaultConstructible<CLASS>::value);
	EXPECT_TRUE(prism::IsDefaultConstructible<UNION>::value);
	EXPECT_TRUE(prism::IsDefaultConstructible<ENUM>::value);
	EXPECT_TRUE(prism::IsDefaultConstructible<STRUCT>::value);
	EXPECT_TRUE(prism::IsDefaultConstructible<INTEGRAL>::value);
	EXPECT_TRUE(prism::IsDefaultConstructible<FLOATING_POINT>::value);
	EXPECT_TRUE(prism::IsDefaultConstructible<MEMBER_OBJECT_POINTER>::value);
	EXPECT_TRUE(prism::IsDefaultConstructible<POINTER_TO_T>::value);
	EXPECT_TRUE(prism::IsDefaultConstructible<int[]>::value);
	EXPECT_TRUE(prism::IsDefaultConstructible<int[5]>::value);
}

/**
 * Test: IsClass<>
 */
TEST_F(type_traitsTest, IsClass) {
	EXPECT_TRUE(prism::IsClass<CLASS>::value);
	EXPECT_TRUE(prism::IsClass<STRUCT>::value);
	EXPECT_TRUE(prism::IsClass<UNION>::value);

	EXPECT_FALSE(prism::IsClass<ARRAY>::value);
	EXPECT_FALSE(prism::IsClass<FLOATING_POINT>::value);
	EXPECT_FALSE(prism::IsClass<INTEGRAL>::value);
	EXPECT_FALSE(prism::IsClass<FUNCTION>::value);
	EXPECT_FALSE(prism::IsClass<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_FALSE(prism::IsClass<MEMBER_OBJECT_POINTER>::value);
	EXPECT_FALSE(prism::IsClass<LREF>::value);
	EXPECT_FALSE(prism::IsClass<RREF>::value);
	EXPECT_FALSE(prism::IsClass<POINTER_TO_T>::value);
	EXPECT_FALSE(prism::IsClass<VOID>::value);
}

/**
 * Test: IsCompound<>
 */
TEST_F(type_traitsTest, IsCompound) {
	EXPECT_TRUE(prism::IsCompound<ARRAY>::value);
	EXPECT_TRUE(prism::IsCompound<CLASS>::value);
	EXPECT_TRUE(prism::IsCompound<UNION>::value);
	EXPECT_TRUE(prism::IsCompound<FUNCTION>::value);
	EXPECT_TRUE(prism::IsCompound<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_TRUE(prism::IsCompound<MEMBER_OBJECT_POINTER>::value);
	EXPECT_TRUE(prism::IsCompound<LREF>::value);
	EXPECT_TRUE(prism::IsCompound<RREF>::value);
	EXPECT_TRUE(prism::IsCompound<POINTER_TO_T>::value);

	//================================================================
	// todo this assertion should indeed be TRUE but currently fails as
	// IsEnum<T> is not properly implemented and always returns false
	//================================================================
	EXPECT_TRUE(prism::IsCompound<ENUM>::value);
	//================================================================

	EXPECT_FALSE(prism::IsCompound<FLOATING_POINT>::value);
	EXPECT_FALSE(prism::IsCompound<INTEGRAL>::value);
	EXPECT_FALSE(prism::IsCompound<VOID>::value);
}

/**
 * Test: IsConst<>
 */
TEST_F(type_traitsTest, IsConst) {
	EXPECT_TRUE(	prism::IsConst<	CONST_INTEGRAL>::value);
	EXPECT_TRUE(	prism::IsConst<	CONST_VOLATILE_INTEGRAL>::value);

	EXPECT_TRUE(	prism::IsConst<	CONST_POINTER_TO_T>::value);
	EXPECT_TRUE(	prism::IsConst<	CONST_POINTER_TO_CONST_T>::value);
	EXPECT_TRUE(	prism::IsConst<	CONST_FLOAT>::value);
	EXPECT_TRUE(	prism::IsConst<	CONST_MEMBER_OBJECT_POINTER>::value);
	EXPECT_TRUE(	prism::IsConst<	CONST_ENUM>::value);
	EXPECT_TRUE(	prism::IsConst<	CONST_UNION>::value);

	EXPECT_FALSE(	prism::IsConst<	INTEGRAL>::value);
	EXPECT_FALSE(	prism::IsConst<	FLOAT>::value);
	EXPECT_FALSE(	prism::IsConst<	MEMBER_OBJECT_POINTER>::value);
	EXPECT_FALSE(	prism::IsConst<	MEMBER_FUNCTION_POINTER>::value);
	EXPECT_FALSE(	prism::IsConst<	POINTER_TO_T>::value);
	EXPECT_FALSE(	prism::IsConst<	POINTER_TO_CONST_T>::value);
	EXPECT_FALSE(	prism::IsConst<	RREF>::value);
	EXPECT_FALSE(	prism::IsConst<	LREF>::value);
	EXPECT_FALSE(	prism::IsConst<	ENUM>::value);
	EXPECT_FALSE(	prism::IsConst<	ARRAY>::value);
	EXPECT_FALSE(	prism::IsConst<	UNION>::value);
	EXPECT_FALSE(	prism::IsConst<	FUNCTION>::value);
}

/**
 * Test: IsEnum<>
 */
TEST_F(type_traitsTest, IsEnum) {
	EXPECT_FALSE(prism::IsEnum<ARRAY>::value);
	EXPECT_FALSE(prism::IsEnum<CLASS>::value);
	EXPECT_FALSE(prism::IsEnum<UNION>::value);
	EXPECT_FALSE(prism::IsEnum<FLOATING_POINT>::value);
	EXPECT_FALSE(prism::IsEnum<INTEGRAL>::value);
	EXPECT_FALSE(prism::IsEnum<FUNCTION>::value);
	EXPECT_FALSE(prism::IsEnum<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_FALSE(prism::IsEnum<MEMBER_OBJECT_POINTER>::value);
	EXPECT_FALSE(prism::IsEnum<LREF>::value);
	EXPECT_FALSE(prism::IsEnum<RREF>::value);
	EXPECT_FALSE(prism::IsEnum<POINTER_TO_T>::value);
	EXPECT_FALSE(prism::IsEnum<VOID>::value);

	//================================================================
	// todo this assertion should indeed be TRUE but currently fails as
	// IsEnum<T> is not properly implemented and always returns false
	//================================================================
	EXPECT_TRUE(prism::IsEnum<ENUM>::value);
	//================================================================
}

/**
 * Test: IsFloatingPoint<>
 */
TEST_F(type_traitsTest, isFloatingPoint) {
	// true EXPECTations
	EXPECT_TRUE(prism::IsFloatingPoint<FLOAT>::value);
	EXPECT_TRUE(prism::IsFloatingPoint<DOUBLE>::value);
	EXPECT_TRUE(prism::IsFloatingPoint<LONG_DOUBLE>::value);

	// false assertations
	EXPECT_FALSE(prism::IsFloatingPoint<ARRAY>::value);
	EXPECT_FALSE(prism::IsFloatingPoint<CHAR>::value);
	EXPECT_FALSE(prism::IsFloatingPoint<CLASS>::value);
	EXPECT_FALSE(prism::IsFloatingPoint<ENUM>::value);
	EXPECT_FALSE(prism::IsFloatingPoint<UNION>::value);
	EXPECT_FALSE(prism::IsFloatingPoint<INTEGRAL>::value);
	EXPECT_FALSE(prism::IsFloatingPoint<FUNCTION>::value);
	EXPECT_FALSE(prism::IsFloatingPoint<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_FALSE(prism::IsFloatingPoint<MEMBER_OBJECT_POINTER>::value);
	EXPECT_FALSE(prism::IsFloatingPoint<LREF>::value);
	EXPECT_FALSE(prism::IsFloatingPoint<RREF>::value);
	EXPECT_FALSE(prism::IsFloatingPoint<POINTER_TO_T>::value);
	EXPECT_FALSE(prism::IsFloatingPoint<VOID>::value);
}

/**
 * Test: IsFunction<>
 */
TEST_F(type_traitsTest, IsFunction) {
	EXPECT_TRUE(prism::IsFunction<FUNCTION>::value);

	EXPECT_FALSE(prism::IsFunction<ARRAY>::value);
	EXPECT_FALSE(prism::IsFunction<CLASS>::value);
	EXPECT_FALSE(prism::IsFunction<ENUM>::value);
	EXPECT_FALSE(prism::IsFunction<UNION>::value);
	EXPECT_FALSE(prism::IsFunction<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_FALSE(prism::IsFunction<MEMBER_OBJECT_POINTER>::value);
	EXPECT_FALSE(prism::IsFunction<LREF>::value);
	EXPECT_FALSE(prism::IsFunction<RREF>::value);
	EXPECT_FALSE(prism::IsFunction<POINTER_TO_T>::value);
	EXPECT_FALSE(prism::IsFunction<VOID>::value);
}

/**
 * Test: IsFundamental<>
 */
TEST_F(type_traitsTest, IsFundamental) {
	EXPECT_TRUE(prism::IsFundamental<float>::value);
	EXPECT_TRUE(prism::IsFundamental<double>::value);
	EXPECT_TRUE(prism::IsFundamental<long double>::value);
	EXPECT_TRUE(prism::IsFundamental<bool>::value);
	EXPECT_TRUE(prism::IsFundamental<char>::value);
	EXPECT_TRUE(prism::IsFundamental<unsigned char>::value);
	EXPECT_TRUE(prism::IsFundamental<short>::value);
	EXPECT_TRUE(prism::IsFundamental<unsigned short>::value);
	EXPECT_TRUE(prism::IsFundamental<int>::value);
	EXPECT_TRUE(prism::IsFundamental<unsigned int>::value);
	EXPECT_TRUE(prism::IsFundamental<long>::value);
	EXPECT_TRUE(prism::IsFundamental<unsigned long>::value);
	EXPECT_TRUE(prism::IsFundamental<long long>::value);
	EXPECT_TRUE(prism::IsFundamental<unsigned long long>::value);
	EXPECT_TRUE(prism::IsFundamental<VOID>::value);
	EXPECT_TRUE(prism::IsFundamental<std::nullptr_t>::value);

	EXPECT_FALSE(prism::IsFundamental<ARRAY>::value);
	EXPECT_FALSE(prism::IsFundamental<CLASS>::value);
	EXPECT_FALSE(prism::IsFundamental<ENUM>::value);
	EXPECT_FALSE(prism::IsFundamental<UNION>::value);
	EXPECT_FALSE(prism::IsFundamental<FUNCTION>::value);
	EXPECT_FALSE(prism::IsFundamental<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_FALSE(prism::IsFundamental<MEMBER_OBJECT_POINTER>::value);
	EXPECT_FALSE(prism::IsFundamental<LREF>::value);
	EXPECT_FALSE(prism::IsFundamental<RREF>::value);
	EXPECT_FALSE(prism::IsFundamental<POINTER_TO_T>::value);
}

/**
 * Test: IsIntegral<>
 */
TEST_F(type_traitsTest, isIntegral) {
	// true assertations
	EXPECT_TRUE(prism::IsIntegral<bool>::value);
	EXPECT_TRUE(prism::IsIntegral<char>::value);
	EXPECT_TRUE(prism::IsIntegral<signed char>::value);
	EXPECT_TRUE(prism::IsIntegral<unsigned char>::value);
	EXPECT_TRUE(prism::IsIntegral<short>::value);
	EXPECT_TRUE(prism::IsIntegral<unsigned short>::value);
	EXPECT_TRUE(prism::IsIntegral<int>::value);
	EXPECT_TRUE(prism::IsIntegral<unsigned int>::value);
	EXPECT_TRUE(prism::IsIntegral<long>::value);
	EXPECT_TRUE(prism::IsIntegral<unsigned long>::value);
	EXPECT_TRUE(prism::IsIntegral<long long>::value);
	EXPECT_TRUE(prism::IsIntegral<unsigned long long>::value);

	// false assertations
	EXPECT_FALSE(prism::IsIntegral<ARRAY>::value);
	EXPECT_FALSE(prism::IsIntegral<CLASS>::value);
	EXPECT_FALSE(prism::IsIntegral<DOUBLE>::value);
	EXPECT_FALSE(prism::IsIntegral<ENUM>::value);
	EXPECT_FALSE(prism::IsIntegral<UNION>::value);
	EXPECT_FALSE(prism::IsIntegral<FLOAT>::value);
	EXPECT_FALSE(prism::IsIntegral<FUNCTION>::value);
	EXPECT_FALSE(prism::IsIntegral<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_FALSE(prism::IsIntegral<MEMBER_OBJECT_POINTER>::value);
	EXPECT_FALSE(prism::IsIntegral<LREF>::value);
	EXPECT_FALSE(prism::IsIntegral<RREF>::value);
	EXPECT_FALSE(prism::IsIntegral<POINTER_TO_T>::value);
	EXPECT_FALSE(prism::IsIntegral<VOID>::value);
}

/**
 * Test: IsLValueReference<>
 */
TEST_F(type_traitsTest, IsLValueReference) {
	EXPECT_TRUE(prism::IsLValueReference<LREF>::value);
	EXPECT_TRUE(prism::IsLValueReference<CONST_LREF>::value);
	EXPECT_TRUE(prism::IsLValueReference<VOLATILE_LREF>::value);

	EXPECT_FALSE(prism::IsLValueReference<ARRAY>::value);
	EXPECT_FALSE(prism::IsLValueReference<CLASS>::value);
	EXPECT_FALSE(prism::IsLValueReference<ENUM>::value);
	EXPECT_FALSE(prism::IsLValueReference<UNION>::value);
	EXPECT_FALSE(prism::IsLValueReference<FLOATING_POINT>::value);
	EXPECT_FALSE(prism::IsLValueReference<INTEGRAL>::value);
	EXPECT_FALSE(prism::IsLValueReference<FUNCTION>::value);
	EXPECT_FALSE(prism::IsLValueReference<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_FALSE(prism::IsLValueReference<MEMBER_OBJECT_POINTER>::value);
	EXPECT_FALSE(prism::IsLValueReference<RREF>::value);
	EXPECT_FALSE(prism::IsLValueReference<POINTER_TO_T>::value);
	EXPECT_FALSE(prism::IsLValueReference<VOID>::value);
}

/**
 * Test: IsMemberFunctionPointer<>
 */
TEST_F(type_traitsTest, IsMemberFunctionPointer) {
	EXPECT_TRUE(prism::IsMemberFunctionPointer<MEMBER_FUNCTION_POINTER>::value);

	EXPECT_FALSE(prism::IsMemberFunctionPointer<ARRAY>::value);
	EXPECT_FALSE(prism::IsMemberFunctionPointer<CLASS>::value);
	EXPECT_FALSE(prism::IsMemberFunctionPointer<ENUM>::value);
	EXPECT_FALSE(prism::IsMemberFunctionPointer<UNION>::value);
	EXPECT_FALSE(prism::IsMemberFunctionPointer<FLOATING_POINT>::value);
	EXPECT_FALSE(prism::IsMemberFunctionPointer<INTEGRAL>::value);
	EXPECT_FALSE(prism::IsMemberFunctionPointer<FUNCTION>::value);
	EXPECT_FALSE(prism::IsMemberFunctionPointer<MEMBER_OBJECT_POINTER>::value);
	EXPECT_FALSE(prism::IsMemberFunctionPointer<LREF>::value);
	EXPECT_FALSE(prism::IsMemberFunctionPointer<RREF>::value);
	EXPECT_FALSE(prism::IsMemberFunctionPointer<POINTER_TO_T>::value);
	EXPECT_FALSE(prism::IsMemberFunctionPointer<VOID>::value);
}

/**
 * Test: IsMemberObjectPointer<>
 */
TEST_F(type_traitsTest, IsMemberObjectPointer) {
	EXPECT_TRUE(prism::IsMemberObjectPointer<MEMBER_OBJECT_POINTER>::value);

	EXPECT_FALSE(prism::IsMemberObjectPointer<ARRAY>::value);
	EXPECT_FALSE(prism::IsMemberObjectPointer<CLASS>::value);
	EXPECT_FALSE(prism::IsMemberObjectPointer<ENUM>::value);
	EXPECT_FALSE(prism::IsMemberObjectPointer<UNION>::value);
	EXPECT_FALSE(prism::IsMemberObjectPointer<FLOATING_POINT>::value);
	EXPECT_FALSE(prism::IsMemberObjectPointer<INTEGRAL>::value);
	EXPECT_FALSE(prism::IsMemberObjectPointer<FUNCTION>::value);
	EXPECT_FALSE(prism::IsMemberObjectPointer<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_FALSE(prism::IsMemberObjectPointer<LREF>::value);
	EXPECT_FALSE(prism::IsMemberObjectPointer<RREF>::value);
	EXPECT_FALSE(prism::IsMemberObjectPointer<POINTER_TO_T>::value);
	EXPECT_FALSE(prism::IsMemberObjectPointer<VOID>::value);
}

/**
 * Test: IsMemberPointer<>
 */
TEST_F(type_traitsTest, IsMemberPointer) {
	EXPECT_TRUE(prism::IsMemberPointer<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_TRUE(prism::IsMemberPointer<MEMBER_OBJECT_POINTER>::value);

	EXPECT_FALSE(prism::IsMemberPointer<ARRAY>::value);
	EXPECT_FALSE(prism::IsMemberPointer<CLASS>::value);
	EXPECT_FALSE(prism::IsMemberPointer<ENUM>::value);
	EXPECT_FALSE(prism::IsMemberPointer<UNION>::value);
	EXPECT_FALSE(prism::IsMemberPointer<FLOATING_POINT>::value);
	EXPECT_FALSE(prism::IsMemberPointer<INTEGRAL>::value);
	EXPECT_FALSE(prism::IsMemberPointer<FUNCTION>::value);
	EXPECT_FALSE(prism::IsMemberPointer<LREF>::value);
	EXPECT_FALSE(prism::IsMemberPointer<RREF>::value);
	EXPECT_FALSE(prism::IsMemberPointer<POINTER_TO_T>::value);
	EXPECT_FALSE(prism::IsMemberPointer<VOID>::value);
}

/**
 * Test: IsPointer<>
 */
TEST_F(type_traitsTest, IsPointer) {
	EXPECT_TRUE(prism::IsPointer<POINTER_TO_T>::value);
	EXPECT_TRUE(prism::IsPointer<POINTER_TO_CONST_T>::value);
	EXPECT_TRUE(prism::IsPointer<POINTER_TO_VOLATILE_T>::value);
	EXPECT_TRUE(prism::IsPointer<CONST_POINTER_TO_T>::value);
	EXPECT_TRUE(prism::IsPointer<CONST_POINTER_TO_CONST_T>::value);
	EXPECT_TRUE(prism::IsPointer<VOLATILE_POINTER_TO_T>::value);
	EXPECT_TRUE(prism::IsPointer<VOLATILE_POINTER_TO_VOLATILE_T>::value);
	EXPECT_TRUE(prism::IsPointer<VOLATILE_POINTER_TO_CONST_T>::value);

	EXPECT_FALSE(prism::IsPointer<ARRAY>::value);
	EXPECT_FALSE(prism::IsPointer<CHAR>::value);
	EXPECT_FALSE(prism::IsPointer<CLASS>::value);
	EXPECT_FALSE(prism::IsPointer<FLOATING_POINT>::value);
	EXPECT_FALSE(prism::IsPointer<ENUM>::value);
	EXPECT_FALSE(prism::IsPointer<UNION>::value);
	EXPECT_FALSE(prism::IsPointer<INTEGRAL>::value);
	EXPECT_FALSE(prism::IsPointer<FUNCTION>::value);
	EXPECT_FALSE(prism::IsPointer<MEMBER_OBJECT_POINTER>::value);
	EXPECT_FALSE(prism::IsPointer<LREF>::value);
	EXPECT_FALSE(prism::IsPointer<RREF>::value);
	EXPECT_FALSE(prism::IsPointer<VOID>::value);
}

/**
 * Test: IsObject<>
 */
TEST_F(type_traitsTest, IsObject) {
	EXPECT_TRUE(prism::IsObject<ARRAY>::value);
	EXPECT_TRUE(prism::IsObject<CLASS>::value);
	EXPECT_TRUE(prism::IsObject<UNION>::value);
	EXPECT_TRUE(prism::IsObject<FLOATING_POINT>::value);
	EXPECT_TRUE(prism::IsObject<INTEGRAL>::value);
	EXPECT_TRUE(prism::IsObject<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_TRUE(prism::IsObject<MEMBER_OBJECT_POINTER>::value);
	EXPECT_TRUE(prism::IsObject<POINTER_TO_T>::value);
	EXPECT_TRUE(prism::IsObject<std::nullptr_t>::value);

	EXPECT_FALSE(prism::IsObject<FUNCTION>::value);
	EXPECT_FALSE(prism::IsObject<LREF>::value);
	EXPECT_FALSE(prism::IsObject<RREF>::value);
	EXPECT_FALSE(prism::IsObject<VOID>::value);

	//================================================================
	// todo this assertion should indeed be TRUE but currently fails as
	// IsEnum<T> is not properly implemented and always returns false
	//================================================================
	EXPECT_TRUE(prism::IsObject<ENUM>::value);
	//================================================================
}

/**
 * Test: IsReferenceable<>
 * -- an object or reference is referenceable
 */
TEST_F(type_traitsTest, IsReferenceable) {
	EXPECT_TRUE(prism::IsReferenceable<ARRAY>::value);
	EXPECT_TRUE(prism::IsReferenceable<CLASS>::value);
	EXPECT_TRUE(prism::IsReferenceable<FLOATING_POINT>::value);
	EXPECT_TRUE(prism::IsReferenceable<INTEGRAL>::value);
	EXPECT_TRUE(prism::IsReferenceable<FUNCTION>::value);
	EXPECT_TRUE(prism::IsReferenceable<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_TRUE(prism::IsReferenceable<MEMBER_OBJECT_POINTER>::value);
	EXPECT_TRUE(prism::IsReferenceable<LREF>::value);
	EXPECT_TRUE(prism::IsReferenceable<RREF>::value);

	EXPECT_FALSE(prism::IsReferenceable<VOID>::value);

	//================================================================
	// todo this assertion should indeed be TRUE but currently fails as
	// IsEnum<T> is not properly implemented and always returns false.
	//================================================================
	EXPECT_TRUE(prism::IsReferenceable<ENUM>::value);
	//================================================================
}

/**
 * Test: IsReference<>
 */
TEST_F(type_traitsTest, IsReference) {
	EXPECT_TRUE(prism::IsReference<LREF>::value);
	EXPECT_TRUE(prism::IsReference<RREF>::value);

	EXPECT_FALSE(prism::IsReference<ARRAY>::value);
	EXPECT_FALSE(prism::IsReference<CLASS>::value);
	EXPECT_FALSE(prism::IsReference<ENUM>::value);
	EXPECT_FALSE(prism::IsReference<UNION>::value);
	EXPECT_FALSE(prism::IsReference<FLOATING_POINT>::value);
	EXPECT_FALSE(prism::IsReference<INTEGRAL>::value);
	EXPECT_FALSE(prism::IsReference<FUNCTION>::value);
	EXPECT_FALSE(prism::IsReference<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_FALSE(prism::IsReference<MEMBER_OBJECT_POINTER>::value);
	EXPECT_FALSE(prism::IsReference<POINTER_TO_T>::value);
	EXPECT_FALSE(prism::IsReference<VOID>::value);
}

/**
 * Test: IsRValueReference<>
 */
TEST_F(type_traitsTest, IsRValueReference) {
	EXPECT_TRUE(prism::IsRValueReference<RREF>::value);
	EXPECT_TRUE(prism::IsRValueReference<CONST_RREF>::value);
	EXPECT_TRUE(prism::IsRValueReference<VOLATILE_RREF>::value);

	EXPECT_FALSE(prism::IsRValueReference<ARRAY>::value);
	EXPECT_FALSE(prism::IsRValueReference<CLASS>::value);
	EXPECT_FALSE(prism::IsRValueReference<ENUM>::value);
	EXPECT_FALSE(prism::IsRValueReference<UNION>::value);
	EXPECT_FALSE(prism::IsRValueReference<FLOATING_POINT>::value);
	EXPECT_FALSE(prism::IsRValueReference<INTEGRAL>::value);
	EXPECT_FALSE(prism::IsRValueReference<FUNCTION>::value);
	EXPECT_FALSE(prism::IsRValueReference<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_FALSE(prism::IsRValueReference<MEMBER_OBJECT_POINTER>::value);
	EXPECT_FALSE(prism::IsRValueReference<LREF>::value);
	EXPECT_FALSE(prism::IsRValueReference<POINTER_TO_T>::value);
	EXPECT_FALSE(prism::IsRValueReference<VOID>::value);
}

/**
 * Test: IsScalar<>
 */
TEST_F(type_traitsTest, IsScalar) {
	EXPECT_TRUE(prism::IsScalar<FLOATING_POINT>::value);
	EXPECT_TRUE(prism::IsScalar<INTEGRAL>::value);
	EXPECT_TRUE(prism::IsScalar<std::nullptr_t>::value);
	EXPECT_TRUE(prism::IsScalar<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_TRUE(prism::IsScalar<MEMBER_OBJECT_POINTER>::value);
	EXPECT_TRUE(prism::IsScalar<POINTER_TO_T>::value);

	EXPECT_FALSE(prism::IsScalar<ARRAY>::value);
	EXPECT_FALSE(prism::IsScalar<CLASS>::value);
	EXPECT_FALSE(prism::IsScalar<UNION>::value);
	EXPECT_FALSE(prism::IsScalar<FUNCTION>::value);
	EXPECT_FALSE(prism::IsScalar<LREF>::value);
	EXPECT_FALSE(prism::IsScalar<RREF>::value);
	EXPECT_FALSE(prism::IsScalar<VOID>::value);

	//================================================================
	// todo this assertion should indeed be TRUE but currently fails as
	// IsEnum<T> is not properly implemented and always returns false
	//================================================================
	EXPECT_TRUE(prism::IsScalar<ENUM>::value);
	//================================================================
}

/**
 * Test: IsSigned<>
 */
TEST_F(type_traitsTest, IsSigned) {
	EXPECT_TRUE(prism::IsSigned<INTEGRAL>::value);
	EXPECT_TRUE(prism::IsSigned<SIGNED_INTEGRAL>::value);

	EXPECT_FALSE(prism::IsSigned<UNSIGNED_INTEGRAL>::value);
	EXPECT_FALSE(prism::IsSigned<ARRAY>::value);
	EXPECT_FALSE(prism::IsSigned<CLASS>::value);
	EXPECT_FALSE(prism::IsSigned<ENUM>::value);
	EXPECT_FALSE(prism::IsSigned<UNION>::value);
	EXPECT_FALSE(prism::IsSigned<FUNCTION>::value);
	EXPECT_FALSE(prism::IsSigned<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_FALSE(prism::IsSigned<MEMBER_OBJECT_POINTER>::value);
	EXPECT_FALSE(prism::IsSigned<LREF>::value);
	EXPECT_FALSE(prism::IsSigned<RREF>::value);
	EXPECT_FALSE(prism::IsSigned<POINTER_TO_T>::value);
	EXPECT_FALSE(prism::IsSigned<VOID>::value);
}

/**
 * Test: IsUnion<>
 */
TEST_F(type_traitsTest, IsUnion) {
	// this fails because IsClass returns true for a union
	EXPECT_TRUE(std::is_class<UNION>::value);
}

/**
 * Test: IsUnsigned<>
 */
TEST_F(type_traitsTest, IsUnsigned) {
	EXPECT_TRUE(prism::IsUnsigned<UNSIGNED_INTEGRAL>::value);

	EXPECT_FALSE(prism::IsUnsigned<INTEGRAL>::value);
	EXPECT_FALSE(prism::IsUnsigned<SIGNED_INTEGRAL>::value);
	EXPECT_FALSE(prism::IsUnsigned<ARRAY>::value);
	EXPECT_FALSE(prism::IsUnsigned<CLASS>::value);
	EXPECT_FALSE(prism::IsUnsigned<ENUM>::value);
	EXPECT_FALSE(prism::IsUnsigned<UNION>::value);
	EXPECT_FALSE(prism::IsUnsigned<FUNCTION>::value);
	EXPECT_FALSE(prism::IsUnsigned<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_FALSE(prism::IsUnsigned<MEMBER_OBJECT_POINTER>::value);
	EXPECT_FALSE(prism::IsUnsigned<LREF>::value);
	EXPECT_FALSE(prism::IsUnsigned<RREF>::value);
	EXPECT_FALSE(prism::IsUnsigned<POINTER_TO_T>::value);
	EXPECT_FALSE(prism::IsUnsigned<VOID>::value);
}

/**
 * Test: IsVoid
 */
TEST_F(type_traitsTest, IsVoid) {
	EXPECT_TRUE(prism::IsVoid<VOID>::value);

	EXPECT_FALSE(prism::IsVoid<void*>::value);
	EXPECT_FALSE(prism::IsVoid<ARRAY>::value);
	EXPECT_FALSE(prism::IsVoid<CLASS>::value);
	EXPECT_FALSE(prism::IsVoid<ENUM>::value);
	EXPECT_FALSE(prism::IsVoid<UNION>::value);
	EXPECT_FALSE(prism::IsVoid<FUNCTION>::value);
	EXPECT_FALSE(prism::IsVoid<MEMBER_FUNCTION_POINTER>::value);
	EXPECT_FALSE(prism::IsVoid<MEMBER_OBJECT_POINTER>::value);
	EXPECT_FALSE(prism::IsVoid<LREF>::value);
	EXPECT_FALSE(prism::IsVoid<RREF>::value);
	EXPECT_FALSE(prism::IsVoid<POINTER_TO_T>::value);
}

/**
 * Test: IsVolatile<>
 */
TEST_F(type_traitsTest, IsVolatile) {
	EXPECT_TRUE(	prism::IsVolatile<	VOLATILE_INTEGRAL>::value);
	EXPECT_TRUE(	prism::IsVolatile<	CONST_VOLATILE_INTEGRAL>::value);

	EXPECT_TRUE(	prism::IsVolatile<	VOLATILE_POINTER_TO_T>::value);
	EXPECT_TRUE(	prism::IsVolatile<	VOLATILE_POINTER_TO_CONST_T>::value);
	EXPECT_TRUE(	prism::IsVolatile<	VOLATILE_FLOAT>::value);
	EXPECT_TRUE(	prism::IsVolatile<	VOLATILE_MEMBER_OBJECT_POINTER>::value);
	EXPECT_TRUE(	prism::IsVolatile<	VOLATILE_ENUM>::value);
	EXPECT_TRUE(	prism::IsVolatile<	VOLATILE_UNION>::value);

	EXPECT_FALSE(	prism::IsVolatile<	INTEGRAL>::value);
	EXPECT_FALSE(	prism::IsVolatile<	FLOAT>::value);
	EXPECT_FALSE(	prism::IsVolatile<	MEMBER_OBJECT_POINTER>::value);
	EXPECT_FALSE(	prism::IsVolatile<	MEMBER_FUNCTION_POINTER>::value);
	EXPECT_FALSE(	prism::IsVolatile<	POINTER_TO_T>::value);
	EXPECT_FALSE(	prism::IsVolatile<	POINTER_TO_CONST_T>::value);
	EXPECT_FALSE(	prism::IsVolatile<	LREF>::value);
	EXPECT_FALSE(	prism::IsVolatile<	RREF>::value);
	EXPECT_FALSE(	prism::IsVolatile<	ENUM>::value);
	EXPECT_FALSE(	prism::IsVolatile<	ARRAY>::value);
	EXPECT_FALSE(	prism::IsVolatile<	UNION>::value);
	EXPECT_FALSE(	prism::IsVolatile<	FUNCTION>::value);
}

/**
 * Test: move()
 */
TEST_F(type_traitsTest, move) {
	int x = 22;
	const int cx = x;
	const int& rx = x;

	EXPECT_TRUE(typeid(int&&) == typeid(prism::move(x)));
	EXPECT_TRUE(typeid(int&&) == typeid(prism::move(cx)));
	EXPECT_TRUE(typeid(int&&) == typeid(prism::move(rx)));
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

	EXPECT_TRUE(EitherConditionTrue1::value);
	EXPECT_TRUE(EitherConditionTrue2::value);
	EXPECT_FALSE(BothConditionsFalse::value);
	EXPECT_TRUE(BothConditionsTrue::value);
	EXPECT_TRUE(AllConditionsTrue::value);
	EXPECT_FALSE(AllConditionsFalse::value);
}

/**
 * Test: RemoveAllExtents<>
 */
TEST_F(type_traitsTest, RemoveAllExtents) {
	EXPECT_TRUE(typeid(int) == typeid(RemoveAllExtents<int>::type));
	EXPECT_TRUE(typeid(int) == typeid(RemoveAllExtents<int[]>::type));
	EXPECT_TRUE(typeid(int) == typeid(RemoveAllExtents<int[5]>::type));
	EXPECT_TRUE(typeid(int) == typeid(RemoveAllExtents<int[5][10]>::type));
}

/**
 * Test: RemoveConst<>
 */
TEST_F(type_traitsTest, RemoveConst) {
	using T1 = prism::RemoveConst<CONST_FLOAT>::type;
	EXPECT_TRUE(typeid(T1) == typeid(FLOAT));

	using T2 = prism::RemoveConst<CONST_POINTER_TO_T>::type;
	EXPECT_TRUE(typeid(T2) == typeid(POINTER_TO_T));

	using T3 = prism::RemoveConst<CONST_POINTER_TO_CONST_T>::type;
	EXPECT_TRUE(typeid(T3) == typeid(POINTER_TO_CONST_T));

	using T4 = prism::RemoveConst<POINTER_TO_CONST_T>::type;
	EXPECT_TRUE(typeid(T4) == typeid(POINTER_TO_CONST_T));
}

/**
 * Test: RemoveConstVolatile<>
 */
TEST_F(type_traitsTest, RemoveConstVolatile) {
	using T1 = prism::RemoveConstVolatile<CONST_VOLATILE_POINTER_TO_T>::type;
	EXPECT_TRUE(typeid(T1) == typeid(POINTER_TO_T));

	using T2 = prism::RemoveConstVolatile<CONST_POINTER_TO_T>::type;
	EXPECT_TRUE(typeid(T2) == typeid(POINTER_TO_T));

	using T3 = prism::RemoveConstVolatile<VOLATILE_POINTER_TO_T>::type;
	EXPECT_TRUE(typeid(T3) == typeid(POINTER_TO_T));

	using T4 = prism::RemoveConstVolatile<CONST_INTEGRAL>::type;
	EXPECT_TRUE(typeid(T4) == typeid(INTEGRAL));

	using T5 = prism::RemoveConstVolatile<VOLATILE_INTEGRAL>::type;
	EXPECT_TRUE(typeid(T5) == typeid(INTEGRAL));
}

/**
 * Test: RemoveExtent<>
 */
TEST_F(type_traitsTest, RemoveExtent) {
	EXPECT_TRUE(typeid(int) == typeid(RemoveExtent<int>::type));
	EXPECT_TRUE(typeid(int) == typeid(RemoveExtent<int[]>::type));
	EXPECT_TRUE(typeid(int) == typeid(RemoveExtent<int[5]>::type));
	EXPECT_TRUE(typeid(int[10]) == typeid(RemoveExtent<int[5][10]>::type));
}

/**
 * Test: RemoveReference<>
 */
TEST_F(type_traitsTest, RemoveReference) {
	using T1 = prism::RemoveReference<int>::type;
	EXPECT_TRUE(typeid(T1) == typeid(int));

	using T2 = prism::RemoveReference<int&>::type;
	EXPECT_TRUE(typeid(T2) == typeid(int));

	using T3 = prism::RemoveReference<int&&>::type;
	EXPECT_TRUE(typeid(T3) == typeid(int));

	using T4 = int&&; // rvalue int
	EXPECT_TRUE(typeid(T4) == typeid(int));

}

/**
 * Test: RemoveVolatile<>
 */
TEST_F(type_traitsTest, RemoveVolatile) {
	using T1 = prism::RemoveVolatile<VOLATILE_FLOAT>::type;
	EXPECT_TRUE(typeid(T1) == typeid(FLOAT));

	using T2 = prism::RemoveVolatile<VOLATILE_POINTER_TO_T>::type;
	EXPECT_TRUE(typeid(T2) == typeid(POINTER_TO_T));

	using T3 = prism::RemoveVolatile<VOLATILE_POINTER_TO_CONST_T>::type;
	EXPECT_TRUE(typeid(T3) == typeid(POINTER_TO_CONST_T));

	using T4 = prism::RemoveVolatile<POINTER_TO_VOLATILE_T>::type;
	EXPECT_TRUE(typeid(T4) == typeid(POINTER_TO_VOLATILE_T));
}

} // end namespace test
} // end namespace prism























