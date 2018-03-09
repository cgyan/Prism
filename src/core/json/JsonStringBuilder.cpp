#include <prism/global>
#include <prism/JsonStringBuilder>
#include <iterator>

PRISM_BEGIN_NAMESPACE

const bool
JsonStringBuilder::empty() const {
    return m_sb.empty();
}

const int
JsonStringBuilder::size() const {
    return m_sb.size();
}

const std::string
JsonStringBuilder::toString() const {
    return m_sb.toString();
}

void
JsonStringBuilder::append(const double d) {
    m_sb.append(d);
}

void
JsonStringBuilder::append(const char * string) {
    m_sb.append('"');
    m_sb.append(string);
    m_sb.append('"');
}

void
JsonStringBuilder::append(const std::string& string) {
    m_sb.append('"');
    m_sb.append(string);
    m_sb.append('"');
}

void
JsonStringBuilder::append(const bool b) {
    m_sb.append(b);
}

void
JsonStringBuilder::append(const int i) {
    m_sb.append(i);
}

void
JsonStringBuilder::append(const JsonObject& object) {
    m_sb.append('{');
    std::string memberSeperator = ",";
    for (auto it = object.begin(); it != object.end(); ++it) {
        if (std::next(it) == object.end()) {
            std::prev(it);
            memberSeperator = "";
        }
        std::string key = (*it).first;
        JsonValue value = (*it).second;
        append(key);
        m_sb.append(':');
        append(value);
        m_sb.append(memberSeperator);
    }
    m_sb.append('}');
}

void
JsonStringBuilder::append(const JsonArray& array) {
    m_sb.append('[');
    std::string elementSeperator = ",";
    for (auto it = array.begin(); it != array.end(); ++it) {
        if (it + 1 == array.end()) elementSeperator = "";
        JsonValue value = *it;
        append(value);
        m_sb.append(elementSeperator);
    }
    m_sb.append(']');
}

void
JsonStringBuilder::append(const JsonValue& value) {
    if (value.isDouble()) m_sb.append(value.toDouble());
    else if (value.isString()) append(value.toString());
    else if (value.isBool()) (value.toBool()) ? m_sb.append(true) : m_sb.append(false);
    else if (value.isNull()) m_sb.append("null");
    else if (value.isObject()) append(value.toObject());
    else if (value.isArray()) append(value.toArray());
}

PRISM_END_NAMESPACE
