/*
 * UniquePointer.h
 * v1
 *
 *  Created on: Nov 8, 2016
 *      Author: iainhemstock
 */

#include <prism/h/global.h>

#ifndef PRISM_UNIQUE_POINTER_H_
#define PRISM_UNIQUE_POINTER_H_

PRISM_BEGIN_NAMESPACE

template <typename T>
struct UniquePointerDeleter;
//============================================================================================
// UniquePointer
//============================================================================================
template <typename T, typename D = prism::UniquePointerDeleter<T>>
class UniquePointer {
public:
	using pointer 		= T*;
	using element_type 	= T;
	using deleter_type	= D;

	/// 						Creates a UniquePointer that will manage the lifetime of a
	///							raw pointer (if supplied). If no pointer is supplied then the
	///							the UniquePointer is in a null state (empty but still valid).
	///							If a pointer is supplied then it is stored internally by the
	///							UniquePointer.
	///
	/// @param p				A raw pointer that the UniquePointer will take ownership of and
	///							will manage the deallocation of.
	///
	/// @since					1.0.0
	explicit UniquePointer(pointer p = nullptr);

	/// 						Explicitly disabled as a UniquePointer cannot be unique if it
	///							is allowable to be copyable
	///
	/// @since					1.0.0
	UniquePointer(const UniquePointer& copy) = delete;

	/// 						Explicitly disabled as a UniquePointer cannot be unique if it
	///							is allowable to be assignable
	///
	///							1.0.0
	UniquePointer&
	operator=(const UniquePointer& rhs) = delete;

	///							Destroys the UniquePointer and if it was managing a raw pointer
	///							then that pointer is deallocated too.
	/// @since					1.0.0
	~UniquePointer();

	///							Access the underlying raw pointer
	///
	///	@return					Returns the underlying raw pointer if one is being managed or a
	///							nullptr if not.
	///
	/// @since					1.0.0
	pointer
	data() const;

	///							Accesses the deleter object of the UniquePointer
	///
	/// @return					Returns the deleter_type object that was specified in the
	///							template arguments (prism::UniquePointerDeleter by default).
	///
	/// @since 					1.0.0
	deleter_type
	getDeleter() const;

	///							Checks if a raw pointer is being managed or not
	///
	/// @return					Returns true if a pointer is being managed and false otherwise
	///
	/// @since 					1.0.0
	const bool
	isNull() const;

	///							Releases ownership of the underlying raw pointer and returns it.
	///							The UniquePointer is now no longer managing the pointer and
	///							responsibility for it must be taken by some other entity. The
	///							UniquePointer becomes null but is still valid to be used again.
	///
	/// @return					The underlying raw pointer
	///
	/// @see					reset()
	///
	/// @since					1.0.0
	pointer
	release();

	///							The UniquePointer takes ownership of a new raw pointer
	///							deallocating any old pointer that is was previously managing.
	///
	/// @param p				The new raw pointer to be managed
	///
	/// @since					1.0.0
	void
	reset(pointer p = nullptr);

	///							Swaps the contents of two UniquePointers. After the swap, the
	///							first UniquePointer will manage the pointer from the second
	///							UniquePointer and vice versa.
	///
	/// @param other			Another UniquePointer to swap with this UniquePointer
	///
	/// @since					1.0.0
	void
	swap(UniquePointer& other);

	///							Accesses the UniquePointer's managed object
	///
	/// @since					1.0.0
	element_type
	operator*();

	///							Accesses the UniquePointer's managed object's members
	///
	/// @since					1.0.0
	pointer
	operator->();

	///	@return					Returns true if the UniquePointer is managing a raw pointer and
	///							false otherwise. This is useful in 'if' statements.
	explicit
	operator bool() const;

private:
	struct UniquePointerData;
	UniquePointerData * d;
};

/// Swaps the contents of two UniquePointers. After the swap, the first UniquePointer will
///	manage the pointer from the second UniquePointer and vice versa.
///
/// @since 1.0.0
template <typename T, typename D>
void swap(UniquePointer<T,D>& up1, UniquePointer<T,D>& up2);

PRISM_END_NAMESPACE

#include <prism/h/priv/UniquePointer_priv.h>

#endif /* PRISM_UNIQUE_POINTER_H_ */
