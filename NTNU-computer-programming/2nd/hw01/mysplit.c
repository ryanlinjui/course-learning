#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int mystrsplit(char ***pppList, int *pCounter , const char *pStr, const char *pSeparator)
{
    printf("here\n");
    fflush( stdout );

    // return 0;
    int32_t len_pStr = strlen(pStr)-1;
    int32_t len_pSeparator = strlen(pSeparator)-1;
    
    char pStr_cpy[1000];
    
    strcpy(pStr_cpy,pStr);
    *pCounter = 0;
    int32_t start=0;
    
    for(int i=0; i < len_pStr; i++)
    {
        for(int j=0; j < len_pSeparator; j++)
        {
            if(pStr[i] != pSeparator[j])
            {
                break;
            }
            i++;
            if(j==len_pSeparator-1)
            {
                pStr_cpy[i] = 0;
                pppList[*pCounter] = pStr_cpy+start;
                start = i;
                (*pCounter)++;
            }
        }
    }
    return 0;
}