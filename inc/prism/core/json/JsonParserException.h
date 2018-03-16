#ifndef PRISM_JSON_PARSER_EXCEPTION_H_
#define PRISM_JSON_PARSER_EXCEPTION_H_

#include <prism/global>
#include <prism/Exception>
#include <prism/JsonSymbols>

class string;

PRISM_BEGIN_NAMESPACE

class JsonParserException : public Exception {
public:
    JsonParserException(const std::string& msg);
    JsonParserException(JsonSymbol symbol, const std::string& input);
};

PRISM_END_NAMESPACE

#endif
