#ifndef PRISM_JSON_PARSER_EXCEPTION_H_
#define PRISM_JSON_PARSER_EXCEPTION_H_

#include <prism/global>
#include <prism/Exception>
#include <prism/JsonSymbols>
#include <sstream>

class string;

PRISM_BEGIN_NAMESPACE

class JsonParserException : public Exception {
public:
    JsonParserException(const std::string& msg);
    JsonParserException(JsonSymbol symbol, const std::string& input);
};

JsonParserException::JsonParserException(const std::string& msg)
: Exception{msg}
{}

JsonParserException::JsonParserException(JsonSymbol symbol, const std::string& input)
: Exception{""}
{
    std::stringstream err;
    err << "Error: parse error - ";
    switch (symbol) {
        case JsonSymbol::NT_S:
            err << "expecting '{', ";
            break;
        case JsonSymbol::NT_T:
            err << "expecting 'String', '}', ";
            break;
        case JsonSymbol::NT_M:
            err << "expecting 'String', ";
            break;
        case JsonSymbol::NT_P:
            err << "expecting 'String', ";
            break;
        case JsonSymbol::NT_Q:
            err << "expecting ',', '}', ']', ";
            break;
        case JsonSymbol::NT_R:
            err << "expecting '[', ";
            break;
        case JsonSymbol::NT_E:
            err << "expecting '{', '[', ']', 'String', 'Number', 'Bool', 'Null', ";
            break;
        case JsonSymbol::NT_F:
            err << "expecting ']', ',', ";
            break;
        case JsonSymbol::NT_V:
            err << "expecting '{', '[', 'String', 'Number', 'Bool', 'Null', ";
            break;
        default:
            break;
    }
    err << "got '" << input << "'";
    this->msg = err.str();
}

PRISM_END_NAMESPACE

#endif
