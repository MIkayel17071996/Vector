#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <unistd.h> 


template<typename T>
class Vector 
{
    //////////////////////////////////////
    public:
    class Base_Iterator
    {
        friend class Vector<T>;

    private:
        T *m_ptr = nullptr;

    public:
        ~Base_Iterator();
        bool operator<(const Base_Iterator &) const;
        bool operator>(const Base_Iterator &) const;
        bool operator<=(const Base_Iterator &) const;
        bool operator>=(const Base_Iterator &) const;
        bool operator==(const Base_Iterator &) const;
        bool operator!=(const Base_Iterator &) const;

        Base_Iterator &operator=(const Base_Iterator &);
        Base_Iterator &operator=(Base_Iterator &&);

    protected:
        explicit Base_Iterator(T *);
        Base_Iterator(const Base_Iterator&);
    };

public:
    class Const_Iterator : public Base_Iterator
    {
        friend class Vector<T>;

    protected:
        explicit Const_Iterator(T *);

    public:
        Const_Iterator();
        Const_Iterator(const Const_Iterator &);
        Const_Iterator(Base_Iterator &&);

        const Const_Iterator &operator=(const Base_Iterator &);
        const Const_Iterator &operator=(Base_Iterator &&);

        const T &operator*() const;
        const T *operator->() const;
        const Const_Iterator &operator++();
        const Const_Iterator &operator++(int);
        const Const_Iterator &operator--();
        const Const_Iterator &operator--(int);
        Const_Iterator operator+(long long int) const;
        Const_Iterator operator-(long long int) const;
        const Const_Iterator &operator+=(long long int);
        const Const_Iterator &operator-=(long long int);
        const T &operator[](std::size_t) const;
    };

    class Iterator : public Const_Iterator
    {
        friend class Vector<T>;

    public:
        Iterator();
        Iterator(const Base_Iterator &);
        Iterator(Base_Iterator &&);

        const Iterator &operator=(const Base_Iterator &);
        const Iterator &operator=(Base_Iterator &&);

        T &operator*();
        T *operator->();

        Iterator &operator++();
        Iterator &operator++(int);
        Iterator &operator--();
        Iterator &operator--(int);
        Iterator operator+(long long int) const;
        Iterator operator-(long long int) const;
        Iterator &operator+=(long long int);
        Iterator &operator-=(long long int);

        T &operator[](std::size_t);

    protected:
        explicit Iterator(T *);
    };

    class Const_Reverse_Iterator : public Base_Iterator
    {
        friend class Vector<T>;

    protected:
        explicit Const_Reverse_Iterator(T *);

    public:
        Const_Reverse_Iterator();
        Const_Reverse_Iterator(const Base_Iterator &);
        Const_Reverse_Iterator(Base_Iterator &&);

        const Const_Reverse_Iterator &operator=(const Base_Iterator &);
        const Const_Reverse_Iterator &operator=(Base_Iterator &&);

        const T &operator*() const;
        const T *operator->() const;

        const Const_Reverse_Iterator &operator++();
        const Const_Reverse_Iterator &operator++(int);
        const Const_Reverse_Iterator &operator--();
        const Const_Reverse_Iterator &operator--(int);
        Const_Reverse_Iterator operator+(long long int) const;
        Const_Reverse_Iterator operator-(long long int) const;
        const Const_Reverse_Iterator &operator+=(long long int);
        const Const_Reverse_Iterator &operator-=(long long int);
        const T &operator[](std::size_t) const;
    };

    class Reverse_Iterator : public Const_Reverse_Iterator
    {
        friend class Vector<T>;

    public:
        Reverse_Iterator();
        Reverse_Iterator(const Base_Iterator &);
        Reverse_Iterator(Base_Iterator &&);

        const Reverse_Iterator &operator=(const Base_Iterator &);
        const Reverse_Iterator &operator=(Base_Iterator &&);

        T &operator*();
        T *operator->();

        Reverse_Iterator &operator++();
        Reverse_Iterator &operator++(int);
        Reverse_Iterator &operator--();
        Reverse_Iterator &operator--(int);
        Reverse_Iterator operator+(long long int);
        Reverse_Iterator operator-(long long int);
        Reverse_Iterator &operator+=(long long int);
        Reverse_Iterator &operator-=(long long int);

        T &operator[](std::size_t);

    protected:
        explicit Reverse_Iterator(T *);
    };
    /////////////////////////////////////

public:
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

public:
    Vector();
    Vector(const size_t);
    Vector(const Vector&);
    Vector(Vector&&) noexcept;
    Vector(std::initializer_list<T>);
    Vector(const std::size_t, const  T&);
    ~Vector();

    Vector& operator=(const Vector&);
    Vector& operator=(Vector&&) noexcept;
    Vector& operator=(std::initializer_list<T>);

    T& operator[](std::size_t);
    const T& operator[](std::size_t) const;
    T& at(std::size_t);
    const T& at(std::size_t) const;
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    T* data() noexcept;
    const T* data() const noexcept;

    Iterator begin() noexcept;
    Const_Iterator cbegin() const noexcept;
    Iterator end() noexcept;
    Const_Iterator cend() const noexcept;
    Reverse_Iterator rbegin() noexcept;
    Const_Reverse_Iterator crbegin() const noexcept;
    Reverse_Iterator rend() noexcept;
    Const_Reverse_Iterator crend() const noexcept;

    bool empty() const noexcept;
    std::size_t size() const noexcept;
    std::size_t max_size() const noexcept;
    void reserve(const std::size_t);
    std::size_t capacity() const noexcept;
    void shrink_to_fit() noexcept;
    /*ASSIGN,emplace,*/

    void clear() noexcept;
    Iterator insert(const Base_Iterator&, const T&);
    Iterator insert(const Base_Iterator&, size_t, const T&);
    Iterator insert(const Base_Iterator&, std::initializer_list<T>);
    Iterator erase(const Base_Iterator&);
    Iterator erase(const Base_Iterator&, const Base_Iterator&);
    void push_back(const T&);
    void push_back(T&&);
    void pop_back();
    void resize(const std::size_t);
    void resize(const std::size_t, const T&);
    void swap(Vector&);
private:
    void Realloc();

private:
    std::size_t m_size;
    std::size_t m_capacity;
    T* m_array;
};

template <typename T, typename U>
bool operator==(const Vector<T>&,const Vector<U>&);

template <typename T, typename U>
bool operator!=(const Vector<T>&,const Vector<U>&);

template <typename T, typename U>
bool operator<(const Vector<T>&,const Vector<U>&);

template <typename T, typename U>
bool operator<=(const Vector<T>&,const Vector<U>&);

template <typename T, typename U>
bool operator>(const Vector<T>&,const Vector<U>&);

template <typename T, typename U>
bool operator>=(const Vector<T>&,const Vector<U>&);


#include "Vector.cpp"


#endif // VECTOR_HPP