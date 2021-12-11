#include <stdio.h>
#include <stdint.h>

int main()
{
    uint16_t num=0;
    printf("$ ./hw0103\n");
    printf("Please enter an unsigned 16-bits number:");
    scanf("%hd",&num);
    printf("Before Flip:\n");
    printf("%d_10 = %.4x_16\n",num,num);
    printf("After  Flip:\n");
    uint16_t n1=num>>12,n2=(num>>4)&(15<<4),n3=(num<<4)&(15<<8),n4=(num<<12)&(15<<12);
    num = n1+n2+n3+n4;
    printf("%d_10 = %.4x_16\n",num,num);
    return 0;
}