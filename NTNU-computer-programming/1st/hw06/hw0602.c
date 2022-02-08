#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "ext.h"

int main()
{
    printf("$ ./hw0602\n");
    while(1)
    {
        uint32_t a=0,b=0,c=0;
        printf("a,b:");
        scanf("%" SCNu32 " %" SCNu32,&a,&b);
        int32_t result = ext_euclidean(a,b,&c);
        printf("%" PRId32 ",%" PRId32 "\n",result,c);
    }
    return 0;
}