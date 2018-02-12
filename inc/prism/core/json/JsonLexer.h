#ifndef PRISM_JSON_LEXER_H_
#define PRISM_JSON_LEXER_H_

#include <prism/global>
#include <prism/JsonToken>
#include <prism/Exception>
#include <string>
#include <queue>

PRISM_BEGIN_NAMESPACE
//==============================================================================
// JsonLexerException
//==============================================================================
class JsonLexerException : public Exception {
public:
    JsonLexerException(const std::string& errMsg)
    : Exception{errMsg}
    {}
};
//==============================================================================
// JsonLexer
//==============================================================================
class JsonLexer {
public:
    JsonLexer() = delete;
    JsonLexer(const std::string& input);
    virtual ~JsonLexer();
    virtual const bool hasNext() const;
    virtual JsonToken next();
private:
    void tokenize(const std::string& input);
    void addToken(JsonToken::Type type, const std::string& val="");
private:
    std::queue<JsonToken> tokens;
};

PRISM_END_NAMESPACE

#endif
