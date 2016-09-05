/*
 * types.h
 * v1
 *
 *  Created on: Sep 5, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_TYPES_H_
#define PRISM_TYPES_H_

namespace prism {

/**
 * conditional is a struct that has a single member called type.
 * If Condition is true then type's data type is set to Type1's data type.
 * If Condition is false then type's data type is set to Type2's data type.
 *
 * prism::conditional<true, int, String>::type t; // type of t is int
 * prism::conditional<false, int, String>::type t; // type of t is String
 */
template <bool Condition, class Type1, class Type2>
struct conditional { typedef Type1 type; };
template <class Type1, class Type2>
struct conditional<false, Type1, Type2> { typedef Type2 type; };

}



#endif /* PRISM_TYPES_H_ */
