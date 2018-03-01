#include <prism/global>
#include <prism/JsonStringBuilder>

PRISM_BEGIN_NAMESPACE

class JsonStringBuilderImpl {
public:
    void appendArray(const JsonArray& array) {
        JsonArray::const_iterator citBegin = array.begin();
        JsonArray::const_iterator citEnd = array.end();
        m_ss << "[";
        std::string seperator = ",";
        for (; citBegin != citEnd; ++citBegin) {
            if (citBegin + 1 == citEnd) seperator = "";
            m_ss << *citBegin << seperator;
        }
        m_ss << "]";
    }

    void appendNull() {
        m_ss << "null";
    }

    void appendDouble(const double d) {
        m_ss << d;
    }

    void appendString(const std::string& s) {
        m_ss << "\"" << s << "\"";
    }

    void appendBool(const bool b) {
        if (b) m_ss << "true";
        else m_ss << "false";
    }

    void appendKeyAndSeperator(const std::string& key) {
        m_ss << "\"" << key << "\"";
        m_ss << ":";
    }

    void appendObjectMember(const std::string& key, const JsonValue& value) {
        m_ss << m_objectMemberSeperator;
        appendKeyAndSeperator(key);
        appendValue(value);
        m_objectMemberSeperator = ",";
    }

    void appendObject(const JsonObject& object) {
        m_ss << "{";
        m_objectMemberSeperator = "";
        for (auto keyValuePair : object) {
            std::string key = keyValuePair.first;
            JsonValue value = keyValuePair.second;
            appendObjectMember(key, value);
        }
        m_objectMemberSeperator = "";
        m_ss << "}";
    }

    void appendValue(const JsonValue& value) {
        if (value.isObject()) appendObject(value.toObject());
        else if (value.isArray()) appendArray(value.toArray());
        else if (value.isNull()) appendNull();
        else if (value.isDouble()) appendDouble(value.toDouble());
        else if (value.isString()) appendString(value.toString());
        else if (value.isBool()) appendBool(value.toBool());
    }

    const std::string toString() const {
        return m_ss.str();
    }
private:
    std::stringstream m_ss;
    std::string m_objectMemberSeperator{""};
};

JsonStringBuilder::JsonStringBuilder()
: m_impl{new JsonStringBuilderImpl}
{}

void
JsonStringBuilder::appendArray(const JsonArray& array) {
    m_impl->appendArray(array);
}

void
JsonStringBuilder::appendNull() {
    m_impl->appendNull();
}

void
JsonStringBuilder::appendDouble(const double d) {
    m_impl->appendDouble(d);
}

void
JsonStringBuilder::appendString(const std::string& s) {
    m_impl->appendString(s);
}

void
JsonStringBuilder::appendBool(const bool b) {
    m_impl->appendBool(b);
}

void
JsonStringBuilder::appendKeyAndSeperator(const std::string& key) {
    m_impl->appendKeyAndSeperator(key);
}

void
JsonStringBuilder::appendValue(const JsonValue& value) {
    m_impl->appendValue(value);
}

void
JsonStringBuilder::appendObjectMember(const std::string& key, const JsonValue& value) {
    m_impl->appendObjectMember(key, value);
}

void
JsonStringBuilder::appendObject(const JsonObject& object) {
    m_impl->appendObject(object);
}

const std::string
JsonStringBuilder::toString() const {
    return m_impl->toString();
}

PRISM_END_NAMESPACE
