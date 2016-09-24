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

#include <prism/Allocator>
#include <prism/Vector>

namespace prism {

template <class T>
class LogAllocator : public Allocator<T> {
public:
	Vector<T*> pointers;
public:
	typedef Allocator<T>						Alloc;
	typedef typename Alloc::value_type 			value_type;
	typedef typename Alloc::pointer 			pointer;
	typedef typename Alloc::reference 			reference;
	typedef typename Alloc::const_pointer 		const_pointer;
	typedef typename Alloc::const_reference 	const_reference;
	typedef typename Alloc::size_type 			size_type;
	typedef typename Alloc::difference_type 	difference_type;

	LogAllocator()
	: Allocator<T>()
	{}

	LogAllocator(const LogAllocator<T>& copy)
	: Allocator<T>(copy)
	{}

	LogAllocator(const LogAllocator<T>&& copy)
	: LogAllocator(copy)
	{}

	template <class U>
	LogAllocator(const LogAllocator<U>& copy)
	: Allocator<U>(copy)
	{}

	template <class U>
	LogAllocator(const LogAllocator<U>&& copy)
	: Allocator<U>(copy)
	{}



	~LogAllocator(){
		if (pointers.size() != 0) {
			std::cerr << "---------------------------------------------------\n";
			std::cerr << "LogAllocator report: " << pointers.size() << " pointers not freed\n";
			std::cerr << "---------------------------------------------------\n";
			for (int i=0; i<pointers.size(); i++)
				std::cerr << "--- [" << i+1 << "] " << pointers.at(i) << "\n";
		}
		else
			std::cerr << "---------------------------------------------------\n"
						 "LogAllocator report: all memory freed successfully!\n"
						 "---------------------------------------------------" << std::endl;
	}

	template <class U>
	struct rebind { typedef LogAllocator<U> other; };
	/* example usage (using an int allocator to create a String allocator):
	 * 	typedef typename Allocator<int>::template rebind<String>::other StringAllocator;
	 */

	pointer
	allocate(const size_type num, const_pointer p=0) {
		pointer ptr = Alloc::allocate(num, p);
		pointers.append(ptr);
		return ptr;
	}

	void
	deallocate(pointer p, const size_type num=0) {
		if (pointers.contains(p))
			pointers.removeAll(p);

		Alloc::deallocate(p, num);
	}

	const int numAllocations() const
	{ return pointers.size(); }
};

} // end namespace prism



#endif /* PRISM_LOGALLOCATOR_H_ */
