#ifndef VEC_H
#define VEC_H

#include <cstddef>


template<typename T>
class Vec {
    size_t capasity;
    size_t size;
    T* arr;

    void resize();

public:
    Vec();
    Vec(size_t cap);
    ~Vec();
    Vec(const Vec& other);
    Vec& operator=(const Vec& other);
    Vec(Vec&& other)noexcept;
    Vec& operator=(Vec&& other)noexcept;
    void add(T item);
    const T& getByIndex(size_t index)const;
    size_t getSize()const;
    size_t getCapasity()const;
    T& operator[](size_t index);
    bool is_all(bool(*checkFunc)(T));
    T* begin();
    T* end();
};

template<typename T>
Vec<T>::Vec() :capasity(16), size(0) {
    this->arr = new T[this->capasity];
}

template<typename T>
Vec<T>::Vec(size_t cap) : capasity(cap), size(0) {
    this->arr = new T[this->capasity];
}

template<typename T>
Vec<T>::~Vec() {
    delete[] this->arr;
}

template<typename T>
Vec<T>::Vec(const Vec& other) : capasity(other.capasity), size(other.size){
    arr = new T[size];
    for (size_t i = 0; i < size; i++) {
        arr[i] = other.arr[i];
    }
}

template<typename T>
Vec<T>& Vec<T>::operator=(const Vec& other){
    T* newArr = new T[other.capasity];

    for (size_t i = 0; i < size; i++) {
        newArr[i] = other.arr[i];
    }

    delete[] arr;

    size = other.size;
    capasity = other.capasity;
    arr = newArr;

    return *this;
}

template<typename T>
Vec<T>::Vec(Vec&& other) noexcept : capasity(other.capasity), size(other.size), arr(other.arr){
    other.size = 0;
    other.arr = nullptr;
}

template<typename T>
Vec<T>& Vec<T>::operator=(Vec&& other) noexcept {
    delete[] arr;

    capasity = other.capasity;
    size = other.size;
    arr = other.arr;

    other.arr = nullptr;
    other.size = 0;
    other.capasity = 16;

    return *this;
}

template<typename T>
void Vec<T>::resize() {
    this->capasity *= 2;
    T* newArr = new T[this->capasity];
    for (size_t i = 0; i < this->size; i++) {
        newArr[i] = this->arr[i];
    }
    delete[] this->arr;
    arr = newArr;
}

template<typename T>
void Vec<T>::add(T item) {

    if (this->size == this->capasity) {
        resize();
    }

    this->arr[this->size] = item;
    this->size++;
}

template<typename T>
const T& Vec<T>::getByIndex(size_t index) const {
    return this->arr[index];
}

template<typename T>
size_t Vec<T>::getSize() const {
    return this->size;
}

template<typename T>
size_t Vec<T>::getCapasity() const {
    return this->capasity;
}

template<typename T>
T& Vec<T>::operator[](size_t index){
    return this->arr[index];
}

template<typename T>
bool Vec<T>::is_all(bool(*checkFunc)(T)){
    bool result = false;
    for (size_t i = 0; i < this->size; i++){
        result = checkFunc(this->arr[i]);
        if (result == false)
        {
            return false;
        }
    }
    return result;
}

template<typename T>
T* Vec<T>::begin(){
    return &(this->arr[0]);
}

template<typename T>
T* Vec<T>::end(){
    return &(this->arr[this->size]);
}

#endif