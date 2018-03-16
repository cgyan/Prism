#include <prism/global>
#include <prism/InvalidConversionException>

PRISM_BEGIN_NAMESPACE

InvalidConversionException::InvalidConversionException(const std::string& msg)
    : Exception{msg}
{}

PRISM_END_NAMESPACE
