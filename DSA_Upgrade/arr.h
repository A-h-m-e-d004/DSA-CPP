#ifndef ARR_H
#define ARR_H

#include <cstddef>
#include<new>

template<typename T , size_t size>
class Arr {
    constexpr static size_t arrSize = size;
    size_t index;
    T* data;

public:

    Arr();
    ~Arr();
    Arr(const Arr& other);
    Arr& operator=(const Arr& other);
    Arr(Arr&& other)noexcept;
    Arr& operator=(Arr&& other)noexcept;
    void push(const T& val);
    T& operator[](size_t i);
    const T& operator[](size_t i)const;
};

template<typename T, size_t size>
Arr<T, size>::Arr(): index(0), data(static_cast<T*>(::operator new(sizeof(T) * size))){}

template<typename T, size_t size>
Arr<T, size>::~Arr(){
    for (size_t i = 0; i < index; i++)
    {
        data[i].~T();
    }
    ::operator delete(data);
}

template<typename T, size_t size>
Arr<T, size>::Arr(const Arr& other) : index(other.index), data(static_cast<T*>(::operator new(sizeof(T) * other.arrSize))) {
    for (size_t i = 0; i < index; i++)
    {
        new (data + i) T(other.data[i]);
    }
}

template<typename T, size_t size>
Arr<T, size>& Arr<T, size>::operator=(const Arr& other){
    T* newData = static_cast<T*>(::operator new(sizeof(T) * other.arrSize));

    for (size_t i = 0; i < other.index; i++)
    {
        new (newData + i) T(other.data[i]);
    }

    for (size_t i = 0; i < index; i++)
    {
        data[i].~T();
    }

    ::operator delete(data);

    arrSize = other.arrSize;
    index = other.index;
    data = newData;

    return *this;
}

template<typename T, size_t size>
Arr<T, size>::Arr(Arr&& other) noexcept {
    arrSize = other.arrSize;
    index = other.index;
    data = other.data;

    other.arrSize = 0;
    other.index = 0;
    other.data = nullptr;
}



template<typename T, size_t size>
void Arr<T, size>::push(const T& val){

    if (index < size)
    {
        new (data + index) T(val);
        index++;
    }

}

template<typename T, size_t size>
T& Arr<T, size>::operator[](size_t i){
    return data[i];
}

template<typename T, size_t size>
const T& Arr<T, size>::operator[](size_t i)const{
    return data[i];
}

#endif