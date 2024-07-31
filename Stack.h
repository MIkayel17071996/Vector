
#ifndef STACK_H
#define STACK_H
#include "Vector.h"
#include <iostream>

template <typename T>
class Stack
{
public:
    Stack();
    ~Stack();
    Stack(std::size_t);
    Stack(std::size_t, const T &);
    Stack(const Stack &);
    Stack(Stack &&) noexcept;

    Stack &operator=(const Stack &);
    Stack &operator=(Stack &&);

public:
    T &top();
    const T &top() const;
    bool empty() const noexcept;
    std::size_t size() const noexcept;
    void push(const T &);
    void push(T &&);
    void pop();
    void swap(Stack &);

private:
    Vector<T> m_vector;

public:
    template <typename U>
    friend bool operator==(const Stack<T> &lhs, const Stack<U> &rhs)
    {
        return lhs.m_vector == rhs.m_vector;
    }

    template <typename U>
    friend bool operator!=(const Stack<T> &lhs, const Stack<U> &rhs)
    {
        return !(lhs == rhs);
    }

    template <typename U>
    friend bool operator<(const Stack<T> &lhs, const Stack<U> &rhs)
    {
        return lhs.m_vector < rhs.m_vector;
    }

    template <typename U>
    friend bool operator<=(const Stack<T> &lhs, const Stack<U> &rhs)
    {
        return !(rhs < lhs);
    }

    template <typename U>
    friend bool operator>(const Stack<T> &lhs, const Stack<U> &rhs)
    {
        return rhs < lhs;
    }

    template <typename U>
    friend bool operator>=(const Stack<T> &lhs, const Stack<U> &rhs)
    {
        return !(lhs < rhs);
    }
};

#include "Stack.cpp"

#endif // STACK_H
