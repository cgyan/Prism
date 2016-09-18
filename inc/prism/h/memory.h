/*
 * memory.h
 * v1
 *
 *  Created on: Sep 15, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_MEMORY_H_
#define PRISM_MEMORY_H_

#include <utility>

namespace prism {

/**
 *
 */
template <class T, typename ...Args>
void
construct(T* p, Args&&... args) {
	::new (static_cast<void*>(p)) T(std::forward<Args>(args)...);
}

/**
 *
 */
template <class T>
void
destroy(T* p) {
	p->~T();
}

} /* namespace prism */



#endif /* PRISM_MEMORY_H_ */
