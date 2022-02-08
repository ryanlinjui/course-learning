#include <stdint.h>
#include <stdio.h>

int32_t big_two_poker_level[52]={
    45,49,1,5, 9,13,17,21,25,29,33,37,41,
    46,50,2,6,10,14,18,22,26,30,34,38,42,
    47,51,3,7,11,15,19,23,27,31,35,39,43,
    48,52,4,8,12,16,20,24,28,32,36,40,44
};

#define btpl big_two_poker_level

int32_t big_two_sort( int8_t cards[] )
{
    //check error
    for(int i=0;i<13;i++)
    {
        if(cards[i]<1||cards[i]>52)
        {
            return -1;
        }
        for(int j=0;j<i;j++)
        {
            if(cards[i]==cards[j])
            {
                return -1;
            }
        }
    }

    //main
    for(int i=0;i<13-1;i++)
    {
        for(int j=i+1;j<13;j++)
        {
            if(btpl[cards[i]-1]>btpl[cards[j]-1])
            {
                int temp=cards[j];
                cards[j]=cards[i];
                cards[i]=temp;
            }
        }
    }
    printf("Sorted Results:");
    for(int i=0;i<13;i++)
    {
        printf(" %d",cards[i]);
    }
    return 0;
}