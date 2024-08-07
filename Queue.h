#ifndef QUEUE_H
#define QUEUE_H
#include <list>

template <typename T>
class Queue
{
public:
    Queue();
    ~Queue();
    Queue(std::size_t);
    Queue(std::size_t, const T &);
    Queue(const Queue &);
    Queue(Queue &&) noexcept;

public:
    Queue &operator=(const Queue &);
    Queue &operator=(Queue &&);

public:
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    bool empty() const noexcept; //
    std::size_t size() const noexcept; //
    void push(const T &);
    void push(T &&);
    void pop();
    void swap(Queue &);

public:
    template <typename U>
    friend bool operator==(const Queue<T> &lhs, const Queue<U> &rhs)
    {
        return lhs.m_list == rhs.m_list;
    }

    template <typename U>
    friend bool operator!=(const Queue<T> &lhs, const Queue<U> &rhs)
    {
        return !(lhs == rhs);
    }

    template <typename U>
    friend bool operator<(const Queue<T> &lhs, const Queue<U> &rhs)
    {
        return lhs.m_list < rhs.m_list;
    }

    template <typename U>
    friend bool operator<=(const Queue<T> &lhs, const Queue<U> &rhs)
    {
        return !(rhs < lhs);
    }

    template <typename U>
    friend bool operator>(const Queue<T> &lhs, const Queue<U> &rhs)
    {
        return rhs < lhs;
    }

    template <typename U>
    friend bool operator>=(const Queue<T> &lhs, const Queue<U> &rhs)
    {
        return !(lhs < rhs);
    }

private:
    std::list<T> m_list;
};

#include "Queue.cpp"

#endif //QUEUE_H