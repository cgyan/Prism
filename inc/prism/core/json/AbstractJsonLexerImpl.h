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
    virtual JsonToken getNextToken() = 0;
    virtual const bool stringIsStillBeingProcessed() const = 0;
};

PRISM_END_NAMESPACE

#endif
