#ifndef PRISM_JSON_DOC_H_
#define PRISM_JSON_DOC_H_

#include <prism/global>
#include <string>

PRISM_BEGIN_NAMESPACE

class JsonObject;

class JsonDoc {
public:
    JsonDoc() = default;
    JsonDoc(const JsonObject& obj);
    JsonDoc(const std::string& json);
    JsonDoc(const JsonDoc& copy);

    const bool isValid() const;
    const std::string toJson() const;
    void swap(JsonDoc& other);
    const int numKeys() const;

    static JsonDoc fromJson(const std::string& json);
    static JsonDoc fromObject(const JsonObject& obj);
private:
    void parse(const std::string& json);
private:
    bool m_valid{true};
    std::string m_json{"{}"};
};

const bool operator==(const JsonDoc& lhs, const JsonDoc& rhs);

PRISM_END_NAMESPACE

#endif
