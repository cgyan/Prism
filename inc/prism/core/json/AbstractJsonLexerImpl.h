#ifndef PRISM_ABSTRACT_JSON_LEXER_IMPL_H_
#define PRISM_ABSTRACT_JSON_LEXER_IMPL_H_

#include <prism/global>
#include <prism/JsonToken>
#include <queue>

PRISM_BEGIN_NAMESPACE

class JsonToken;

class AbstractJsonLexerImpl {
public:
    virtual ~AbstractJsonLexerImpl() {}
    virtual std::queue<JsonToken>& tokens() = 0;
    virtual void addToken(JsonToken::Type type, const std::string& val="") = 0;
    virtual void tokenize(const std::string& input) = 0;
};

PRISM_END_NAMESPACE

#endif
