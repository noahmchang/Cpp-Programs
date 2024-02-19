#ifndef QSORT_CPP
#define QSORT_CPP

#include "qsort.hpp"

/// @brief Sorts the elements in the range [first, last) using an order determined by comparator.
/// @tparam RandomAccessIter Random access iterator
/// @tparam Comparator function or callable object that can be called with 2 argument(s) and a return value convertible to bool
/// @param first the iterator referencing the first element in the range (included) to be sorted
/// @param last the iterator referencing the last element in the range (excluded) to be sorted
/// @param comparator when called, returns truthy value if the first argument should be placed before the second and falsy value otherwise
template <typename RandomAccessIter, typename Comparator>
void quick_sort(RandomAccessIter first, RandomAccessIter last, Comparator comparator)
{   
    //iterators are working as value not index??

    //If 0 or 1 elements
    if(first == last || first+1 == last){
        return;
    }
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    RandomAccessIter pivot = first + (std::rand() % std::distance(first, last));
    std::iter_swap(pivot, last - 1);
    //random pivot at the end
    pivot = last - 1;
    RandomAccessIter left_ptr = first;
    RandomAccessIter right_ptr = last - 2;
    while(true){
        while(left_ptr != last && comparator(*left_ptr, *pivot)){
            left_ptr++;
        }
        while(right_ptr != first && comparator(*pivot, *right_ptr)){
            right_ptr--;
        }
        if(left_ptr >= right_ptr){
            break;
        }
        std::iter_swap(left_ptr, right_ptr);
        left_ptr++;
        right_ptr--;
    }
    std::iter_swap(pivot, left_ptr);
    quick_sort(first, left_ptr, comparator);
    quick_sort(left_ptr+1, last, comparator);

    // auto partition = [&](int p, RandomAccessIter r) {
    //     T x = r;
    //     int i = p - 1;

    //     for(int j = p; j < r; ++j){
    //         if(comparator(A[j], x)){
    //             i = i + 1;
    //             std::swap(A[i], A[j]);
    //         }
    //     }
    //     std::swap(A[i + 1], A[r]);
    //     return i + 1;
    // };

    // if(comparator(first, last)){
    //     int pivot = partition(first, last);
    //     quick_sort(first, pivot-1, comparator);
    //     quick_sort(pivot+1, last, comparator);
    // }
    
}

#endif
