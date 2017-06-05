#include <prism/Object>
#include <cassert>

PRISM_BEGIN_NAMESPACE

// ============================================================================================
// ObjectImpl
// ============================================================================================
class ObjectImpl {
public:
    Object * m_parent;
    Object::ObjectList m_children;
public:
    void setParent(Object * parent);
    void addChild(Object * child);
};

void
ObjectImpl::setParent(Object * parent) {
    m_parent = parent;
}

void
ObjectImpl::addChild(Object * child) {
    m_children.push_back(child);
}
// ============================================================================================
// Object
// ============================================================================================
Object::Object(Object * parent)
:   impl{new ObjectImpl}
{
    setParent(parent);
}

Object::~Object() {
    //
}

Object *
Object::parent() const {
    return impl->m_parent;
}

void
Object::setParent(Object * parent) {
    impl->setParent(parent);
    if (parent) parent->impl->addChild(this);
}

const Object::ObjectList &
Object::children() const {
    return impl->m_children;
}

PRISM_END_NAMESPACE
