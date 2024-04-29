#include <stdlib.h>
#include <string.h>

char *mystrtok_r(char *str, const char *delim, char **saveptr)
{
    static char str_db[10000000];
    static int32_t start,len_str;
    if(str!=NULL)
    {
        strcpy(str_db,str);
        start=0;
        len_str = strlen(str+start)-1;
        for(int i=0;i<len_str;i++)
        {
            for(int j=0;j<strlen(delim)-1;j++)
            {
                if(str_db[i]==delim[j])
                {
                    str_db[i]=0;
                }
            }
        }
    }
    else
    {
        do
        {
            start += strlen(str_db+start)+1;
        }while(strlen(str_db+start)==0);
    }
    return (start>=len_str) ? NULL : str_db+start;
}