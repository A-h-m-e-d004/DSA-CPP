#ifndef VEC_H
#define VEC_H

#include <cstddef>
#include<new>
#include<exception>

template<typename T>
class Vec {
    size_t capasity;
    size_t size;
    T* arr;

    bool resize();
    T* allocate(size_t cap);
    void destroy_elements();
    void free_memory();

public:
    Vec();
    Vec(size_t cap);
    ~Vec();
    Vec(const Vec& other);
    Vec& operator=(const Vec& other);
    Vec(Vec&& other)noexcept;
    Vec& operator=(Vec&& other)noexcept;
    void add(const T& item);
    void add(T&& item);
    const T& getByIndex(size_t index)const;
    size_t getSize()const;
    size_t getCapasity()const;
    T& operator[](size_t index);
    const T& operator[](size_t index)const;
    bool is_all(bool(*checkFunc)(const T&));
    bool is_empty()const;
    template<typename Func>
    void applyAll(Func func);
    T* begin();
    T* end();

    template<typename... Args>
    void add_all(Args... args);

    void reserve(size_t cap);
};

template<typename T>
T* Vec<T>::allocate(size_t cap){
    if (cap == 0)
    {
        return nullptr;
    }
    return static_cast<T*>(::operator new(sizeof(T) * cap, std::nothrow));
}

template<typename T>
void Vec<T>::destroy_elements(){
    for (size_t i = 0; i < size; i++)
    {
        arr[i].~T();
    }
}

template<typename T>
void Vec<T>::free_memory(){
    ::operator delete(arr);
}

template<typename T>
Vec<T>::Vec() :capasity(8), size(0){
    arr = allocate(capasity);
    if (!arr)
    {
        std::terminate();
    }
}

template<typename T>
Vec<T>::Vec(size_t cap) : capasity(cap), size(0){
    arr = allocate(capasity);
    if (!arr)
    {
        std::terminate();
    }
}

template<typename T>
Vec<T>::~Vec() {
    destroy_elements();
    free_memory();
}

template<typename T>
Vec<T>::Vec(const Vec& other) : capasity(other.capasity), size(other.size){
    arr = allocate(capasity);
    for (size_t i = 0; i < size; i++) {
        new (arr + i) T(other.arr[i]);
    }
}

template<typename T>
Vec<T>& Vec<T>::operator=(const Vec& other){

    if (this == &other)
    {
        return *this;
    }

    T* newArr = allocate(other.capasity);

    if (!newArr)
    {
        return *this;
    }

    for (size_t i = 0; i < other.size; i++)
    {
        new (newArr + i) T(other.arr[i]);
    }

    destroy_elements();
    
    free_memory();

    size = other.size;
    capasity = other.capasity;
    arr = newArr;

    return *this;
}

template<typename T>
Vec<T>::Vec(Vec&& other) noexcept : capasity(other.capasity), size(other.size), arr(other.arr){
    other.capasity = 8;
    other.size = 0;
    other.arr = nullptr;
}

template<typename T>
Vec<T>& Vec<T>::operator=(Vec&& other) noexcept {

    if (this == &other)
    {
        return *this;
    }

    destroy_elements();
    
    free_memory();

    capasity = other.capasity;
    size = other.size;
    arr = other.arr;

    other.arr = nullptr;
    other.size = 0;
    other.capasity = 8;

    return *this;
}

template<typename T>
bool Vec<T>::resize() {

    if (capasity == 0)
    {
        return false;
    }
    
    size_t newCapasity = this->capasity * 2; 

    T* newArr = allocate(newCapasity);

    if (!newArr)
    {
        return false;
    }
    
    for (size_t i = 0; i < this->size; i++) {
       new (newArr + i) T(arr[i]);
    }
    
    destroy_elements();
    
    free_memory();

    capasity = newCapasity;
    arr = newArr;

    return true;
}

template<typename T>
void Vec<T>::reserve(size_t cap){
    
    if (cap <= capasity)
    {
        return;
    }
    
    T* newArr = allocate(cap);

    if (!newArr)
    {
        return;
    }
    
    for (size_t i = 0; i < size; i++)
    {
        new (newArr + i) T(arr[i]);
    }

    destroy_elements();
    free_memory();

    arr = newArr;
    capasity = cap;
    
}

template<typename T>
void Vec<T>::add(const T& item) {

    if (capasity == 0 || !(arr))
    {
        return;
    }

    if (this->size == this->capasity) {
        if (!resize())
        {
            return;
        }
    }

    new (arr + size) T(item);
    this->size++;
}

template<typename T>
void Vec<T>::add(T&& item){

    if (capasity == 0 || !(arr))
    {
        return;
    }

    if (this->size == this->capasity) {
        if (!resize())
        {
            return;
        }
        
    }

    new (arr + size) T(std::move(item));
    this->size++;
}

template<typename T>
template<typename... Args>
void Vec<T>::add_all(Args... args){
    static_assert((std::is_same_v<T, Args> && ...), "All arguments must have the same type as T");

    if (capasity == 0 || !(arr))
    {
        return;
    }

    while (size + sizeof...(Args) > capasity) {
        if (!resize())
        {
            return;
        }
    }
    
    (((new (arr + size) T(args)), this->size++), ...);
}

template<typename T>
const T& Vec<T>::getByIndex(size_t index) const {
    if (index >= 0 && index < size)
    {
        return this->arr[index];
    }
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
const T& Vec<T>::operator[](size_t index)const{
    return this->arr[index];
}

template<typename T>
bool Vec<T>::is_all(bool(*checkFunc)(const T&)){
    for (size_t i = 0; i < this->size; i++){
        if (!checkFunc(arr[i]))
        {
            return false;
        }
    }
    return true;
}

template<typename T>
bool Vec<T>::is_empty()const{
    return size == 0;
}

template<typename T>
template<typename Func>
void Vec<T>::applyAll(Func func){
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = func(arr[i]);
    }
}

template<typename T>
T* Vec<T>::begin(){
    return arr;
}

template<typename T>
T* Vec<T>::end(){
    return arr + size;
}

#endif