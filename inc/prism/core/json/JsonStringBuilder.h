#ifndef PRISM_JSON_STRING_BUILDER_H_
#define PRISM_JSON_STRING_BUILDER_H_

#include <prism/global>
#include <prism/JsonValue>
#include <prism/JsonObject>
#include <prism/JsonArray>
#include <string>
#include <sstream>
#include <memory>

PRISM_BEGIN_NAMESPACE

class JsonStringBuilderImpl;

class JsonStringBuilder {
public:
    JsonStringBuilder();

    void appendArray(const JsonArray& array);
    void appendNull();
    void appendDouble(const double d);
    void appendString(const std::string& s);
    void appendBool(const bool b);
    void appendKeyAndSeperator(const std::string& key);
    void appendValue(const JsonValue& value);
    void appendObjectMember(const std::string& key, const JsonValue& value);
    void appendObject(const JsonObject& object);
    const std::string toString() const;
private:
    std::shared_ptr<JsonStringBuilderImpl> m_impl;
};

PRISM_END_NAMESPACE

#endif
