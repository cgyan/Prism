#ifndef PRISM_DIVIDE_BY_ZERO_EXCEPTION_H_
#define PRISM_DIVIDE_BY_ZERO_EXCEPTION_H_

#include <prism/global>
#include <prism/Exception>

PRISM_BEGIN_NAMESPACE

class DivideByZeroException : public Exception {
public:
    DivideByZeroException()
    : Exception{"Attempt to divide by zero threw exception"}
    {}
};

PRISM_END_NAMESPACE

#endif // PRISM_DIVIDE_BY_ZERO_EXCEPTION_H_
