#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

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
                printf("")
            }
        }
    }

    

    return 0;
}
