#ifndef FUNCS_H
#define FUNCS_H

#include<vector>
#include<iostream>



template<typename T>
void print(T val){
    std::cout << val << "\n";
}




template<typename T, typename Func>
void applyAll(std::vector<T>& arr, T(*func)(T)){
    for (auto &i : arr)
    {
        i = func(i);
    }
}

inline int add(int x, int y){
    return x + y;
}


#endif