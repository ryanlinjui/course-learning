#include <stdio.h>
#include <stdint.h>

int main()
{
    int32_t a=0,b=0,c=0;
    int64_t judge=0;
    printf("$ ./hw0201\n");
    printf("Please enter a quadratic polynomial (a,b,c): ");
    scanf("%d,%d,%d",&a,&b,&c);
    judge=b*b-4*a*c;
    if(judge>0)
    {
        printf("Two distinct real roots.\n");
    }
    else if(judge==0)
    {
       printf("One real root.\n");
    }
    else
    {
        printf("No real roots.\n");
    }
    return 0;
}
