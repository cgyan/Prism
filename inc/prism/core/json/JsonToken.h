#ifndef PRISM_JSON_TOKEN_H_
#define PRISM_JSON_TOKEN_H_

#include <prism/global>
#include <string>

PRISM_BEGIN_NAMESPACE

class JsonToken {
public:
    enum class Type {
        Comma,
        Colon,
        LeftBrace,
        RightBrace,
        LeftBracket,
        RightBracket,
        String,
        Number,
        BoolLiteral,
        NullLiteral
    };
    Type type;
    std::string val{};
public:
    JsonToken() = default;
    JsonToken(JsonToken::Type type, const std::string val="");
};

const bool operator==(const JsonToken& lhs, const JsonToken& rhs);

PRISM_END_NAMESPACE

#endif
