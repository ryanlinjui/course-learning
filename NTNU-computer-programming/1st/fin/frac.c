#include <stdint.h>

void simple(int64_t a, int64_t b,int64_t *aa,int64_t *bb)
{
    int a_nega = 0,b_nega = 0;
    if(a<0)
    {
        a = -a;
        a_nega = 1;
    }
    if(b<0)
    {
        b = -b;
        b_nega = 1;
    }

    if(a>b)
    {
        int i=2;
        while(i<a)
        {
            if((a%i==0) && (b%i==0))
            {
                
                a/=i;
                b/=i;
                i=2;
            }
            else
            {
                i++;
            }
        }
    }
    else
    {
        int i=2;
        while(i<b)
        {
            if((a%i==0) && (b%i==0))
            {
                
                a/=i;
                b/=i;
                i=2;
            }
            else
            {
                i++;
            }
        }
    }
    if(a_nega)
    {
        a = -a;
    }
    if(b_nega)
    {
        b = -b;
    }
    if(b==0)
    {
        a = 1;
    }
    if(b>0&&a<0)
    {
        b = -b;
        a = -a;
    }
    *aa = a;
    *bb = b;
}

int32_t frac_add( int32_t *x, int32_t *y,int32_t a, int32_t b, int32_t c, int32_t d )
{
    if(b==0||d==0)
    {
        return -1;
    }
    int64_t yy= b*d,xx=a*d+b*c;
    if(xx<0&&yy<0)
    {
        xx = -xx;
        yy = -yy;
    }
    simple(yy,xx,&yy,&xx);
    *x=xx;
    *y=yy;
    return 0;
}

int32_t frac_del( int32_t *x, int32_t *y,int32_t a, int32_t b, int32_t c, int32_t d )
{
    if(b==0||d==0)
    {
        return -1;
    }
    int64_t yy= b*d,xx=a*d-b*c;
    if(xx<0&&yy<0)
    {
        xx = -xx;
        yy = -yy;
    }
    simple(yy,xx,&yy,&xx);
    *x=xx;
    *y=yy;
    return 0;
}

int32_t frac_mul( int32_t *x, int32_t *y,int32_t a, int32_t b, int32_t c, int32_t d )
{
    if(b==0||d==0)
    {
        return -1;
    }
    int64_t yy= b*d,xx=a*c;
    if(xx<0&&yy<0)
    {
        xx = -xx;
        yy = -yy;
    }
    simple(yy,xx,&yy,&xx);
    *x=xx;
    *y=yy;
    return 0;
}

int32_t frac_div( int32_t *x, int32_t *y,int32_t a, int32_t b, int32_t c, int32_t d )
{
    if(b==0||c==0)
    {
        return -1;
    }
    int64_t yy= b*c,xx=a*d;
    if(xx<0&&yy<0)
    {
        xx = -xx;
        yy = -yy;
    }
    simple(yy,xx,&yy,&xx);
    *x=xx;
    *y=yy;
    return 0;
}