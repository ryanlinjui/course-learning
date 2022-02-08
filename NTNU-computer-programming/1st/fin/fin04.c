#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include "mem.h"

int main()
{
    size_t arr_size = 5;
    size_t *arr = (size_t *)malloc(arr_size*sizeof(size_t));
    size_t request_size = 10;
    arr = (size_t *)my_malloc(request_size,arr_size,arr);
    my_push(&arr,request_size,arr);
    my_free(arr,request_size);
    return 0;
}
