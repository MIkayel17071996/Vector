#include "Vector.h"
#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <unistd.h> 
#include <cassert>


/***************************SPECIAL FUNCTIONS****************************/
template <typename T>
Vector<T>::Vector()
    : m_size(0)
    , m_capacity(0)
    , m_array(nullptr)
{
}

template <typename T>
Vector<T>::Vector(const size_t value)
    : m_size(value)
    , m_capacity(value)
    , m_array(new T[m_capacity])
{
    for (int i = 0; i < m_size; ++i)
    {
        m_array[i] = 0;
    }
}

template <typename T>
Vector<T>::Vector(const std::size_t size, const T& value)
    : m_size(size)
    , m_capacity(size)
    , m_array(new T[m_capacity])
{
    for (int i = 0; i < m_size; ++i)
    {
        m_array[i] = value;
    }
}

template <typename T>
Vector<T>::Vector(const Vector& rhv)
    : m_size(rhv.m_size)
    , m_capacity(rhv.m_capacity)
{
    m_array = new T[m_capacity];

    for (int i = 0; i < m_size; ++i)
    {
        m_array[i] = rhv.m_array[i];
    }
}

template <typename T>
Vector<T>::Vector(Vector&& rhv) noexcept
    : m_size(rhv.m_size)
    , m_capacity(rhv.m_capacity)
{
    m_array = new T[m_capacity];

    for (int i = 0; i < m_size; ++i)
    {
        m_array[i] = rhv.m_array[i];
    }

    rhv.clear();
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> ls)
    : m_size(ls.size())
    , m_capacity(m_size)
    , m_array(new T[m_capacity])
{
    auto it = ls.begin();
    for (int i = 0; i < m_size; ++i)
    {
        m_array[i] = *it++;
    }
}
/***************************OPERATOR =****************************/
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& rhv)
{
    if (this != &rhv)
    {
        Vector<T> temp(rhv);
        swap(temp);
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& rhv) noexcept
{
    if (this != &rhv)
    {
        Vector<T> temp(rhv);
        swap(temp);
        rhv.clear();
    }
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(std::initializer_list<T> ls)
{
    clear();
    m_size = ls.size();
    m_capacity = m_size;
    m_array = new T[m_capacity];
    

    auto it = ls.begin();
    for (int i = 0; i < m_size; ++i)
    {
        m_array[i] = *it++;
    }
    return *this;

}


/*************************Element access**************************/
template <typename T>
T& Vector<T>::operator[](size_t index)
{

    return m_array[index];
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const 
{
    return m_array[index];
}

template <typename T>
T& Vector<T>::at(size_t index)
{
    if (index >= m_size) {
        throw std::out_of_range("Index out of range");
    }

    return m_array[index];
}

template <typename T>
const T& Vector<T>::at(size_t index) const 
{
    if (index >= m_size) {
        throw std::out_of_range("Index out of range");
    }
    
    return m_array[index];
}

template <typename T>
T& Vector<T>::front()
{
    if (empty())
    {
        throw std::logic_error("CANNOT RETURN ELEMENT OF THE FRONT , VECTOR IS EMPTY!!!");
    }

    return m_array[0];
}

template <typename T>
const T& Vector<T>::front() const
{
    if (empty())
    {
        throw std::logic_error("CANNOT RETURN ELEMENT OF THE FRONT , VECTOR IS EMPTY!!!");
    }

    return m_array[0];
}

template <typename T>
T& Vector<T>::back()
{
    if (empty())
    {
        throw std::logic_error("CANNOT RETURN ELEMENT OF THE FRONT , VECTOR IS EMPTY!!!");
    }

    return m_array[m_size-1];
}

template <typename T>
const T& Vector<T>::back() const 
{
    if (empty())
    {
        throw std::logic_error("CANNOT RETURN ELEMENT OF THE FRONT , VECTOR IS EMPTY!!!");
    }

    return m_array[m_size-1];
}

template <typename T>
T* Vector<T>::data() noexcept
{
    return m_array;
}

template <typename T>
const T* Vector<T>::data() const noexcept
{
    return m_array;
}
/***************************Modifiers****************************/

template <typename T>
void Vector<T>::clear() noexcept
{
    m_size = 0;
    m_capacity = 0;
    delete [] m_array;
    m_array = nullptr;
}

template <typename T>
Vector<T>::~Vector()
{
    clear();
}

template <typename T>
void Vector<T>::push_back(const T& value)
{
    if (m_capacity == 0 || m_size == m_capacity)
    {
        Realloc();
    } 

    m_array[m_size++] = value;

}

template <typename T>
void Vector<T>::push_back(T&& value)
{
    if (m_capacity == 0 || m_size == m_capacity)
    {
        Realloc();
    } 

    m_array[m_size++] = value;

}

template <typename T>
void Vector<T>::pop_back()
{
    if (empty())
    {
        throw std::out_of_range("THE VECTOR IS ALREADY EMPTY");
    }else {
        --m_size;
    }
}


template <typename T>
void Vector<T>::swap(Vector<T>& rhv)
{
    using std::swap;

    std::swap(m_size, rhv.m_size);
    std::swap(m_capacity, rhv.m_capacity);
    std::swap(m_array, rhv.m_array);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::insert(const Base_Iterator& pos, const T& value)
{
    size_type index = pos.m_ptr - m_array;
   
    if (m_size == m_capacity) {
        Realloc();
    }

    for (size_type i = m_size; i > index; --i) {
        m_array[i] = std::move(m_array[i - 1]);
    }

    m_array[index] = value;
    ++m_size;

    return Iterator(m_array + index);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::insert(const Base_Iterator& pos, size_t count, const T& value)
{
    size_type index = pos.m_ptr - m_array;

    if (m_size + count > m_capacity) {
        reserve(m_size + count);  
    }

    for (size_type i = m_size; i > index; --i) {
        m_array[i + count - 1] = std::move(m_array[i - 1]);
    }

    for (size_type i = index; i < index + count; ++i) {
        m_array[i] = value;
    }

    m_size += count;

    return Iterator(m_array + index);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::insert(const Base_Iterator& pos, std::initializer_list<T> ls)
{
    size_type index = pos.m_ptr - m_array;
    size_t count = ls.size();

    if (m_size + count > m_capacity) {
        reserve(m_size + count);  
    }

    for (size_type i = m_size; i > index; --i) {
        m_array[i + count - 1] = std::move(m_array[i - 1]);
    }

    auto it = ls.begin();
    for (size_type i = index; i < index + count; ++i) {
        m_array[i] = *it++;
    }

    m_size += count;

    return Iterator(m_array + index);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::erase(const Base_Iterator& pos)
{

    if (empty())
    {
        throw std::logic_error("THE VECTOR IS EMPTY");
    }

    size_type index = pos.m_ptr - m_array;

    for (size_type i = index; i < m_size - 1; ++i) {
        m_array[i] = std::move(m_array[i + 1]);
    }

    --m_size;

    return Iterator(m_array + index);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::erase(const Base_Iterator& pos1, const Base_Iterator& pos2)
{
    size_type start = pos1.m_ptr - m_array;
    size_type end = pos2.m_ptr - m_array;

    if (start > end || end >= m_size)
    {
        throw std::invalid_argument("Invalid range for erase");
    } else if(empty())
    {
        throw std::logic_error("THE VECTOR IS EMPTY");

    }

    size_type count = end - start + 1;

    for (size_type i = start + count; i < m_size; ++i)
    {
        m_array[i - count] = std::move(m_array[i]);
    }

    m_size -= count;

    return Iterator(m_array + start);
}

/***************************CAPACITY****************************/

template <typename T>
std::size_t Vector<T>::max_size() const noexcept
{
    std::size_t elem_size = sizeof(int);
    std::size_t max_bytes = sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE);
    std::size_t max_elements = max_bytes / elem_size;

    return max_elements;
}

template <typename T>
bool Vector<T>::empty() const noexcept
{
    return (m_size == 0);
}

template <typename T>
std::size_t Vector<T>::size() const noexcept
{
    return m_size;
}

template <typename T>
std::size_t Vector<T>::capacity() const noexcept
{
    return m_capacity;
}

template <typename T>
void Vector<T>::reserve(const std::size_t new_cap)
{
    if (new_cap <= m_capacity)
    {
        return;
    }
    m_capacity = new_cap;
    T* tmp = new T[new_cap];

    for (int i = 0; i < m_size; ++i)
    {
        tmp[i] = m_array[i];
    }

    delete [] m_array;
    m_array = tmp;
    tmp = nullptr;
}

template <typename T>
void Vector<T>::shrink_to_fit() noexcept
{
    if (empty() || m_size == m_capacity)
    {
        return;
    }

    if (m_size == 0)
    {
        m_capacity = 0;
        delete [] m_array;
        m_array = nullptr;

    } else {
        
        m_capacity = m_size;
        T* tmp = new T[m_capacity];

        for (int i = 0; i < m_size; ++i)
        {
            tmp[i] = m_array[i];
        }

        delete [] m_array;
        m_array = tmp;
        tmp = nullptr;
    }
}

template <typename T>
void Vector<T>::resize(const std::size_t new_size)
{   
    if (new_size == m_size)
    {
        return;
    } else if (new_size < m_size)
    {
        m_size = new_size;
    } else {
        for (int i = m_size; i <= new_size; ++i)
        {
            push_back(0);
        }
        m_size = new_size;
    }
}

template <typename T>
void Vector<T>::resize(const std::size_t new_size,const T& value)
{   
    if (new_size == m_size)
    {
        return;
    } else if (new_size < m_size)
    {
        m_size = new_size;
    } else {
        for (int i = m_size; i < new_size; ++i)
        {
            push_back(value);
        }
        m_size = new_size;
    }
}


template <typename T>
void Vector<T>::Realloc()
{
    if (m_capacity == 0)
    {
        m_capacity = 10;
        m_array = new T[m_capacity];
    }else {
        m_capacity *= 2;

        T* tmp = new T[m_capacity];

        for (int i = 0; i < m_size; ++i)
        {
            tmp[i] = m_array[i];
        }

        delete [] m_array;
        m_array = tmp;
        tmp = nullptr;
    }
}

/***************************__Iterators__****************************/
template <typename T>
typename Vector<T>::Iterator Vector<T>::begin() noexcept
{
    return Iterator(m_array);
}

template <typename T>
typename Vector<T>::Const_Iterator Vector<T>::cbegin() const noexcept
{
    return Const_Iterator(m_array);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::end() noexcept
{
    return Iterator(m_array + m_size);
}

template <typename T>
typename Vector<T>::Const_Iterator Vector<T>::cend() const noexcept
{
    return Const_Iterator(m_array + m_size);
}

template <typename T>
typename Vector<T>::Reverse_Iterator Vector<T>::rbegin() noexcept
{
    return Reverse_Iterator(m_array + m_size -1);
}

template <typename T>
typename Vector<T>::Const_Reverse_Iterator Vector<T>::crbegin() const noexcept
{
    return Const_Reverse_Iterator(m_array + m_size -1);
}

template <typename T>
typename Vector<T>::Reverse_Iterator Vector<T>::rend() noexcept
{
    return Reverse_Iterator(m_array -1);
}

template <typename T>
typename Vector<T>::Const_Reverse_Iterator Vector<T>::crend() const noexcept
{
    return Const_Reverse_Iterator(m_array -1);
}

/***************************Base Iterator****************************/
template <typename T>
Vector<T>::Base_Iterator::Base_Iterator(T* ptr)
   : m_ptr(ptr)
{
}

template <typename T>
Vector<T>::Base_Iterator::Base_Iterator(const Base_Iterator & rhv)
   : m_ptr(rhv.ptr)
{
}

template <typename T>
Vector<T>::Base_Iterator::~Base_Iterator()
{
}

template <typename T>
typename Vector<T>::Base_Iterator& Vector<T>::Base_Iterator::operator=(const Base_Iterator &other)
{
    m_ptr = other.m_ptr;
    return *this;
}

template <typename T>
typename Vector<T>::Base_Iterator& Vector<T>::Base_Iterator::operator=(Base_Iterator &&other)
{
    m_ptr = other.m_ptr;
    other.m_ptr = nullptr;
    return *this;
}

template <typename T>
bool Vector<T>::Base_Iterator::operator<(const Base_Iterator &rhv) const
{
    return m_ptr < rhv.m_ptr;
}

template <typename T>
bool Vector<T>::Base_Iterator::operator>(const Base_Iterator &rhv) const
{
    return m_ptr > rhv.m_ptr;
}

template <typename T>
bool Vector<T>::Base_Iterator::operator<=(const Base_Iterator &rhv) const
{
    return m_ptr <= rhv.m_ptr;
}

template <typename T>
bool Vector<T>::Base_Iterator::operator>=(const Base_Iterator &rhv) const
{
    return m_ptr >= rhv.m_ptr;
}

template <typename T>
bool Vector<T>::Base_Iterator::operator==(const Base_Iterator &rhv) const
{
    return m_ptr == rhv.m_ptr;
}

template <typename T>
bool Vector<T>::Base_Iterator::operator!=(const Base_Iterator &rhv) const
{
    return m_ptr != rhv.m_ptr;
}

/***************************Const_Iterator****************************/
template <typename T>
Vector<T>::Const_Iterator::Const_Iterator(T* ptr)
   : Base_Iterator(ptr)
{
}

template <typename T>
Vector<T>::Const_Iterator::Const_Iterator()
   : Base_Iterator(nullptr)
{
}

template <typename T>
Vector<T>::Const_Iterator::Const_Iterator(const Const_Iterator & other)
    : Base_Iterator(other.m_ptr)
{
}

template <typename T>
Vector<T>::Const_Iterator::Const_Iterator(Base_Iterator && other)
    : Base_Iterator(std::move(other.ptr))
{
}

template <typename T>
const typename  Vector<T>::Const_Iterator& Vector<T>::Const_Iterator::operator=
                (const Base_Iterator & rhv)
{
    Base_Iterator::m_ptr = rhv.m_ptr;  
    return *this;
}

template <typename T>
const typename Vector<T>::Const_Iterator& Vector<T>::Const_Iterator::operator=
                (Base_Iterator && rhv)
{
    Base_Iterator::m_ptr = std::move(rhv.m_ptr);
    return *this;
}

template <typename T>
const T& Vector<T>::Const_Iterator::operator*() const
{
    assert(Base_Iterator::m_ptr != nullptr);
    return *Base_Iterator::m_ptr;
}

template <typename T>
const T* Vector<T>::Const_Iterator::operator->() const
{
    assert(Base_Iterator::m_ptr != nullptr);
    return Base_Iterator::m_ptr;
}

template <typename T>
const typename Vector<T>::Const_Iterator& Vector<T>::Const_Iterator::operator++()
{
    assert(Base_Iterator::m_ptr != nullptr && "Cannot increment past end");
    ++Base_Iterator::m_ptr;
    return *this;
}       

template <typename T>
const typename Vector<T>::Const_Iterator& Vector<T>::Const_Iterator::operator++(int)
{
    assert(Base_Iterator::m_ptr != nullptr && "Cannot increment past end");
    Const_Iterator temp = *this;
    ++(*this);
    return temp;
} 

template <typename T>
const typename Vector<T>::Const_Iterator& Vector<T>::Const_Iterator::operator--()
{
    assert(Base_Iterator::m_ptr != nullptr && "Cannot decrement past begin");
    --(*this);
    return *this;
}

template <typename T>
const typename Vector<T>::Const_Iterator& Vector<T>::Const_Iterator::operator--(int)
{
    assert(Base_Iterator::m_ptr != nullptr && "Cannot decrement past begin");
    Const_Iterator temp = *this;
    --(*this);
    return temp;
}


template <typename T>
typename Vector<T>::Const_Iterator Vector<T>::Const_Iterator::operator+(long long int n) const {
    Const_Iterator result = *this;
    result += n;
    return result;
}

template <typename T>
typename Vector<T>::Const_Iterator Vector<T>::Const_Iterator::operator-(long long int n) const {
    Const_Iterator result = *this;
    result -= n;
    return result;
}

template <typename T>
const typename Vector<T>::Const_Iterator &Vector<T>::Const_Iterator::operator+=(long long int n) {
    if (n >= 0) {
        for (long long int i = 0; i < n; ++i) {
            ++(*this);
        }
    } else {
        for (long long int i = 0; i > n; --i) {
            --(*this);
        }
    }
    return *this;
}

template <typename T>
const typename Vector<T>::Const_Iterator &Vector<T>::Const_Iterator::operator-=(long long int n) {
    return (*this += -n);
}

template <typename T>
const T &Vector<T>::Const_Iterator::operator[](std::size_t index) const {
    return *(*this + index);
}

/***************************__Iterator__****************************/
template <typename T>
Vector<T>::Iterator::Iterator(T* ptr)
   : Const_Iterator(ptr)
{
}

template <typename T>
Vector<T>::Iterator::Iterator()
   : Const_Iterator(nullptr)
{
}

template <typename T>
Vector<T>::Iterator::Iterator(const Base_Iterator & other)
    : Const_Iterator(other.ptr)
{
}

template <typename T>
Vector<T>::Iterator::Iterator(Base_Iterator && other)
    : Const_Iterator(std::move(other.ptr))
{
}

template <typename T>
const typename  Vector<T>::Iterator& Vector<T>::Iterator::operator=
                (const Base_Iterator & rhv)
{
    Base_Iterator::m_ptr = rhv.m_ptr;  
    return *this;
}

template <typename T>
const typename Vector<T>::Iterator& Vector<T>::Iterator::operator=
                (Base_Iterator && rhv)
{
    Base_Iterator::m_ptr = std::move(rhv.m_ptr);
    return *this;
}

template <typename T>
T& Vector<T>::Iterator::operator*()
{
    assert(Base_Iterator::m_ptr != nullptr);
    return *Base_Iterator::m_ptr;
}

template <typename T>
T* Vector<T>::Iterator::operator->() 
{
    assert(Base_Iterator::m_ptr != nullptr);
    return Base_Iterator::m_ptr;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
{
    assert(Base_Iterator::m_ptr != nullptr && "Cannot increment past end");
    ++Base_Iterator::m_ptr;
    return *this;
}       

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator++(int)
{
    assert(Base_Iterator::m_ptr != nullptr && "Cannot increment past end");
    Iterator temp = *this;
    ++(*this);
    return temp;
} 

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator--()
{
    assert(Base_Iterator::m_ptr != nullptr && "Cannot decrement past begin");
    --(*this);
    return *this;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator--(int)
{
    assert(Base_Iterator::m_ptr != nullptr && "Cannot decrement past begin");
    Iterator temp = *this;
    --(*this);
    return temp;
}


template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator+(long long int n) const {
    Iterator result = *this;
    result += n;
    return result;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator-(long long int n) const {
    Iterator result = *this;
    result -= n;
    return result;
}

template <typename T>
typename Vector<T>::Iterator &Vector<T>::Iterator::operator+=(long long int n) {
    if (n >= 0) {
        for (long long int i = 0; i < n; ++i) {
            ++(*this);
        }
    } else {
        for (long long int i = 0; i > n; --i) {
            --(*this);
        }
    }
    return *this;
}

template <typename T>
typename Vector<T>::Iterator &Vector<T>::Iterator::operator-=(long long int n) {
    return (*this += -n);
}

template <typename T>
T& Vector<T>::Iterator::operator[](std::size_t index)
{
    return *(*this + index);
}

/**************************Const_Reverse_Iterator****************************/
template <typename T>
Vector<T>::Const_Reverse_Iterator::Const_Reverse_Iterator(T* ptr)
   : Base_Iterator(ptr)
{
}

template <typename T>
Vector<T>::Const_Reverse_Iterator::Const_Reverse_Iterator()
   : Base_Iterator(nullptr)
{
}

template <typename T>
Vector<T>::Const_Reverse_Iterator::Const_Reverse_Iterator(const Base_Iterator & other)
    : Base_Iterator(other.ptr)
{
}

template <typename T>
Vector<T>::Const_Reverse_Iterator::Const_Reverse_Iterator(Base_Iterator && other)
    : Base_Iterator(std::move(other.ptr))
{
}

template <typename T>
const typename  Vector<T>::Const_Reverse_Iterator& Vector<T>::Const_Reverse_Iterator::operator=
                (const Base_Iterator & rhv)
{
    Base_Iterator::m_ptr = rhv.m_ptr;  
    return *this;
}

template <typename T>
const typename Vector<T>::Const_Reverse_Iterator& Vector<T>::Const_Reverse_Iterator::operator=
                (Base_Iterator && rhv)
{
    Base_Iterator::m_ptr = std::move(rhv.m_ptr);
    return *this;
}

template <typename T>
const T& Vector<T>::Const_Reverse_Iterator::operator*() const
{
    assert(Base_Iterator::m_ptr != nullptr);
    return *Base_Iterator::m_ptr;
}

template <typename T>
const T* Vector<T>::Const_Reverse_Iterator::operator->() const
{
    assert(Base_Iterator::m_ptr != nullptr);
    return Base_Iterator::m_ptr;
}

template <typename T>
const typename Vector<T>::Const_Reverse_Iterator& Vector<T>::Const_Reverse_Iterator::operator++()
{
    assert(Base_Iterator::m_ptr != nullptr && "Cannot increment past end");
    --Base_Iterator::m_ptr;
    return *this;
}       

template <typename T>
const typename Vector<T>::Const_Reverse_Iterator& Vector<T>::Const_Reverse_Iterator::operator++(int)
{
    assert(Base_Iterator::m_ptr != nullptr && "Cannot increment past end");
    Const_Reverse_Iterator temp = *this;
    --(*this);
    return temp;
} 

template <typename T>
const typename Vector<T>::Const_Reverse_Iterator& Vector<T>::Const_Reverse_Iterator::operator--()
{
    assert(Base_Iterator::m_ptr != nullptr && "Cannot decrement past begin");
    ++(*this);
    return *this;
}

template <typename T>
const typename Vector<T>::Const_Reverse_Iterator& Vector<T>::Const_Reverse_Iterator::operator--(int)
{
    assert(Base_Iterator::m_ptr != nullptr && "Cannot decrement past begin");
    Const_Reverse_Iterator temp = *this;
    ++(*this);
    return temp;
}


template <typename T>
typename Vector<T>::Const_Reverse_Iterator Vector<T>::Const_Reverse_Iterator::operator+(long long int n) const {
    Const_Reverse_Iterator result = *this;
    result -= n;
    return result;
}

template <typename T>
typename Vector<T>::Const_Reverse_Iterator Vector<T>::Const_Reverse_Iterator::operator-(long long int n) const {
    Const_Reverse_Iterator result = *this;
    result += n;
    return result;
}

template <typename T>
const typename Vector<T>::Const_Reverse_Iterator &Vector<T>::Const_Reverse_Iterator::operator+=(long long int n) {
    if (n >= 0) {
        for (long long int i = 0; i < n; ++i) {
            --(*this);
        }
    } else {
        for (long long int i = 0; i > n; --i) {
            ++(*this);
        }
    }
    return *this;
}

template <typename T>
const typename Vector<T>::Const_Reverse_Iterator &Vector<T>::Const_Reverse_Iterator::operator-=(long long int n) {
    return (*this -= -n);
}

template <typename T>
const T &Vector<T>::Const_Reverse_Iterator::operator[](std::size_t index) const {
    return *(*this - index);
}
/**************************Const_Reverse_Iterator****************************/
template <typename T>
Vector<T>::Reverse_Iterator::Reverse_Iterator(T* ptr)
   : Const_Reverse_Iterator(ptr)
{
}

template <typename T>
Vector<T>::Reverse_Iterator::Reverse_Iterator()
   : Const_Reverse_Iterator(nullptr)
{
}

template <typename T>
Vector<T>::Reverse_Iterator::Reverse_Iterator(const Base_Iterator & other)
    : Const_Reverse_Iterator(other.ptr)
{
}

template <typename T>
Vector<T>::Reverse_Iterator::Reverse_Iterator(Base_Iterator && other)
    : Const_Reverse_Iterator(std::move(other.ptr))
{
}

template <typename T>
const typename  Vector<T>::Reverse_Iterator& Vector<T>::Reverse_Iterator::operator=
                (const Base_Iterator & rhv)
{
    Base_Iterator::m_ptr = rhv.m_ptr;  
    return *this;
}

template <typename T>
const typename Vector<T>::Reverse_Iterator& Vector<T>::Reverse_Iterator::operator=
                (Base_Iterator && rhv)
{
    Base_Iterator::m_ptr = std::move(rhv.m_ptr);
    return *this;
}

template <typename T>
T& Vector<T>::Reverse_Iterator::operator*() 
{
    assert(Base_Iterator::m_ptr != nullptr);
    return *Base_Iterator::m_ptr;
}

template <typename T>
T* Vector<T>::Reverse_Iterator::operator->() 
{
    assert(Base_Iterator::m_ptr != nullptr);
    return Base_Iterator::m_ptr;
}

template <typename T>
typename Vector<T>::Reverse_Iterator& Vector<T>::Reverse_Iterator::operator++()
{
    assert(Base_Iterator::m_ptr != nullptr && "Cannot increment past end");
    --Base_Iterator::m_ptr;
    return *this;
}       

template <typename T>
typename Vector<T>::Reverse_Iterator& Vector<T>::Reverse_Iterator::operator++(int)
{
    assert(Base_Iterator::m_ptr != nullptr && "Cannot increment past end");
    Reverse_Iterator temp = *this;
    --(*this);
    return temp;
} 

template <typename T>
typename Vector<T>::Reverse_Iterator& Vector<T>::Reverse_Iterator::operator--()
{
    assert(Base_Iterator::m_ptr != nullptr && "Cannot decrement past begin");
    ++(*this);
    return *this;
}

template <typename T>
typename Vector<T>::Reverse_Iterator& Vector<T>::Reverse_Iterator::operator--(int)
{
    assert(Base_Iterator::m_ptr != nullptr && "Cannot decrement past begin");
    Reverse_Iterator temp = *this;
    ++(*this);
    return temp;
}


template <typename T>
typename Vector<T>::Reverse_Iterator Vector<T>::Reverse_Iterator::operator+(long long int n) {
    Reverse_Iterator result = *this;
    result -= n;
    return result;
}

template <typename T>
typename Vector<T>::Reverse_Iterator Vector<T>::Reverse_Iterator::operator-(long long int n) {
    Reverse_Iterator result = *this;
    result += n;
    return result;
}

template <typename T>
typename Vector<T>::Reverse_Iterator &Vector<T>::Reverse_Iterator::operator+=(long long int n) {
    if (n >= 0) {
        for (long long int i = 0; i < n; ++i) {
            --(*this);
        }
    } else {
        for (long long int i = 0; i > n; --i) {
            ++(*this);
        }
    }
    return *this;
}

template <typename T>
typename Vector<T>::Reverse_Iterator &Vector<T>::Reverse_Iterator::operator-=(long long int n) {
    return (*this -= -n);
}

template <typename T>
T &Vector<T>::Reverse_Iterator::operator[](std::size_t index)  {
    return *(*this - index);
}


/***************************Non-member functions****************************/

template <typename T, typename U>
bool operator==(const Vector<T>& lhv,const Vector<U>& rhv)
{
    if (lhv.size() != rhv.size())
    {
        return false;
    }

    int size = lhv.size();

    for (int i = 0; i < size; ++i)
    {
        if (lhv[i] != rhv[i])
        {
            return false;
        }
    }

    return true;
}

template <typename T, typename U>
bool operator!=(const Vector<T>& lhv,const Vector<U>& rhv)
{
    return !(lhv == rhv);
}

template <typename T, typename U>
bool operator<(const Vector<T>& lhv,const Vector<U>& rhv)
{
    if (lhv == rhv)
    {
        return false;
    }

    size_t minSize = std::min(lhv.size(), rhv.size());
    
    for (size_t i = 0; i < minSize; ++i) {
        if (lhv[i] < rhv[i]) {
            return true;  
        } else if (lhv[i] > rhv[i]) {
            return false; 
        }
    }

     return lhv.size() < rhv.size();
}

template <typename T, typename U>
bool operator>(const Vector<T>& lhv,const Vector<U>& rhv)
{
    if (lhv == rhv)
    {
        return false;
    }

    return !(lhv < rhv);
}   

template <typename T, typename U>
bool operator<=(const Vector<T>& lhv,const Vector<U>& rhv)
{
    if (lhv == rhv)
    {
        return true;
    }

    size_t minSize = std::min(lhv.size(), rhv.size());
    
    for (size_t i = 0; i < minSize; ++i) {
        if (lhv[i] < rhv[i]) {
            return true;  
        } else if (lhv[i] > rhv[i]) {
            return false; 
        }
    }

     return lhv.size() < rhv.size();
}

template <typename T, typename U>
bool operator>=(const Vector<T>& lhv,const Vector<U>& rhv)
{
    if (lhv == rhv)
    {
        return true;
    }

    return !(lhv < rhv);
}  






