#ifndef PRISM_ABSTRACT_JSON_OBJECT_IMPL_H_
#define PRISM_ABSTRACT_JSON_OBJECT_IMPL_H_

#include <prism/global>
#include <prism/Vector>
#include <string>
#include <prism/JsonObject>

PRISM_BEGIN_NAMESPACE

class AbstractJsonObjectImpl {
public:
    virtual ~AbstractJsonObjectImpl() {}

    virtual AbstractJsonObjectImpl* clone() const = 0;
    virtual const int numMembers() const { return int{}; }
    virtual void insertNewMember(const std::string& key, const JsonValue& value) = 0;
    virtual void removeMember(const std::string& key) {}
    virtual prism::Vector<std::string> keys() const { return prism::Vector<std::string>{}; }
    virtual const bool containsKey(const std::string& key) { return bool{}; }
    virtual JsonObject::iterator findMember(const std::string& key) { return JsonObject::iterator{}; }
    virtual JsonObject::iterator begin() { return JsonObject::iterator{}; }
    virtual JsonObject::iterator end() { return JsonObject::iterator{}; }
    virtual const bool equals(AbstractJsonObjectImpl * rhs) const = 0;
};

PRISM_END_NAMESPACE

#endif
