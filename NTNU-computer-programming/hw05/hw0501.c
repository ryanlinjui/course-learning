#include <stdio.h>
#include <stdint.h>
#include "poker.h"

int main()
{
    printf("$ ./hw0501\n");
    int8_t poker_card[13] = {12,26,6,2,13,5,52,4,8,7,34,16,44};
    big_two_sort(poker_card);
    return 0;
}