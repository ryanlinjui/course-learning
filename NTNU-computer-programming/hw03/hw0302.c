//1. overflow case在這題的定義為結果會超過32bit可以表達的範圍為overflow

//1. 32bit整數是指int32_t，如果是無號的會額外說。
//2. 32bit可以表達的範圍包含int32_t和uint32_t，所以hw0302的overflow case是指超出-2147483648~4294967295這個範圍的數。

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    uint64_t n1=0,n2=0,sum=0;
    int64_t n1_0=0,n2_0=0,sum_0=0;
    printf("$ ./hw0302\n");
    printf("Please enter the first  number: ");
    scanf("%ld",&n1);
    printf("Please enter the second number: ");
    scanf("%ld",&n2);
    if(n1>pow(2,32)-1||n2>pow(2,32)-1){
        printf("Invalid Input!!\n");
        return 0;
    }
    sum = n1 + n2;
    if(sum>pow(2,32)-1){
        printf("Overflow happens\n");
        return 0;
    }
    if(n1==0){
        n1=1;
        n1_0=-1;
    }
    if(n2==0){
        n2=1;
        n2_0=-1;
    }
    if(sum==0){
        sum=1;
        sum_0=-1;
    }
    uint64_t n1_digit=(uint64_t)log10(n1)+1,n2_digit=(uint64_t)log10(n2)+1,sum_digit=(uint64_t)log10(sum)+1;
    printf("  ");
    for(int i=0; i<sum_digit-n1_digit;i++){
        printf("  ");
    }
    while(n1_digit--)
    {
        if(n1_0==-1){
            printf(" %d",0);
        }
        else{
            printf(" %ld",(n1%(uint64_t)pow(10,n1_digit+1))/(uint64_t)pow(10,n1_digit));
        }
        
    }
    printf("\n+)");
    for(int i=0; i<sum_digit-n2_digit;i++){
        printf("  ");
    }

    while(n2_digit--)
    {
        if(n2_0==-1){
            printf(" %d",0);
        }
        else{
            printf(" %ld",(n2%(uint64_t)pow(10,n2_digit+1))/(uint64_t)pow(10,n2_digit));
        }
    }
    
    printf("\n--");
    
    for(int i=0;i<sum_digit;i++)
    {
        printf("--");
    }
    printf("\n  ");
    while(sum_digit--)
    {
        if(sum_0==-1){
            printf(" %d",0);
        }
        else{
            printf(" %ld",(sum%(uint64_t)pow(10,sum_digit+1))/(uint64_t)pow(10,sum_digit));
        }
    }
    printf("\n");
    return 0;
}
