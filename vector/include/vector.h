#pragma once

#include <cstddef>
#include <iostream>

template<typename T>
class Vector
{
public:
    Vector() = default;
    Vector(const Vector<T>& other);
    ~Vector();

    void reserve(const std::size_t new_capacity);
    void push_back(const T& value);
    std::size_t size() const;
    std::size_t max_size() const;
    bool empty() const;
    void pop_back();
    void resize(const std::size_t count);


    //clear
    //insert
    //insert_range
    //emplace
    //emplace_back
    //erase
    //append_range;

    //Vector& operator=(const Vector& other);
    //Vector& (const Vector& other);

    //[]
    //[] const 
    // at()
    // front()
    //fornt const
    // back
    // back const
    // data
    // data const
    // capacity
    // clear - удалить все элементы из вектора

    // resize
    // swap
    // == != < <= > >=

    // merge

    // begin
    // cbegin
    // end
    // cend
    // rbegin
    // crbegin
    // rend
    // crend

private:
    T * m_arr = nullptr;
    std::size_t m_size = 0;
    std::size_t m_capacity = 0;
};


//////////////////////////////////////////////////////////////////////


template<typename T>
void Vector<T>::reserve(const std::size_t new_capacity)
{
    if (m_capacity >= new_capacity) {
        return;
    }
    std::size_t index = 0;
    T * new_arr = reinterpret_cast<T*>(new char[new_capacity * sizeof(T)]);
    try {
        for (; index < m_size; ++index) {
            new(new_arr + index) T(m_arr[index]);
        }
    } catch (...) {
        for (std::size_t i = 0; i < index; ++i) {
            (new_arr + i)->~T();
        }
        delete[] reinterpret_cast<char*>(new_arr);
        throw; 
    }
    for (std::size_t i = 0; i < index; ++i) {
        (m_arr + index)->~T();
    }
    
    delete[] reinterpret_cast<char*>(m_arr);
    m_arr = new_arr;
    m_capacity = new_capacity;
}

template<typename T>
void Vector<T>::push_back(const T& value)
{
    if (m_size == m_capacity) {
        reserve(m_capacity > 0 ? m_capacity * 2 : 1);
    }
    m_arr[m_size] = value;
    ++m_size;
}

template<typename T>
std::size_t Vector<T>::size() const
{
    return m_size;
}

template<typename T>
bool Vector<T>::empty() const
{
    return (m_size == 0);
}
template<typename T>
void Vector<T>::pop_back()
{
    if (size() == 0) {
        return;
    }
    (m_size - 1)->~T();
    --m_size;
}

template<typename T>
void Vector<T>::resize(const std::size_t count)
{
    if (count == m_size) {
        return;
    } else if (count > m_size) {
        reserve(count);
        std::size_t index = m_size;
        std::size_t create_index = m_size;
        try {
            for (; create_index < count; ++create_index) {
                new(m_arr + create_index) T();
            }
        } catch (...) {
            for (std::size_t i = m_size; i < create_index; ++i) {
                m_arr[i]->~T();
            }
            m_size = index;
            throw;
        }
        m_size = count;
    } else {
        for (std::size_t i = 0; i < count - m_size; ++i) {
            pop_back();
        }
        m_size = count;
    }
}

template<typename T>
Vector<T>::Vector(const Vector<T>& other)
{
    reserve(other.m_size);
    std::size_t index = 0;
    T * m_arr = reinterpret_cast<T*>(new char[other.m_size * sizeof(T)]);
    try {
        for (; index < m_size; ++index) {
            new(m_arr + index) T(m_arr[index]);
        }
    } catch (...) {
        for (std::size_t i = 0; i < index; ++i) {
            (m_arr + i)->~T();
        }
        delete[] reinterpret_cast<char*>(m_arr);
        throw; 
    }
    this->m_size = other.m_size;
    this->m_capacity = other.new_capacity;
}

template<typename T>
Vector<T>::~Vector()
{
    for (std::size_t i = 0; i < m_size; ++i) {
            (m_arr + i)->~T();
    }
    delete[] reinterpret_cast<char*>(m_arr);
}
