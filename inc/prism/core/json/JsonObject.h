#ifndef PRISM_JSONOBJECT_H_
#define PRISM_JSONOBJECT_H_

#include <prism/global>
#include <memory>
#include <list>
#include <map>
#include <ostream>

PRISM_BEGIN_NAMESPACE

class JsonValue;

class JsonObject {
public:
    using iterator = std::map<std::string, JsonValue>::iterator;
    using const_iterator = std::map<std::string, JsonValue>::const_iterator;
public:
    JsonObject();
    JsonObject(std::initializer_list<std::pair<std::string, JsonValue>> il);

    const int size() const;
    const bool empty() const;
    const bool contains(const std::string& key) const;
    JsonValue& operator[](const std::string& key);
    std::list<std::string> keys() const;
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

    const bool operator==(const JsonObject& rhs);
    // const bool operator!=(const JsonObject& rhs);
private:
    class JsonObjectData;
    std::shared_ptr<JsonObjectData> m_data;
};

std::ostream& operator<<(std::ostream& out, const JsonObject& jo);

PRISM_END_NAMESPACE

#endif
