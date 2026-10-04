#ifndef MY_STACK_H
#define MY_STACK_H

#include<cstddef>

template<typename T>
class My_Stack{

    size_t top;
    size_t capasity;
    size_t size;
    T* data;

public:

    My_Stack();
    My_Stack(size_t cap);
    ~My_Stack();
    void push(const T& val);
    T peek()const;
    T pop();
    void display();
};

template<typename T>
My_Stack<T>::My_Stack():top(0), capasity(16), size(0), data(new T[capasity]){}

template<typename T>
My_Stack<T>::My_Stack(size_t cap):top(0), capasity(cap), size(0), data(new T[capasity]){}

template<typename T>
My_Stack<T>::~My_Stack(){
    delete[] data;
}

template<typename T>
void My_Stack<T>::push(const T& val){
    if (size == capasity)
    {

        capasity *= 2;

        T* newData = new T[capasity];

        for (size_t i = 0; i < size; i++)
        {
            newData[i] = data[i];
        }

        delete[] data;

        data = newData;
        
    }

    data[top] = val;
    top++;
    size++;
}

template<typename T>
T My_Stack<T>::peek()const{
    return data[top];
}

template<typename T>
T My_Stack<T>::pop(){
    T toDelete = data[top];
    top--;
    size--;
    return toDelete;
}

template<typename T>
void My_Stack<T>::display(){
    if (size != 0)
    {
       for (size_t i = size - 1; i >= 0; i--)
        {
            std::cout << data[i] << "\n";
        }
    }
    
    
}

#endif