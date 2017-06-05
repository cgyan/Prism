#ifndef PRISM_OBJECT_H_
#define PRISM_OBJECT_H_

#include <prism/global>
#include <list>
#include <memory>

PRISM_BEGIN_NAMESPACE

class ObjectImpl;

class Object {
private:
    using ObjectImplPtr = std::shared_ptr<ObjectImpl>;
public:
    using ObjectList = std::list<Object *>;
public:
    Object(Object * parent = nullptr);
    ~Object();

    Object * parent() const;
    void setParent(Object * parent);
    const ObjectList& children() const;
private:
    ObjectImplPtr impl;
};

PRISM_END_NAMESPACE

#endif // PRISM_OBJECT_H_
