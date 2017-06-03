#include <prism/Object>

PRISM_BEGIN_NAMESPACE

Object::Object(Object * parent)
:   m_parent{nullptr}
{
    if (parent) setParent(parent);
}

Object *
Object::parent() const {
    return m_parent;
}

void
Object::setParent(Object * parent) {
    m_parent = parent;
    parent->m_children.push_back(this);
}

Object::ObjectList
Object::children() const {
    return m_children;
}

PRISM_END_NAMESPACE
