#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "mymem.h"

#define AC_COLOR "\x1B[0;33m"
#define WR_COLOR "\x1B[0;30m"

int main()
{
    size_t test_case[10][2] = {{94,255},
                            {10,10},
                            {0,1},
                            {0,0},
                            {36,15},
                            {942,55},
                            {2022,2021},
                            {7,1},
                            {100,0},
                            {1,0}};
    for (int i=0;i<10;i++)
    {
        int64_t before = test_case[i][0];
        int64_t after = test_case[i][1];
        printf("Testcase(%2"PRId32"): before= %4"PRId64", after= %4"PRId64" --Result: ",i+1,before,after);       
        int64_t *arr = malloc(before*sizeof(int64_t));
        my_realloc((void*)(&arr),before,after);
        printf("arr:%p\n",&arr);
        if(sizeof(arr)==after)
        {
            printf("AC\n");
        }
        else
        {
            printf("WR\n");
        }
        free(arr);
    }
    
    return 0;
}