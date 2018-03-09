#ifndef PRISM_STACK_H_
#define PRISM_STACK_H_

#include <prism/global>
#include <prism/Vector>

PRISM_BEGIN_NAMESPACE

template <typename T, typename Container = prism::Vector<T>>
class Stack {
public:
    Stack() = default;
    Stack(const Vector<T>& vector);
    Stack(const Stack<T, Container>& rhs);
    Stack(Stack<T, Container>&& rhs);
    Stack<T, Container>& operator=(const Stack<T, Container>& rhs);
    Stack<T, Container>& operator=(Stack<T, Container>&& rhs);

    static Stack<T, Container> fromVector(const Vector<T>& vector);

    const bool empty() const;
    const int size() const;
    void push(const T& value);
    void pop();
    T& top();
    const T& top() const;
    void clear();
    void swap(Stack<T, Container>& other);

    template <typename U>
    friend const bool operator==(const Stack<U>& lhs, const Stack<U>& rhs);
    template <typename U>
    friend const bool operator!=(const Stack<U>& lhs, const Stack<U>& rhs);
private:
    Container m_storage;
};

template <typename T, typename Container>
void swap(Stack<T, Container>& a, Stack<T, Container>& b);

PRISM_END_NAMESPACE

#include <prism/core/priv/Stack_priv.h>

#endif
