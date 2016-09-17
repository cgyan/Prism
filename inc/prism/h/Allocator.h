/*
 * Allocator.h
 * v1
 *
 *  Created on: Sep 15, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_ALLOCATOR_H_
#define PRISM_ALLOCATOR_H_

#include <utility> // for std::forward
#include <ostream>

namespace prism {

template <class Alloc>
struct AllocatorTraits {
	typedef Alloc							allocator_type;
	typedef typename Alloc::value_type 		value_type;
	typedef typename Alloc::pointer 		pointer;
	typedef typename Alloc::reference 		reference;
	typedef typename Alloc::const_pointer 	const_pointer;
	typedef typename Alloc::const_reference const_reference;
	typedef typename Alloc::size_type  		size_type;
	typedef typename Alloc::difference_type difference_type;

	static
	pointer
	allocate(Alloc& alloc, const size_type num) {
		return alloc.allocate(num);
	}

	static
	void
	deallocate(Alloc& alloc, pointer p) {
		alloc.deallocate(p);
	}

	static
	void
	destroy(Alloc& alloc, pointer p) {
		alloc.destroy(p);
	}

	template <typename ...Args>
	static
	void
	construct(Alloc& alloc, pointer p, Args&& ...args) {
		alloc.construct(p, args...);
	}
};

template <class T>
class Allocator {
public:
	typedef T 			value_type;
	typedef T* 			pointer;
	typedef T& 			reference;
	typedef const T* 	const_pointer;
	typedef const T& 	const_reference;
	typedef size_t 		size_type;
	typedef ptrdiff_t 	difference_type;

	template <class U>
	struct rebind { typedef Allocator<U> other; };
	/* example usage (using an int allocator to create a String allocator):
	 * 	typedef typename Allocator<int>::template rebind<String>::other StringAllocator;
	 */

	/*
	 *
	 */
	Allocator()
	{/* nothing to initialize */}

	/**
	 *
	 */
	Allocator(const Allocator<T>& copy)
	{/* nothing to copy */}

	/**
	 *
	 */
	template <class U>
	Allocator(const Allocator<U>& copy)
	{/* nothing to copy */}

	/**
	 *
	 */
	virtual ~Allocator()
	{/* nothing to destruct */}

	/**
	 *
	 */
	pointer
	address(const_reference value) {
		return &value;
	}

	/**
	 *
	 */
	const_pointer
	address(const_reference value) const {
		return &value;
	}

	/**
	 *
	 */
	pointer
	allocate(const size_type num, const_pointer p=0) {
		pointer ptr = static_cast<pointer>(::operator new(num * sizeof(T)));
		std::cout << "Allocator: allocating " << num << "*sizeof(T) [" << ptr << "]" << std::endl;
		return ptr;
	}

	/**
	 *
	 */
	template <typename ...Args>
	void
	construct(pointer p, Args&& ...args) {
		::new (static_cast<void*>(p)) T(std::forward<Args>(args)...);
	}

	/**
	 *
	 */
	void
	deallocate(pointer p, const size_type num=0) {
		std::cout << "Allocator: deallocating p [" << p << "]" << std::endl;
		::operator delete(p);
	}

	/**
	 *
	 */
	void
	destroy(pointer p) {
		p->~T();
	}

	/**
	 *
	 */
	size_type
	max_size() const {
		return static_cast<size_type>(-1) / sizeof(value_type);
	}

	/**
	 *
	 */
	template <class T2>
	const bool
	operator==(const Allocator<T2>& rhs) {
		return true;
	}

	/**
	 *
	 */
	template <class T2>
	const bool
	operator!=(const Allocator<T2>& rhs) {
		return false;
	}

private:
	void operator=(const Allocator<T>& rhs)
	{/* don't allow assignment*/}
};

} /* namespace prism */

#endif /* PRISM_ALLOCATOR_H_ */
