#ifndef ARR_STACK_H
#define ARR_STACK_H

#include<cstddef>

template<typename T, size_t size>
class Arr_stack
{
    T arr[size];

public:

    T& operator[](size_t index){
        return arr[index];
    }
};


#endif