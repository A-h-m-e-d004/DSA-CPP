#ifndef MY_ALGORITHMS_H
#define MY_ALGORITHMS_H

#include<cstddef>

namespace sort_algorithms {

    template<typename T, size_t size>
    void bubble_sort(T (&arr)[size]){
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size - i - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    T temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    template<typename T, size_t size>
    void selection_sort(T (&arr)[size]){
        for (size_t i = 0; i < size; i++)
        {
            size_t minNumIndex = i;
            for (size_t j = i + 1; j < size; j++)
            {
                if (arr[j] < arr[minNumIndex])
                {
                    minNumIndex = j;
                }
            }
            T temp = arr[i];
            arr[i] = arr[minNumIndex];
            arr[minNumIndex] = temp;
        }
        
    }

    template<typename T, size_t size>
    void insertion_sort(T (&arr)[size]){
        for (size_t i = 1; i < size; i++)
        {
            T key = arr[i];
            int j = static_cast<int>(i - 1);

            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }
}

namespace search_algorithms
{
    
    template<typename T, size_t size>
    constexpr bool linear_search(const T (&arr)[size], T value){
        bool result = false;
        for (size_t i = 0; i < size; i++)
        {
            if (arr[i] == value)
            {
                result = true;
                return result;
            }
        }
        return result;
    }


    template<typename T, size_t size>
    constexpr bool binary_search(const T (&arr)[size], T value){
        size_t low = 0;
        size_t high = size - 1;

        bool result = false;

        while (low <= high)
        {

            size_t middle = low + (high - low) / 2;

            if (arr[middle] == value)
            {
                result = true;
                return result;
            } else if (value < arr[middle]) {
                high = middle - 1;
            } else {
                low = middle + 1;
            }
        }
        return result;
    }

} // namespace search_algorithms



#endif