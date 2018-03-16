#include <prism/global>
#include <prism/Exception>
#include <string>

PRISM_BEGIN_NAMESPACE

class InvalidConversionException : public Exception {
public:
    InvalidConversionException() = delete;
    InvalidConversionException(const std::string& msg);
};

PRISM_END_NAMESPACE
