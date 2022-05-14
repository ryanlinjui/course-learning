#pragma once
#include "cstd.h"

// only support local variable (stack)
#define get_array_length(array) (sizeof(array)/sizeof(array[0])) 

// int array reverse
void int_arr_reverse(uint32_t **arr, uint32_t n)
{
    for (int low = 0, high = n - 1; low < high; low++, high--)
    {
        int32_t temp = (*arr)[low];
        (*arr)[low] = (*arr)[high];
        (*arr)[high] = temp;
    }
}

// get array max value

// get array min value

// check array's value

// check value is in array