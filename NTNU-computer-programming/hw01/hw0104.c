#include <stdio.h>
#include <stdint.h>

int main()
{
    float s=0,v_0=0,t=0,a=0;
    printf("$ ./hw0104\n");
    printf("v_0: ");
    scanf("%f",&v_0);
    printf("a: ");
    scanf("%f",&a);
    printf("t: ");
    scanf("%f",&t);
    s = (v_0*t) + (a*t*t)/2;
    printf("--> s = %f\n",s);
    return 0;
}
