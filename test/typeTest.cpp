/*
 * typeTest.cpp
 * v1
 *
 *  Created on: Nov 2, 2016
 *      Author: iainhemstock
 */

#include <gtest/gtest.h>
#include <prism/h/type2.h>

namespace prism {
namespace test {

class typeTest : public ::testing::Test {

};

/**
 * Test: IsConst<>
 */
TEST_F(typeTest, IsConst) {
	ASSERT_TRUE(prism::IsConst<const int>::value);
	ASSERT_TRUE(prism::IsConst<const volatile int>::value);
	ASSERT_TRUE(prism::IsConst<int* const>::value);

	ASSERT_FALSE(prism::IsConst<int>::value);
	ASSERT_FALSE(prism::IsConst<int*>::value);
	ASSERT_FALSE(prism::IsConst<const int*>::value);
	ASSERT_FALSE(prism::IsConst<int&>::value);
	ASSERT_FALSE(prism::IsConst<int&&>::value);
}

/**
 * Test: IsVolatile<>
 */
TEST_F(typeTest, IsVolatile) {
	ASSERT_TRUE(prism::IsVolatile<volatile int>::value);
	ASSERT_TRUE(prism::IsVolatile<const volatile int>::value);
	ASSERT_TRUE(prism::IsVolatile<int * volatile>::value);

	ASSERT_FALSE(prism::IsConst<int>::value);
	ASSERT_FALSE(prism::IsConst<int*>::value);
	ASSERT_FALSE(prism::IsConst<volatile  int*>::value);
	ASSERT_FALSE(prism::IsConst<int&>::value);
	ASSERT_FALSE(prism::IsConst<int&&>::value);
}

/*
 * Test: conditional_type<>
 * -- using two fundamental types
 */
TEST_F(typeTest, conditional_type_fundamental) {
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
TEST_F(typeTest, conditional_type_nonmember_pointers) {
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
TEST_F(typeTest, conditional_type_unions) {
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
TEST_F(typeTest, conditional_type_enums) {
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
TEST_F(typeTest, conditional_type_member_pointers) {
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
TEST_F(typeTest, conditional_type_arrays) {
	typedef prism::ConditionalType_t<true, char[1],int[1]> CharArrayType;
	typedef prism::ConditionalType_t<false, char[1],int[1]> IntArrayType;

	// CharTypeArray holds 1 char so should be the size of 1 char
	// IntTypeArray holds 1 int so should be the size of 1 int
	ASSERT_EQ(sizeof(CharArrayType), sizeof(char));
	ASSERT_EQ(sizeof(IntArrayType), sizeof(int));
}

/**
 * Test: Or<>
 */
TEST_F(typeTest, Or) {
	// first true, second false
	typedef prism::Or<
				prism::IsFloatingPoint<float>, 	// true
				prism::IsIntegral<float> 		// false
			>::type EitherConditionTrue1;

	// first false, second true
	typedef prism::Or<
				prism::IsFloatingPoint<char>, 	// false
				prism::IsIntegral<char> 		// true
			>::type EitherConditionTrue2;

	// both false
	typedef prism::Or<
				prism::IsFloatingPoint<void>, 	// false
				prism::IsIntegral<void> 		// false
			>::type EitherConditionTrue3;

	// both true
	typedef prism::Or<
				prism::IsFloatingPoint<float>,	// true
				prism::IsArithmetic<float>		// also true
			>::type EitherConditionTrue4;

	ASSERT_TRUE(EitherConditionTrue1::value);
	ASSERT_TRUE(EitherConditionTrue2::value);
	ASSERT_FALSE(EitherConditionTrue3::value);
	ASSERT_TRUE(EitherConditionTrue4::value);
}

/**
 * Test: And<>
 */
TEST_F(typeTest, And) {

	// both true
	typedef prism::And<
				prism::IsConst<const int>,	 	// true
				prism::IsIntegral<const int>	// true
			>::type BothConditionTrue1;

	// first true, second false
	typedef prism::And<
				prism::IsConst<const int>, 		// true
				prism::IsFloatingPoint<const int>// false
			>::type BothConditionTrue2;

	// first false, second true
	typedef prism::And<
				prism::IsFloatingPoint<const int>,// false
				prism::IsConst<const int> 		// true
			>::type BothConditionTrue3;

	// both false
	typedef prism::And<
				prism::IsFloatingPoint<const int>,	// false
				prism::IsVoid<const int>		// also false
			>::type BothConditionTrue4;

	ASSERT_TRUE(BothConditionTrue1::value);
	ASSERT_FALSE(BothConditionTrue2::value);
	ASSERT_FALSE(BothConditionTrue3::value);
	ASSERT_FALSE(BothConditionTrue4::value);
}

/**
 * Test: IsFloatingPoint<>
 */
TEST_F(typeTest, isFloatingPoint) {
	// true assertations
	ASSERT_TRUE(prism::IsFloatingPoint<float>::value);
	ASSERT_TRUE(prism::IsFloatingPoint<double>::value);
	ASSERT_TRUE(prism::IsFloatingPoint<long double>::value);
	ASSERT_TRUE(prism::IsFloatingPoint<const float>::value);
	ASSERT_TRUE(prism::IsFloatingPoint<const double>::value);
	ASSERT_TRUE(prism::IsFloatingPoint<const long double>::value);
	ASSERT_TRUE(prism::IsFloatingPoint<volatile float>::value);
	ASSERT_TRUE(prism::IsFloatingPoint<volatile double>::value);
	ASSERT_TRUE(prism::IsFloatingPoint<volatile long double>::value);
	ASSERT_TRUE(prism::IsFloatingPoint<const volatile float>::value);
	ASSERT_TRUE(prism::IsFloatingPoint<const volatile double>::value);
	ASSERT_TRUE(prism::IsFloatingPoint<const volatile long double>::value);

	// false assertations
	ASSERT_FALSE(prism::IsFloatingPoint<int>::value);
	ASSERT_FALSE(prism::IsFloatingPoint<char>::value);
	ASSERT_FALSE(prism::IsFloatingPoint<bool>::value);
}

/**
 * Test: IsIntegral<>
 */
TEST_F(typeTest, isIntegral) {
	// true assertations
	ASSERT_TRUE(prism::IsIntegral<bool>::value);
	ASSERT_TRUE(prism::IsIntegral<char>::value);
	ASSERT_TRUE(prism::IsIntegral<signed char>::value);
	ASSERT_TRUE(prism::IsIntegral<unsigned char>::value);
	ASSERT_TRUE(prism::IsIntegral<short>::value);
	ASSERT_TRUE(prism::IsIntegral<unsigned short>::value);
	ASSERT_TRUE(prism::IsIntegral<int>::value);
	ASSERT_TRUE(prism::IsIntegral<unsigned>::value);
	ASSERT_TRUE(prism::IsIntegral<long>::value);
	ASSERT_TRUE(prism::IsIntegral<unsigned long>::value);
	ASSERT_TRUE(prism::IsIntegral<long long>::value);
	ASSERT_TRUE(prism::IsIntegral<unsigned long long>::value);

	ASSERT_TRUE(prism::IsIntegral<const bool>::value);
	ASSERT_TRUE(prism::IsIntegral<const char>::value);
	ASSERT_TRUE(prism::IsIntegral<const signed char>::value);
	ASSERT_TRUE(prism::IsIntegral<const unsigned char>::value);
	ASSERT_TRUE(prism::IsIntegral<const short>::value);
	ASSERT_TRUE(prism::IsIntegral<const unsigned short>::value);
	ASSERT_TRUE(prism::IsIntegral<const int>::value);
	ASSERT_TRUE(prism::IsIntegral<const unsigned>::value);
	ASSERT_TRUE(prism::IsIntegral<const long>::value);
	ASSERT_TRUE(prism::IsIntegral<const unsigned long>::value);
	ASSERT_TRUE(prism::IsIntegral<const long long>::value);
	ASSERT_TRUE(prism::IsIntegral<const unsigned long long>::value);

	ASSERT_TRUE(prism::IsIntegral<volatile bool>::value);
	ASSERT_TRUE(prism::IsIntegral<volatile char>::value);
	ASSERT_TRUE(prism::IsIntegral<volatile signed char>::value);
	ASSERT_TRUE(prism::IsIntegral<volatile unsigned char>::value);
	ASSERT_TRUE(prism::IsIntegral<volatile short>::value);
	ASSERT_TRUE(prism::IsIntegral<volatile unsigned short>::value);
	ASSERT_TRUE(prism::IsIntegral<volatile int>::value);
	ASSERT_TRUE(prism::IsIntegral<volatile unsigned>::value);
	ASSERT_TRUE(prism::IsIntegral<volatile long>::value);
	ASSERT_TRUE(prism::IsIntegral<volatile unsigned long>::value);
	ASSERT_TRUE(prism::IsIntegral<volatile long long>::value);
	ASSERT_TRUE(prism::IsIntegral<volatile unsigned long long>::value);

	ASSERT_TRUE(prism::IsIntegral<const volatile bool>::value);
	ASSERT_TRUE(prism::IsIntegral<const volatile char>::value);
	ASSERT_TRUE(prism::IsIntegral<const volatile signed char>::value);
	ASSERT_TRUE(prism::IsIntegral<const volatile unsigned char>::value);
	ASSERT_TRUE(prism::IsIntegral<const volatile short>::value);
	ASSERT_TRUE(prism::IsIntegral<const volatile unsigned short>::value);
	ASSERT_TRUE(prism::IsIntegral<const volatile int>::value);
	ASSERT_TRUE(prism::IsIntegral<const volatile unsigned>::value);
	ASSERT_TRUE(prism::IsIntegral<const volatile long>::value);
	ASSERT_TRUE(prism::IsIntegral<const volatile unsigned long>::value);
	ASSERT_TRUE(prism::IsIntegral<const volatile long long>::value);
	ASSERT_TRUE(prism::IsIntegral<const volatile unsigned long long>::value);

	// false assertations
	ASSERT_FALSE(prism::IsIntegral<float>::value);
	ASSERT_FALSE(prism::IsIntegral<double>::value);
	ASSERT_FALSE(prism::IsIntegral<long double>::value);
	ASSERT_FALSE(prism::IsIntegral<void>::value);
	ASSERT_FALSE(prism::IsIntegral<std::nullptr_t>::value);
}

/**
 * Test: isArithmetic<>
 */
TEST_F(typeTest, IsArithmetic) {
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

	ASSERT_TRUE(prism::IsArithmetic<const float>::value);
	ASSERT_TRUE(prism::IsArithmetic<const double>::value);
	ASSERT_TRUE(prism::IsArithmetic<const long double>::value);
	ASSERT_TRUE(prism::IsArithmetic<const bool>::value);
	ASSERT_TRUE(prism::IsArithmetic<const char>::value);
	ASSERT_TRUE(prism::IsArithmetic<const unsigned char>::value);
	ASSERT_TRUE(prism::IsArithmetic<const short>::value);
	ASSERT_TRUE(prism::IsArithmetic<const unsigned short>::value);
	ASSERT_TRUE(prism::IsArithmetic<const int>::value);
	ASSERT_TRUE(prism::IsArithmetic<const unsigned int>::value);
	ASSERT_TRUE(prism::IsArithmetic<const long>::value);
	ASSERT_TRUE(prism::IsArithmetic<const unsigned long>::value);
	ASSERT_TRUE(prism::IsArithmetic<const long long>::value);
	ASSERT_TRUE(prism::IsArithmetic<const unsigned long long>::value);

	ASSERT_TRUE(prism::IsArithmetic<volatile float>::value);
	ASSERT_TRUE(prism::IsArithmetic<volatile double>::value);
	ASSERT_TRUE(prism::IsArithmetic<volatile long double>::value);
	ASSERT_TRUE(prism::IsArithmetic<volatile bool>::value);
	ASSERT_TRUE(prism::IsArithmetic<volatile char>::value);
	ASSERT_TRUE(prism::IsArithmetic<volatile unsigned char>::value);
	ASSERT_TRUE(prism::IsArithmetic<volatile short>::value);
	ASSERT_TRUE(prism::IsArithmetic<volatile unsigned short>::value);
	ASSERT_TRUE(prism::IsArithmetic<volatile int>::value);
	ASSERT_TRUE(prism::IsArithmetic<volatile unsigned int>::value);
	ASSERT_TRUE(prism::IsArithmetic<volatile long>::value);
	ASSERT_TRUE(prism::IsArithmetic<volatile unsigned long>::value);
	ASSERT_TRUE(prism::IsArithmetic<volatile long long>::value);
	ASSERT_TRUE(prism::IsArithmetic<volatile unsigned long long>::value);

	ASSERT_TRUE(prism::IsArithmetic<const volatile float>::value);
	ASSERT_TRUE(prism::IsArithmetic<const volatile double>::value);
	ASSERT_TRUE(prism::IsArithmetic<const volatile long double>::value);
	ASSERT_TRUE(prism::IsArithmetic<const volatile bool>::value);
	ASSERT_TRUE(prism::IsArithmetic<const volatile char>::value);
	ASSERT_TRUE(prism::IsArithmetic<const volatile unsigned char>::value);
	ASSERT_TRUE(prism::IsArithmetic<const volatile short>::value);
	ASSERT_TRUE(prism::IsArithmetic<const volatile unsigned short>::value);
	ASSERT_TRUE(prism::IsArithmetic<const volatile int>::value);
	ASSERT_TRUE(prism::IsArithmetic<const volatile unsigned int>::value);
	ASSERT_TRUE(prism::IsArithmetic<const volatile long>::value);
	ASSERT_TRUE(prism::IsArithmetic<const volatile unsigned long>::value);
	ASSERT_TRUE(prism::IsArithmetic<const volatile long long>::value);
	ASSERT_TRUE(prism::IsArithmetic<const volatile unsigned long long>::value);

	// false assertations
	ASSERT_FALSE(prism::IsArithmetic<void>::value);
	ASSERT_FALSE(prism::IsArithmetic<std::nullptr_t>::value);
}

/**
 * Test: IsFundamental<>
 */
TEST_F(typeTest, IsFundamental) {
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

	ASSERT_TRUE(prism::IsFundamental<const float>::value);
	ASSERT_TRUE(prism::IsFundamental<const double>::value);
	ASSERT_TRUE(prism::IsFundamental<const long double>::value);
	ASSERT_TRUE(prism::IsFundamental<const bool>::value);
	ASSERT_TRUE(prism::IsFundamental<const char>::value);
	ASSERT_TRUE(prism::IsFundamental<const unsigned char>::value);
	ASSERT_TRUE(prism::IsFundamental<const short>::value);
	ASSERT_TRUE(prism::IsFundamental<const unsigned short>::value);
	ASSERT_TRUE(prism::IsFundamental<const int>::value);
	ASSERT_TRUE(prism::IsFundamental<const unsigned int>::value);
	ASSERT_TRUE(prism::IsFundamental<const long>::value);
	ASSERT_TRUE(prism::IsFundamental<const unsigned long>::value);
	ASSERT_TRUE(prism::IsFundamental<const long long>::value);
	ASSERT_TRUE(prism::IsFundamental<const unsigned long long>::value);

	ASSERT_TRUE(prism::IsFundamental<volatile float>::value);
	ASSERT_TRUE(prism::IsFundamental<volatile double>::value);
	ASSERT_TRUE(prism::IsFundamental<volatile long double>::value);
	ASSERT_TRUE(prism::IsFundamental<volatile bool>::value);
	ASSERT_TRUE(prism::IsFundamental<volatile char>::value);
	ASSERT_TRUE(prism::IsFundamental<volatile unsigned char>::value);
	ASSERT_TRUE(prism::IsFundamental<volatile short>::value);
	ASSERT_TRUE(prism::IsFundamental<volatile unsigned short>::value);
	ASSERT_TRUE(prism::IsFundamental<volatile int>::value);
	ASSERT_TRUE(prism::IsFundamental<volatile unsigned int>::value);
	ASSERT_TRUE(prism::IsFundamental<volatile long>::value);
	ASSERT_TRUE(prism::IsFundamental<volatile unsigned long>::value);
	ASSERT_TRUE(prism::IsFundamental<volatile long long>::value);
	ASSERT_TRUE(prism::IsFundamental<volatile unsigned long long>::value);

	ASSERT_TRUE(prism::IsFundamental<const volatile float>::value);
	ASSERT_TRUE(prism::IsFundamental<const volatile double>::value);
	ASSERT_TRUE(prism::IsFundamental<const volatile long double>::value);
	ASSERT_TRUE(prism::IsFundamental<const volatile bool>::value);
	ASSERT_TRUE(prism::IsFundamental<const volatile char>::value);
	ASSERT_TRUE(prism::IsFundamental<const volatile unsigned char>::value);
	ASSERT_TRUE(prism::IsFundamental<const volatile short>::value);
	ASSERT_TRUE(prism::IsFundamental<const volatile unsigned short>::value);
	ASSERT_TRUE(prism::IsFundamental<const volatile int>::value);
	ASSERT_TRUE(prism::IsFundamental<const volatile unsigned int>::value);
	ASSERT_TRUE(prism::IsFundamental<const volatile long>::value);
	ASSERT_TRUE(prism::IsFundamental<const volatile unsigned long>::value);
	ASSERT_TRUE(prism::IsFundamental<const volatile long long>::value);
	ASSERT_TRUE(prism::IsFundamental<const volatile unsigned long long>::value);
}

/**
 * Test: IsSigned<>
 */
TEST_F(typeTest, IsSigned) {
		ASSERT_TRUE(prism::IsSigned<int>::value);
		ASSERT_TRUE(prism::IsSigned<signed int>::value);
		ASSERT_TRUE(prism::IsSigned<const signed int>::value);
		ASSERT_TRUE(prism::IsSigned<volatile signed int>::value);
		ASSERT_TRUE(prism::IsSigned<const volatile signed int>::value);

		ASSERT_FALSE(prism::IsSigned<unsigned int>::value);
}

/**
 * Test: IsUnsigned<>
 */
TEST_F(typeTest, IsUnsigned) {
	ASSERT_TRUE(prism::IsUnsigned<unsigned int>::value);
	ASSERT_TRUE(prism::IsUnsigned<const unsigned int>::value);
	ASSERT_TRUE(prism::IsUnsigned<volatile unsigned int>::value);
	ASSERT_TRUE(prism::IsUnsigned<const volatile unsigned int>::value);

	ASSERT_FALSE(prism::IsUnsigned<int>::value);
	ASSERT_FALSE(prism::IsUnsigned<signed int>::value);
}

/**
 * Test: IsPointer<>
 */
TEST_F(typeTest, IsPointer) {
	ASSERT_TRUE(prism::IsPointer<int*>::value);
	ASSERT_TRUE(prism::IsPointer<const int*>::value);
	ASSERT_TRUE(prism::IsPointer<volatile int*>::value);
	ASSERT_TRUE(prism::IsPointer<const volatile int*>::value);

	ASSERT_FALSE(prism::IsPointer<char>::value);
	ASSERT_FALSE(prism::IsPointer<char&>::value);
}

/**
 * Test: IsReference<>
 */
TEST_F(typeTest, IsReference) {
	ASSERT_TRUE(prism::IsReference<int&>::value);
	ASSERT_TRUE(prism::IsReference<const int&>::value);
	ASSERT_TRUE(prism::IsReference<volatile int&>::value);
	ASSERT_TRUE(prism::IsReference<const volatile int&>::value);
	ASSERT_TRUE(prism::IsReference<int&&>::value);
	ASSERT_TRUE(prism::IsReference<const int&&>::value);
	ASSERT_TRUE(prism::IsReference<volatile int&&>::value);
	ASSERT_TRUE(prism::IsReference<const volatile int&&>::value);

	ASSERT_FALSE(prism::IsReference<char>::value);
	ASSERT_FALSE(prism::IsReference<char*>::value);
}

/**
 * Test: IsRValueReference<>
 */
TEST_F(typeTest, IsRValueReference) {
	ASSERT_TRUE(prism::IsRValueReference<int&&>::value);
	ASSERT_TRUE(prism::IsRValueReference<const int&&>::value);
	ASSERT_TRUE(prism::IsRValueReference<volatile int&&>::value);
	ASSERT_TRUE(prism::IsRValueReference<const volatile int&&>::value);

	ASSERT_FALSE(prism::IsRValueReference<int&>::value);
	ASSERT_FALSE(prism::IsRValueReference<int*>::value);
	ASSERT_FALSE(prism::IsRValueReference<int>::value);
}

/**
 * Test: IsArray<>
 */
TEST_F(typeTest, IsArray) {
	ASSERT_TRUE(prism::IsArray<int[5]>::value);
	ASSERT_TRUE(prism::IsArray<const int[5]>::value);
	ASSERT_TRUE(prism::IsArray<volatile int[5]>::value);
	ASSERT_TRUE(prism::IsArray<const volatile int[5]>::value);
	ASSERT_TRUE(prism::IsArray<int*[5]>::value);
	ASSERT_TRUE(prism::IsArray<const int*[5]>::value);
	ASSERT_TRUE(prism::IsArray<volatile int*[5]>::value);
	ASSERT_TRUE(prism::IsArray<const volatile int*[5]>::value);

	ASSERT_FALSE(prism::IsArray<int>::value);
	ASSERT_FALSE(prism::IsArray<int*>::value);
	ASSERT_FALSE(prism::IsArray<int&>::value);
}

/**
 * Test: IsMemberPointer<>
 */
TEST_F(typeTest, IsMemberPointer) {
	struct A { int x;};
	int A::* mfp = &A::x;

	ASSERT_TRUE(prism::IsMemberPointer<int A::*>::value);
	ASSERT_TRUE(prism::IsMemberPointer<void (A::*)()>::value);
	ASSERT_TRUE(prism::IsMemberPointer<decltype(mfp)>::value);

	ASSERT_FALSE(prism::IsMemberPointer<int>::value);
	ASSERT_FALSE(prism::IsMemberPointer<int*>::value);
	ASSERT_FALSE(prism::IsMemberPointer<int&>::value);
}

/**
 * Test: IsMemberFunctionPointer<>
 */
TEST_F(typeTest, IsMemberFunctionPointer) {
	struct A { int x; void func(){}; };
	int A::* mop = &A::x;
	void(A::*mfp)() = &A::func;

	ASSERT_TRUE(prism::IsMemberFunctionPointer<void (A::*)()>::value);
	ASSERT_TRUE(prism::IsMemberFunctionPointer<decltype(mfp)>::value);

	ASSERT_FALSE(prism::IsMemberFunctionPointer<A*>::value);
	ASSERT_FALSE(prism::IsMemberFunctionPointer<decltype(mop)>::value);
}

/**
 * Test: IsMemberObjectPointer<>
 */
TEST_F(typeTest, IsMemberObjectPointer) {
	struct A { int x; void func(){}; };
	int A::* mop = &A::x;
	void(A::*mfp)() = &A::func;

	ASSERT_TRUE(prism::IsMemberObjectPointer<int A::*>::value);
	ASSERT_TRUE(prism::IsMemberObjectPointer<decltype(mop)>::value);

	ASSERT_FALSE(prism::IsMemberObjectPointer<void (A::*)()>::value);
	ASSERT_FALSE(prism::IsMemberObjectPointer<decltype(mfp)>::value);
}

/**
 * Test: IsClass<>
 */
TEST_F(typeTest, IsClass) {
	class A {};
	struct B {};
	union C{};
	ASSERT_TRUE(prism::IsClass<A>::value);
	ASSERT_TRUE(prism::IsClass<B>::value);
	ASSERT_TRUE(prism::IsClass<C>::value);

	ASSERT_FALSE(prism::IsClass<int>::value);
	ASSERT_FALSE(prism::IsClass<A*>::value);
	ASSERT_FALSE(prism::IsClass<int A::*>::value);
}

/**
 * Test: IsCompound<>
 */
TEST_F(typeTest, IsCompound) {
	class A{ public: int x; int y(){return x;}};

	ASSERT_TRUE(prism::IsCompound<int&>::value);			// l_reference
	ASSERT_TRUE(prism::IsCompound<int&&>::value);			// r_reference
	ASSERT_TRUE(prism::IsCompound<A>::value);				// class
	ASSERT_TRUE(prism::IsCompound<int[5]>::value);			// array
	ASSERT_TRUE(prism::IsCompound<int*>::value);			// pointer
	ASSERT_TRUE(prism::IsCompound<int A::*>::value);		// member pointer
	ASSERT_TRUE(prism::IsCompound<void (A::*)()>::value);	// member function pointer
	ASSERT_TRUE(prism::IsCompound<const int *>::value);

	ASSERT_FALSE(prism::IsCompound<int>::value);
	ASSERT_FALSE(prism::IsCompound<bool>::value);
	ASSERT_FALSE(prism::IsCompound<char>::value);
	ASSERT_FALSE(prism::IsCompound<void>::value);
}

/**
 * Test: IsScalar<>
 */
TEST_F(typeTest, IsScalar) {
	class A{ public: int x; int y(){return x;}};

	ASSERT_TRUE(prism::IsScalar<float>::value);
	ASSERT_TRUE(prism::IsScalar<int>::value);
	ASSERT_TRUE(prism::IsScalar<int A::*>::value);		// member pointer
	ASSERT_TRUE(prism::IsScalar<void (A::*)()>::value);	// member function pointer
	ASSERT_TRUE(prism::IsScalar<const int *>::value);
	ASSERT_TRUE(prism::IsScalar<int*>::value);

	ASSERT_FALSE(prism::IsScalar<void>::value);
	ASSERT_FALSE(prism::IsScalar<int[5]>::value);
	ASSERT_FALSE(prism::IsScalar<A>::value);
	ASSERT_FALSE(prism::IsScalar<int&>::value);
	ASSERT_FALSE(prism::IsScalar<int&&>::value);
	ASSERT_FALSE(prism::IsScalar<int(int)>::value); // is function

}

} // end namespace test
} // end namespace prism













