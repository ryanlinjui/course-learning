#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "polynomial.h"

void ERROR()
{
    printf("Invalid Input!!\n");
    exit(0);
}

int main()
{
    printf("$ ./hw0503\n");

    //input
    int64_t p1_degree=0,p2_degree=0;
    printf("Please enter p1 degree: ");
    scanf("%ld",&p1_degree);
    if(p1_degree<1||p1_degree>100)
    {
        ERROR();
    }
    int64_t p1_c[p1_degree+1];
    printf("Please enter p1 coefficients: ");
    for(int i=0;i<p1_degree+1;i++)
    {
        scanf("%ld",&p1_c[i]);
    }

    printf("Please enter p2 degree: ");
    scanf("%ld",&p2_degree);
    if(p2_degree<1||p2_degree>100)
    {
        ERROR();
    }
    int64_t p2_c[p2_degree+1];
    printf("Please enter p2 coefficients: ");

    for(int i=0;i<p2_degree+1;i++)
    {
        scanf("%ld",&p2_c[i]);
    }

    //main
    calculate_result(p1_c,p1_degree+1,p2_c,p2_degree+1);
    return 0;
}