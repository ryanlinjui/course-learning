#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "mirror.h"

int main()
{
    printf("$ ./hw0601\n");
    double x1=0, y1=0, x2=0, y2=0;
    while(1)
    {
        printf("x1,y1,x2,y2: ");
        scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
        set_line(x1, y1, x2, y2);
        double a=0,b=0,c=0,d=0;
        printf("a,b: ");
        scanf("%lf %lf",&a,&b);
        printf("return:%d\n",get_mirror(a,b,&c,&d));
        printf("result:(%lf,%lf)\n",c,d);
    }
    return 0;
}