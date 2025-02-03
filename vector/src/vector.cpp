#include "../include/vector.h"

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
    m_arr[m_size - 1]->~T();
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
    m_arr->m_size = other.m_size;
    m_arr->m_capacity = other.new_capacity;
}

template<typename T>
Vector<T>::~Vector()
{
    for (std::size_t i = 0; i < m_size; ++i) {
            (m_arr + i)->~T();
    }
    delete[] reinterpret_cast<char*>(m_arr);
}
