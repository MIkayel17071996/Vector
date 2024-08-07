#include <iostream>
#include <list>
#include "Queue.h"

template <typename T>
Queue<T>::~Queue()
{
    m_list.clear();
}

template <typename T>
Queue<T>::Queue()
    : m_list()
{
}

template <typename T>
Queue<T>::Queue(std::size_t value)
    : m_list(value)
{
}

template <typename T>
Queue<T>::Queue(std::size_t count, const T &value)
    : m_list(count, value)
{
}

template <typename T>
Queue<T>::Queue(const Queue &other)
    : m_list(other.m_list)
{
}

template <typename T>
Queue<T>::Queue(Queue &&other) noexcept
    : m_list(std::move(other.m_list))
{
}

template <typename T>
Queue<T> &Queue<T>::operator=(const Queue &rhv)
{
    if (this != &rhv)
    {
        m_list = rhv.m_list;
    }
    return *this;
}

template <typename T>
Queue<T> &Queue<T>::operator=(Queue &&rhv)
{
    if (this != &rhv)
    {
        m_list = std::move(rhv.m_list);
    }
    return *this;
}

template <typename T>
bool Queue<T>::empty() const noexcept
{
    return m_list.empty();
}

template <typename T>
std::size_t Queue<T>::size() const noexcept
{
    return m_list.size();
}

template <typename T>
void Queue<T>::push(const T& value)
{
    m_list.push_back(value);
}

template <typename T>
void Queue<T>::push(T&& value)
{
    m_list.push_back(value);
}

template <typename T>
void Queue<T>::pop()
{
    m_list.pop_front();
}

template <typename T>
T& Queue<T>::front()
{
    return m_list.front();
}

template <typename T>
const T& Queue<T>::front() const
{
    return m_list.front();
}

template <typename T>
T& Queue<T>::back()
{
    return m_list.back();
}

template <typename T>
const T& Queue<T>::back() const
{
    return m_list.back();
}

template <typename T>
void Queue<T>::swap(Queue& other)
{
    m_list.swap(other.m_list);
}