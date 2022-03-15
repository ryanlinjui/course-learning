#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

char* pattern_filter(const char *pattern)
{
    int32_t len_pattern = strlen(pattern);
    char* pattern_cpy = malloc(len_pattern);

    for (int i = 0,skip=1; i < len_pattern; i++)
    {
        if(pattern[i] == '*')
        {
            if(skip)
            {
                continue;
            }
            skip = 1;
        }
        else
        {
            skip = 0;
        }
        pattern_cpy[i] = pattern[i];
    }
    pattern_cpy[1] = 0;
    return pattern_cpy;
}


int mymatch(char ***pppList, const char *pStr, const char *pPattern)
{
    char *pattern = pattern_filter(pPattern);
    printf("cpy:%s\n", pattern);
    return 0;
    int32_t len_pStr = strlen(pStr);
    int32_t len_pPattern = strlen(pPattern);
    int32_t count = 0;

    for(int i = 0; i < len_pStr; i++)
    {
        for(int j = i; j < len_pStr; j++)
        {
            for (int p_Pstr = i; p_Pstr <= j; p_Pstr++)
            {
                for(int p_pPattern=0; p_Pstr <= len_pPattern; p_Pstr++)
                {
                    if(pStr[p_Pstr] == pPattern[p_pPattern])
                    {

                    }
                }
            }
        }
    }
    return count;
}