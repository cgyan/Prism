#include <prism/global>
#include <prism/Exception>

PRISM_BEGIN_NAMESPACE

class InvalidConversionException : public Exception {
public:
    InvalidConversionException() = delete;
    InvalidConversionException(const std::string& msg);
};

InvalidConversionException::InvalidConversionException(const std::string& msg)
    : Exception{msg}
{}

PRISM_END_NAMESPACE
