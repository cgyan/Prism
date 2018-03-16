#ifndef PRISM_JSON_OBJECT_H_
#define PRISM_JSON_OBJECT_H_

#include <prism/global>
#include <prism/JsonValue>
#include <prism/JsonObjectIterator>
#include <prism/Vector>
#include <prism/Pair>
#include <memory>
#include <ostream>

PRISM_BEGIN_NAMESPACE

class AbstractJsonObjectImpl;

class JsonObject {
public:
    using iterator = prism::JsonObjectIterator<false>;
    using const_iterator = prism::JsonObjectIterator<true>;
public:
    JsonObject();
    JsonObject(std::initializer_list<prism::Pair<std::string, JsonValue>> il);
    JsonObject(const JsonObject& copy);
    JsonObject(AbstractJsonObjectImpl * impl);
    JsonObject& operator=(const JsonObject& rhs);

    const int size() const;
    const bool empty() const;
    const bool contains(const std::string& key) const;
    prism::Vector<std::string> keys() const;
    void insert(const std::string& key, const JsonValue& value);
    void remove(const std::string& key);
    void erase(JsonObject::iterator it);
    iterator find(const std::string& key);

    iterator begin();
    const_iterator begin() const;
    const_iterator cbegin() const;
    iterator end();
    const_iterator end() const;
    const_iterator cend() const;

    JsonValue& operator[](const std::string& key);
    const bool operator==(const JsonObject& rhs) const;
    // const bool operator!=(const JsonObject& rhs);
private:
    std::shared_ptr<AbstractJsonObjectImpl> m_impl;
};

std::ostream& operator<<(std::ostream& out, const JsonObject& jo);

PRISM_END_NAMESPACE

#endif
