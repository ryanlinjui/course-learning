#include <stdio.h>
#include <stdint.h>

int main()
{
    int32_t n1=0,n2=0,sum=0;
    printf("$ ./hw0102\n");
    printf("Please enter the first  number: ");
    scanf("%d",&n1);
    printf("Please enter the second number: ");
    scanf("%d",&n2);
    sum = n1 + n2;
    printf("   %d %d %d\n",n1/100,(n1%100)/10,n1%10);
    printf("+) %d %d %d\n",n2/100,(n2%100)/10,n2%10);
    printf("--------\n");
    if(sum>=1000)
    {
        printf(" %d %d %d %d\n",sum/1000,(sum%1000)/100,(sum%100)/10,sum%10);
    }
    else
    {
        printf("   %d %d %d\n",sum/100,(sum%100)/10,sum%10);
    }
    return 0;
}
