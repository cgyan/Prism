#include <prism/global>
#include <prism/algorithm>

PRISM_BEGIN_NAMESPACE

template <typename T, typename Container>
Stack<T, Container>::Stack(const Vector<T>& vector) {
    for (auto val : vector) {
        this->push(val);
    }
}

template <typename T, typename Container>
Stack<T, Container>::Stack(const Stack<T, Container>& rhs)
: m_storage{rhs.m_storage}
{}

template <typename T, typename Container>
Stack<T, Container>::Stack(Stack<T, Container>&& rhs) {
    this->swap(rhs);
}

template <typename T, typename Container>
Stack<T, Container>&
Stack<T, Container>::operator=(const Stack<T, Container>& rhs) {
    if (*this != rhs)
        m_storage = rhs.m_storage;
    return *this;
}

template <typename T, typename Container>
Stack<T, Container>&
Stack<T, Container>::operator=(Stack<T, Container>&& rhs) {
    m_storage = std::move(rhs.m_storage);
    return *this;
}

template <typename T, typename Container>
Stack<T, Container>::~Stack()
{}

template <typename T, typename Container>
Stack<T, Container>
Stack<T, Container>::fromVector(const Vector<T>& vector) {
    return Stack<T, Container>(vector);
}

template <typename T, typename Container>
const bool
Stack<T, Container>::empty() const {
    return m_storage.empty();
}

template <typename T, typename Container>
const int
Stack<T, Container>::size() const {
    return m_storage.size();
}

template <typename T, typename Container>
void
Stack<T, Container>::push(const T& value) {
    m_storage.append(value);
}

template <typename T, typename Container>
void
Stack<T, Container>::pop() {
    m_storage.removeLast();
}

template <typename T, typename Container>
T&
Stack<T, Container>::top() {
    return m_storage.back();
}

template <typename T, typename Container>
const T&
Stack<T, Container>::top() const {
    return m_storage.back();
}

template <typename T, typename Container>
void
Stack<T, Container>::clear() {
    m_storage.clear();
}

template <typename T, typename Container>
void
Stack<T, Container>::swap(Stack<T, Container>& other) {
    prism::swap(this->m_storage, other.m_storage);
}

template <typename T, typename Container>
Stack<T, Container>&
Stack<T, Container>::operator<<(const T& value) {
    push(value);
    return *this;
}

template <typename T, typename Container>
Stack<T, Container>&
Stack<T, Container>::operator+=(const T& value) {
    push(value);
    return *this;
}

template <typename U>
const bool
operator==(const Stack<U>& lhs, const Stack<U>& rhs) {
    return lhs.m_storage == rhs.m_storage;
}

template <typename U>
const bool
operator!=(const Stack<U>& lhs, const Stack<U>& rhs) {
    return !(lhs == rhs);
}

template <typename T, typename Container>
void
swap(Stack<T, Container>& a, Stack<T, Container>& b) {
    a.swap(b);
}

PRISM_END_NAMESPACE
