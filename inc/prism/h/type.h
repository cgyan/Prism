/*
 * type.h
 * v1
 *
 *  Created on: Oct 29, 2016
 *      Author: iainhemstock
 */

#ifndef PRISM_TYPE_H_
#define PRISM_TYPE_H_

namespace prism {

template <typename T>
class FundamentalType {
public:
	enum { Yes = 0, NO = 1 };
};

#define PRISM_FUNDAMENTAL_TYPE(T) 	\
template <> 						\
class FundamentalType<T> { 			\
public:								\
	enum { YES = 1, NO = 0 }; 		\
};

// list taken from: http://en.cppreference.com/w/cpp/language/types
PRISM_FUNDAMENTAL_TYPE(bool)
PRISM_FUNDAMENTAL_TYPE(char)
PRISM_FUNDAMENTAL_TYPE(signed char)
PRISM_FUNDAMENTAL_TYPE(unsigned char)
PRISM_FUNDAMENTAL_TYPE(short)
PRISM_FUNDAMENTAL_TYPE(unsigned short)
PRISM_FUNDAMENTAL_TYPE(int)
PRISM_FUNDAMENTAL_TYPE(unsigned)
PRISM_FUNDAMENTAL_TYPE(long)
PRISM_FUNDAMENTAL_TYPE(unsigned long)
PRISM_FUNDAMENTAL_TYPE(long long)
PRISM_FUNDAMENTAL_TYPE(unsigned long long)
PRISM_FUNDAMENTAL_TYPE(float)
PRISM_FUNDAMENTAL_TYPE(double)
PRISM_FUNDAMENTAL_TYPE(long double)

#undef PRISM_FUNDAMENTAL_TYPE

} // end namespace prism



#endif /* PRISM_TYPE_H_ */

