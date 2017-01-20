/*
 * LogAllocator.h
 * v1
 *
 *  Created on: Sep 18, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_LOGALLOCATOR_H_
#define PRISM_LOGALLOCATOR_H_

/*! This simple class extends the Allocator class by logging each memory allocation
 * and deallocation by storing the newly allocated pointer in a Vector on allocation
 * and removes it when the pointer is deallocated. In theory, at the end of the LoggerAllocator's
 * lifetime the Vector should be empty as all pointers should be deallocated. If there are
 * still pointers in the vector then an error message is printed to the console.
 */

#include <prism/h/Vector.h>
#include <utility>

namespace prism {

template <class T>
class LogAllocator {
public:
	Vector<T*> pointers;
public:
	typedef T 					value_type;
	typedef value_type*	 		pointer;
	typedef value_type&	 		reference;
	typedef const value_type *	const_pointer;
	typedef const value_type & 	const_reference;
	typedef size_t 				size_type;
	typedef std::ptrdiff_t 		difference_type;

	LogAllocator()
	{}

	LogAllocator(const LogAllocator<T>& copy)
	{}

	LogAllocator(const LogAllocator<T>&& copy)
	{}

	template <class U>
	LogAllocator(const LogAllocator<U>& copy)
	{

	}

	template <class U>
	LogAllocator(const LogAllocator<U>&& copy)
	{
		pointers = copy.pointers;
	}



	~LogAllocator(){
		if (pointers.size() != 0) {
			std::cerr << "---------------------------------------------------\n";
			std::cerr << "LogAllocator report: " << pointers.size() << " pointers not freed\n";
			std::cerr << "---------------------------------------------------\n";
			for (int i=0; i<pointers.size(); i++)
				std::cerr << "--- [" << i+1 << "] " << pointers.at(i) << "\n";
		}
		else {
//			std::cerr << "---------------------------------------------------\n"
//						 "LogAllocator report: all memory freed successfully!\n"
//						 "---------------------------------------------------" << std::endl;
		}
	}

	/* example usage (using an int allocator to create a String allocator):
	 * 	typedef typename Allocator<int>::template rebind<String>::other StringAllocator;
	 */
	template <class U>
	struct rebind { typedef LogAllocator<U> other; };

	/**
	 *
	 */
    struct propagate_on_container_copy_assignment
    : std::true_type
    {};

    /**
     *
     */
    struct propagate_on_container_move_assignment
    : std::true_type
    {};

    /**
     *
     */
    struct propagate_on_container_swap
    : std::true_type
    {};

    /**
     *
     */
    pointer
    address(const_reference value)
    { return &value; }

    /**
     *
     */
    const_pointer
    address(const_reference value) const
    { return &value; }

    /**
     *
     */
	pointer
	allocate(const size_type num, const_pointer p=0) {
		pointer ptr = static_cast<pointer>(::operator new(num * sizeof(T)));
		pointers.append(ptr);
		return ptr;
	}

	/**
	 *
	 */
	template <typename ...Args>
	void
	construct(T* p, Args&& ...args)
	{ ::new (static_cast<void*>(p)) T(std::forward<Args>(args)...); }

	/**
	 *
	 */
	void
	deallocate(pointer p, const size_type num=0) {
		if (pointers.contains(p))
			pointers.removeAll(p);

		::operator delete(p);
	}

	/**
	 *
	 */
	void
	destroy(pointer p)
	{ p->~T(); }

	/**
	 *
	 */
	size_type
	max_size() const
	{ return static_cast<size_type>(-1) / sizeof(value_type); }

	/**
	 *
	 */
	const int
	numAllocations() const
	{ return pointers.size(); }

	/**
	 *
	 */
	template <class T2>
	const bool
	operator==(const LogAllocator<T2>& rhs)
	{ return true; }

	/**
	 *
	 */
	template <class T2>
	const bool
	operator!=(const LogAllocator<T2>& rhs)
	{ return false; }

	/**
	 *
	 */
	void operator=(const LogAllocator<T>& rhs)
	{/* nothing to copy*/}

	/**
	 *
	 */
	void operator=(const LogAllocator<T>&& rhs)
	{/* nothing to move*/}

	/**
	 *
	 */
	template <class U>
	void operator=(const LogAllocator<U>& rhs)
	{/* nothing to assign */}

	/**
	 *
	 */
	template <class U>
	void operator=(const LogAllocator<U>&& rhs)
	{/* nothing to move */}

	/**
	 *
	 */
	LogAllocator select_on_container_copy_construction(const LogAllocator &a)
	{ return a; }
};

/**
 *
 */
template<class T>
bool
operator==(const LogAllocator<T> &a1, const LogAllocator<T> &a2)
{ return true; }

} // end namespace prism



#endif /* PRISM_LOGALLOCATOR_H_ */

