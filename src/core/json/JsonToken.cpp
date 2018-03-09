#include <prism/global>
#include <prism/JsonToken>
#include <ostream>

PRISM_BEGIN_NAMESPACE

JsonToken::JsonToken(JsonToken::Type type, const std::string value)
    : type{type}, value{value}
{}

const bool
operator==(const JsonToken& lhs, const JsonToken& rhs) {
    return ((lhs.type == rhs.type) && (lhs.value == rhs.value));
}

std::ostream&
operator<<(std::ostream& out, const JsonToken& token) {
    // out << "JsonToken (type: " << token.type << ", value: " << token.value << ")";
    return out;
}

PRISM_END_NAMESPACE
