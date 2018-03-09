#ifndef PRISM_JSON_DOC_H_
#define PRISM_JSON_DOC_H_

#include <prism/global>
#include <prism/JsonObject>
#include <string>
#include <memory>

PRISM_BEGIN_NAMESPACE

class JsonDocImpl;

class JsonDoc {
public:
    JsonDoc();
    JsonDoc(const std::string& json);
    JsonDoc(const JsonObject& object);
    JsonDoc(const JsonDoc& copy);
    JsonDoc(JsonDoc&& rhs);
    JsonDoc& operator=(const JsonDoc& rhs);
    JsonDoc& operator=(JsonDoc&& rhs);
    ~JsonDoc();

    const bool valid() const;
    const bool empty() const;
    const std::string toJson() const;
    void swap(JsonDoc& other);
    void clear();
    JsonObject object() const;
    const std::string errorMessage() const;
private:
    friend const bool operator==(const JsonDoc& lhs, const JsonDoc& rhs);
    friend const bool operator!=(const JsonDoc& lhs, const JsonDoc& rhs);
private:
    std::shared_ptr<JsonDocImpl> m_impl;
};

PRISM_END_NAMESPACE

#endif
