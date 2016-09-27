/*
 * types.h
 * v1
 *
 *  Created on: Sep 5, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_UTILITIES_H_
#define PRISM_UTILITIES_H_

namespace prism {

/**
 * conditional_type is a struct that has a single member called type.
 * If condition is true then type's data type is set to Type1's data type.
 * If condition is false then type's data type is set to Type2's data type.
 *
 * prism::conditional_type<true, int, String>::type t; // type of t is int
 * prism::conditional_type<false, int, String>::type t; // type of t is String
 */
template <bool condition, class Type1, class Type2>
struct conditional_type { typedef Type1 type; };
template <class Type1, class Type2>
struct conditional_type<false, Type1, Type2> { typedef Type2 type; };

}



#endif /* PRISM_UTILITIES_H_ */
