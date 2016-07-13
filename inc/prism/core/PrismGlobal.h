/*
 * global.h
 * v0.1
 *
 *  Created on: Jun 27, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_GLOBAL_H_
#define PRISM_GLOBAL_H_

namespace prism {

template <typename T>
const T& max(const T &a, const T &b) { return (a<b) ? b : a; }
template <typename T>
const T& min(const T &a, const T &b) { return (a<b) ? a : b; }

}



#endif /* PRISM_GLOBAL_H_ */
