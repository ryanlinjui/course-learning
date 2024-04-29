#include <stdint.h>

double eq_a=0,eq_b=0,eq_c=0;

void set_line( double x1, double y1, double x2, double y2 )
{
    if(x1==x2&&y1==y2)
    {
        return;
    }
    //(Y-Y1)/(Y2-Y1)=(X-X1)/(X2-X1)
    eq_a = 1/(x2-x1);
    eq_b = -(1/(y2-y1));
    eq_c = -(-y1/(y2-y1))+(-x1/(x2-x1));
}

int32_t get_mirror( double a, double b, double *c, double *d )
{
    if(eq_a==0&&eq_b==0&&eq_c==0)
    {
        return -1;
    }
    double t = (eq_a*a+eq_b*b+eq_c)/(eq_a*eq_a+eq_b*eq_b);
    *c = a-2*eq_a*t;
    *d = b-2*eq_b*t;
    return 0;
}