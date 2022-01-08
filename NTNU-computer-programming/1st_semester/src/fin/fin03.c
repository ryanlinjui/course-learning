#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include "frac.h"

int main()
{
    int32_t f=0,x=0,y=0,a=0,b=0,c=0,d=0;
    while(1)
    {
        printf("f: ");
        scanf("%"SCNu32, &f);
        printf("a b c d: ");
        scanf("%"SCNu32" %"SCNu32" %"SCNu32" %"SCNu32, &a,&b,&c,&d);
        
        if(f==-1)
        {
            printf("88\n");
            exit(0);
        }
        if(f==0)
        {
            printf("add: %"PRId32"\n",frac_add(&x,&y,a,b,c,d));
        }
        else if(f==1)
        {
            printf("del: %"PRId32"\n",frac_del(&x,&y,a,b,c,d));
        }
        else if(f==2)
        {
            printf("mul: %"PRId32"\n",frac_mul(&x,&y,a,b,c,d));
        }
        else if(f==3)
        {
            printf("div: %"PRId32"\n",frac_div(&x,&y,a,b,c,d));
        }
        printf("result: x=%"PRId32",y= %"PRId32"\n",x,y);
    }
    return 0;
}
