#ifndef PRISM_JSONTOKEN_H_
#define PRISM_JSONTOKEN_H_

#include <prism/global>
#include <string>
#include <ostream>

PRISM_BEGIN_NAMESPACE

class JsonToken {
public:
    enum class LexemeType {
        COMMA,
        COLON,
        LEFT_BRACE,
        RIGHT_BRACE,
        LEFT_BRACKET,
        RIGHT_BRACKET,
        STRING,
        NUMBER,
        BOOL_LITERAL,
        NULL_LITERAL
    };
    LexemeType type;
    std::string val{};
public:
    JsonToken() = default;
    JsonToken(JsonToken::LexemeType type, const std::string val="");
};

JsonToken::JsonToken(JsonToken::LexemeType type, const std::string val)
    : type{type}, val{val}
{}

const bool
operator==(const JsonToken& lhs, const JsonToken& rhs) {
    return ((lhs.type == rhs.type) && (lhs.val == rhs.val));
}

std::ostream&
operator<<(std::ostream& out, const JsonToken& tk) {
    out << "JsonToken (type: " << tk.type << ", val: " << tk.val << ")";
    return out;
}

PRISM_END_NAMESPACE

#endif
