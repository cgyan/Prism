#ifndef PRISM_JSON_STRING_BUILDER_H_
#define PRISM_JSON_STRING_BUILDER_H_

#include <prism/global>
#include <prism/StringBuilder>
#include <prism/JsonValue>
#include <prism/JsonObject>
#include <prism/JsonArray>
#include <string>

PRISM_BEGIN_NAMESPACE

class JsonStringBuilder {
public:
    const bool empty() const;
    const int size() const;
    const std::string toString() const;

    void append(const double d);
    void append(const char * string);
    void append(const std::string& string);
    void append(const bool b);
    void append(const int i);
    void append(const JsonObject& object);
    void append(const JsonArray& array);
    void append(const JsonValue& value);
private:
    StringBuilder m_sb;
};

PRISM_END_NAMESPACE

#endif
