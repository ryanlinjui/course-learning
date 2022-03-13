#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int mymatch(char ***pppList, const char *pStr, const char *pPattern)
{
    int32_t len_pPattern = strlen(pPattern)-1;
    int32_t len_pStr = strlen(pStr)-1;
    int32_t count = 0;

    for(int i = 0; i < len_pStr; i++)
    {
        for(int j = 0; j < len_pPattern; j++)
        {
            
        }
    }
    return count;
}