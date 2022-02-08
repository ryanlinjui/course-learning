#include <stdint.h>
#include <stdio.h>

uint64_t mod_num[100];

int32_t ext_euclidean( uint32_t a, uint32_t b, uint32_t *c )
{
    if(a<b||b==0)
    {
        return -1;
    }
    uint32_t origin_a = a;
    uint32_t origin_b = b;
    uint64_t num=0;
    while(1) 
    {
        if(b==0)
        {
            if(a==1) //co-prime
            {
                uint64_t l_ans = 1;
                uint64_t ans = mod_num[num-2];
                uint64_t _ans = 1;
                for(int i=2;i<num;i++)
                {
                    _ans = ans;
                    ans = (ans*mod_num[num-i-1])+l_ans;
                    l_ans = _ans;
                }
                if(num%2==0)
                {
                    ans = origin_a - ans;
                }
                *c= *(&ans);
                return 1;
            }
            *c=*(&a);
            return 0;
        }
        int d=a/b;
        mod_num[num] = d;
        num++;
        a-=d*b;
        int temp = a;
        a=b;
        b=temp;
    }
}