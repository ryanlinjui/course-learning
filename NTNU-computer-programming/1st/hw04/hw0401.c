#include <stdio.h>
#include <stdlib.h>
#include "k_function.h"

int64_t n=0;

void input(){
    printf("Please enter n (1-100, n must be odd): ");
    scanf("%ld",&n);
    if(n%2==0||n<2||n>100){
        printf("Invalid Input!!!");
        exit(0);
    }
}

int main()
{
    printf("$ ./hw0401\n");
    input();
    k_print(n);
    return 0;
}