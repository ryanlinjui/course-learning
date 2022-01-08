#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

double eq_a=0,eq_b=0,eq_c=0;

int main()
{
    printf("$ ./fin01\n");

    int32_t p[5][2];

    for (int i=0; i<5;i++)
    {
        printf("Please enter P%"PRId32": ",i+1);
        scanf("%"SCNu32",%"SCNu32,&p[i][0],&p[i][1]);
        if(i>0)
        {
            if((p[i][0]==p[i-1][0])&&(p[i][1]==p[i-1][1]))
            {
                printf("This is not a pentagon\n");
                exit(0);
            }
            if(i==1)
            {
                eq_a = 1/((double)p[i][0]-(double)p[i-1][0]);
                eq_b = -(1/((double)p[i][1]-(double)p[i-1][1]));
                eq_c = -(-(double)p[i-1][1]/((double)p[i][1]-(double)p[i-1][1]))+(-(double)p[i-1][0]/((double)p[i][0]-(double)p[i-1][0]));
            }
        }
        if(i>1)
        {
            double _eq_a = 1/((double)p[i][0]-(double)p[i-1][0]);
            double _eq_b = -(1/((double)p[i][1]-(double)p[i-1][1]));
            double _eq_c = -(-(double)p[i-1][1]/((double)p[i][1]-(double)p[i-1][1]))+(-(double)p[i-1][0]/((double)p[i][0]-(double)p[i-1][0]));
            if((eq_a==_eq_a)&&(eq_b==_eq_b)&&(eq_c==_eq_c))
            {
                printf("This is not a pentagon\n");
                exit(0);
            }
            eq_a = _eq_a;
            eq_b = _eq_b;
            eq_c = _eq_c;
        }
    }

    double area = 0;
    area = ( ((double)p[0][0]*(double)p[1][1]-(double)p[1][0]*(double)p[0][1])+
            ((double)p[1][0]*(double)p[2][1]-(double)p[2][0]*(double)p[1][1])+
            ((double)p[2][0]*(double)p[3][1]-(double)p[3][0]*(double)p[2][1])+
            ((double)p[3][0]*(double)p[4][1]-(double)p[4][0]*(double)p[3][1])+
            ((double)p[4][0]*(double)p[0][1]-(double)p[0][0]*(double)p[4][1])
            )/2;
    if(area==0)
    {
        printf("This is not a pentagon\n");
        exit(0);   
    }
    printf("%lf\n",area);
    return 0;
}
