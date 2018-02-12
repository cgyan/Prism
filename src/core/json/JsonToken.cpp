#include <prism/global>
#include <prism/JsonToken>
#include <ostream>

PRISM_BEGIN_NAMESPACE

JsonToken::JsonToken(JsonToken::Type type, const std::string val)
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
