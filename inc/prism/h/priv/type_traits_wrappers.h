/*
 * type_traits_wrappers.h
 * v1
 *
 *  Created on: 30 Nov 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_TYPE_TRAITS_WRAPPERS_H_
#define PRISM_TYPE_TRAITS_WRAPPERS_H_

#include <prism/h/global.h>
#include <type_traits>

PRISM_BEGIN_NAMESPACE

//============================================================================================
// AlignmentOf
//============================================================================================
template <typename T>
struct AlignmentOf : public std::alignment_of<T>{};
//============================================================================================
// HasVirtualDestructor
//============================================================================================
template <typename T>
struct HasVirtualDestructor : public std::has_virtual_destructor<T>{};
//============================================================================================
// IsAbstract
//============================================================================================
template <typename T>
struct IsAbstract : public std::is_abstract<T>{};
//============================================================================================
// IsAssignable
//============================================================================================
template <typename T, typename U>
struct IsAssignable : public std::is_assignable<T,U>{};
//============================================================================================
// IsBaseOf
//============================================================================================
template <typename B, typename D>
struct IsBaseOf : public std::is_base_of<B,D>{};
//============================================================================================
// IsConstructible
//============================================================================================
template <typename T, typename ...Args>
struct IsConstructible : public std::is_constructible<T,Args...>{};
//============================================================================================
// IsConvertible
//============================================================================================
template <typename From, typename To>
struct IsConvertible : public std::is_convertible<From,To>{};
//============================================================================================
// IsCopyAssignable
//============================================================================================
template <typename T>
struct IsCopyAssignable : public std::is_copy_assignable<T>{};
//============================================================================================
// IsCopyConstructible
//============================================================================================
template <typename T>
struct IsCopyConstructible : public std::is_copy_constructible<T>{};
//============================================================================================
// IsDestructible
//============================================================================================
template <typename T>
struct IsDestructible : public std::is_destructible<T>{};
//============================================================================================
// IsEmpty
//============================================================================================
template <typename T>
struct IsEmpty : public std::is_empty<T>{};
//============================================================================================
// IsEnum
//============================================================================================
template <typename T>
struct IsEnum : public std::is_enum<T>{};
//============================================================================================
// IsLiteralType
//============================================================================================
template <typename T>
struct IsLiteralType : public std::is_literal_type<T>{};
//============================================================================================
// IsMoveAssignable
//============================================================================================
template <typename T>
struct IsMoveAssignable : public std::is_move_assignable<T>{};
//============================================================================================
// IsMoveConstructible
//============================================================================================
template <typename T>
struct IsMoveConstructible : public std::is_move_constructible<T>{};
//============================================================================================
// IsNoThrowAssignable
//============================================================================================
template <typename T, typename U>
struct IsNoThrowAssignable : public std::is_nothrow_assignable<T,U>{};
//============================================================================================
// IsNoThrowConstructible
//============================================================================================
template <typename T, typename ...Args>
struct IsNoThrowConstructible : public std::is_nothrow_constructible<T,Args...>{};
//============================================================================================
// IsNoThrowCopyAssignable
//============================================================================================
template <typename T>
struct IsNoThrowCopyAssignable : public std::is_nothrow_copy_assignable<T>{};
//============================================================================================
// IsNoThrowCopyConstructible
//============================================================================================
template <typename T>
struct IsNoThrowCopyConstructible : public std::is_nothrow_copy_constructible<T>{};
//============================================================================================
// IsNoThrowDefaultConstructible
//============================================================================================
template <typename T>
struct IsNoThrowDefaultConstructible : public std::is_nothrow_default_constructible<T>{};
//============================================================================================
// IsNoThrowDestructible
//============================================================================================
template <typename T>
struct IsNoThrowDestructible : public std::is_nothrow_destructible<T>{};
//============================================================================================
// IsNoThrowMoveAssignable
//============================================================================================
template <typename T>
struct IsNoThrowMoveAssignable : public std::is_nothrow_move_assignable<T>{};
//============================================================================================
// IsNoThrowMoveConstructible
//============================================================================================
template <typename T>
struct IsNoThrowMoveConstructible : public std::is_nothrow_move_constructible<T>{};
//============================================================================================
// IsPod
//============================================================================================
template <typename T>
struct IsPod : public std::is_pod<T>{};
//============================================================================================
// IsPolymorphic
//============================================================================================
template <typename T>
struct IsPolymorphic : public std::is_polymorphic<T>{};
//============================================================================================
// IsStandardLayout
//============================================================================================
template <typename T>
struct IsStandardLayout : public std::is_standard_layout<T>{};
//============================================================================================
// IsTrivial
//============================================================================================
template <typename T>
struct IsTrivial : public std::is_trivial<T>{};
//============================================================================================
// IsTriviallyAssignable
//============================================================================================
template <typename T, typename U>
struct IsTriviallyAssignable : public std::is_trivially_assignable<T,U>{};
//============================================================================================
// IsTriviallyConstructible
//============================================================================================
template <typename T, typename ...Args>
struct IsTriviallyConstructible : public std::is_trivially_constructible<T,Args...>{};
//============================================================================================
// IsTriviallyCopyable
//============================================================================================
template <typename T>
struct IsTriviallyCopyable : public std::is_trivially_copyable<T>{};
//============================================================================================
// IsTriviallyCopyAssignable
//============================================================================================
template <typename T>
struct IsTriviallyCopyAssignable : public std::is_trivially_copy_assignable<T>{};
//============================================================================================
// IsTriviallyCopyConstructible
//============================================================================================
template <typename T>
struct IsTriviallyCopyConstructible : public std::is_trivially_copy_constructible<T>{};
//============================================================================================
// IsTriviallyDefaultConstructible
//============================================================================================
template <typename T>
struct IsTriviallyDefaultConstructible : public std::is_trivially_default_constructible<T>{};
//============================================================================================
// IsTriviallyDestructible
//============================================================================================
template <typename T>
struct IsTriviallyDestructible : public std::is_trivially_destructible<T>{};
//============================================================================================
// IsTriviallyMoveAssignable
//============================================================================================
template <typename T>
struct IsTriviallyMoveAssignable : public std::is_trivially_move_assignable<T>{};
//============================================================================================
// IsTriviallyMoveconstructible
//============================================================================================
template <typename T>
struct IsTriviallyMoveConstructible : public std::is_trivially_move_constructible<T>{};
//============================================================================================
// IsUnion
//============================================================================================
template <typename T>
struct IsUnion : public std::is_union<T>{};
//============================================================================================
// Rank
//============================================================================================
template <typename T>
struct Rank : public std::rank<T>{};

PRISM_END_NAMESPACE
#endif /* PRISM_TYPE_TRAITS_WRAPPERS_H_ */











