#ifndef PRISM_OBJECT_H_
#define PRISM_OBJECT_H_

#include <prism/global>
#include <list>

PRISM_BEGIN_NAMESPACE

class Object {
public:
    using ObjectList = std::list<Object *>;
public:
                Object(Object * parent = nullptr);

    Object *    parent() const;
    void        setParent(Object * parent);
    ObjectList  children() const;
private:
    Object *    m_parent;
    ObjectList  m_children;
};

PRISM_END_NAMESPACE

#endif // PRISM_OBJECT_H_
