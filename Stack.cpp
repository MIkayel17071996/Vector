#include <iostream>
#include "Stack.h"
#include "Vector.h"

template <typename T>
Stack<T>::~Stack()
{
    m_vector.clear();
}

template <typename T>
Stack<T>::Stack()
    : m_vector()
{
}

template <typename T>
Stack<T>::Stack(std::size_t value)
    : m_vector(value)
{
}

template <typename T>
Stack<T>::Stack(std::size_t count, const T &value)
    : m_vector(count, value)
{
}

template <typename T>
Stack<T>::Stack(const Stack &other)
    : m_vector(other.m_vector)
{
}

template <typename T>
Stack<T>::Stack(Stack &&other) noexcept
    : m_vector(std::move(other.m_vector))
{
}

template <typename T>
Stack<T> &Stack<T>::operator=(const Stack &rhv)
{
    if (this != &rhv)
    {
        m_vector = rhv.m_vector;
    }
    return *this;
}

template <typename T>
Stack<T> &Stack<T>::operator=(Stack &&rhv)
{
    if (this != &rhv)
    {
        m_vector = std::move(rhv.m_vector);
    }
    return *this;
}

template <typename T>
T &Stack<T>::top()
{
    if (empty())
    {
        throw std::logic_error("THE STACK IS EMPTY");
    }

    return m_vector.back();
}

template <typename T>
const T &Stack<T>::top() const
{
    if (empty())
    {
        throw std::logic_error("THE STACK IS EMPTY");
    }

    return m_vector.back();
}

template <typename T>
bool Stack<T>::empty() const noexcept
{
    return m_vector.empty();
}

template <typename T>
std::size_t Stack<T>::size() const noexcept
{
    return m_vector.size();
}

template <typename T>
void Stack<T>::push(const T &value)
{
    m_vector.push_back(value);
}

template <typename T>
void Stack<T>::push(T &&value)
{
    m_vector.push_back(value);
}

template <typename T>
void Stack<T>::pop()
{
    m_vector.pop_back();
}

template <typename T>
void Stack<T>::swap(Stack &other)
{
    m_vector.swap(other.m_vector);
}
