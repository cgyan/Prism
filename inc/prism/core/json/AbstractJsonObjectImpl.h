#ifndef PRISM_ABSTRACT_JSON_OBJECT_IMPL_H_
#define PRISM_ABSTRACT_JSON_OBJECT_IMPL_H_

#include <prism/global>
#include <string>
#include <list>
#include <prism/JsonObject>

PRISM_BEGIN_NAMESPACE

class AbstractJsonObjectImpl {
public:
    virtual ~AbstractJsonObjectImpl() {}

    virtual const int numMembers() const { return int{}; }
    virtual void insertNewMember(const std::string& key, const JsonValue& value) {}
    virtual void removeMember(const std::string& key) {}
    virtual std::list<std::string> keys() const { return std::list<std::string>{}; }
    virtual const bool containsKey(const std::string& key) { return bool{}; }
    virtual JsonObject::iterator findMember(const std::string& key) { return JsonObject::iterator{}; }
    virtual JsonObject::iterator begin() { return JsonObject::iterator{}; }
    virtual JsonObject::iterator end() { return JsonObject::iterator{}; }
    virtual const bool operator==(AbstractJsonObjectImpl * rhs) { return bool{}; }
};

PRISM_END_NAMESPACE

#endif
