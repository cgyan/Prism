#ifndef PRISM_JSONLEXER_H_
#define PRISM_JSONLEXER_H_

#include <prism/global>
#include <prism/JsonToken>
#include <string>
#include <queue>

PRISM_BEGIN_NAMESPACE
//==============================================================================
// JsonLexer
//==============================================================================
class JsonLexer {
public:
    JsonLexer() = default;
    JsonLexer(const std::string& input);
    const bool hasNext() const;
    JsonToken next();
private:
    void tokenize(const std::string& input);
    void addToken(JsonToken::LexemeType type, const std::string& val="");
private:
    std::queue<JsonToken> tokens;
};

PRISM_END_NAMESPACE

#endif
