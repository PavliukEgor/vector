#include <cstddef>

#ifndef _VECTOR_
#define _VECTOR_
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
    bool empty() const;
    void pop_back();
    void resize(const std::size_t count);

    // оператор присваивания
    // оператор индексирования [] + const []
    // merge
    // итераторы

private:
    T * m_arr;
    std::size_t m_size = 0;
    std::size_t m_capacity = 0;
};



#endif // _VECTOR_