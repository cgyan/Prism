#ifndef PRISM_JSON_LEXER_H_
#define PRISM_JSON_LEXER_H_

#include <prism/global>
#include <memory>

PRISM_BEGIN_NAMESPACE

class AbstractJsonLexerImpl;
class JsonToken;

class JsonLexer {
private:
    JsonLexer() = delete;
public:
    JsonLexer(const std::string& input);

    const bool hasMoreTokens() const;
    JsonToken getNextToken();
private:
    std::shared_ptr<AbstractJsonLexerImpl> m_impl;
};

PRISM_END_NAMESPACE

#endif
