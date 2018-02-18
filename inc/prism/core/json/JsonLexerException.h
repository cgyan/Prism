#ifndef PRISM_JSON_LEXER_EXCEPTION_H_
#define PRISM_JSON_LEXER_EXCEPTION_H_

#include <prism/global>
#include <prism/Exception>

PRISM_BEGIN_NAMESPACE

class JsonLexerException : public Exception {
public:
    JsonLexerException(const std::string& errMsg)
    : Exception{errMsg}
    {}
};

PRISM_END_NAMESPACE

#endif
