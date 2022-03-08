#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

long int mystrtol(const char *nptr, char **endptr, int base)
{
    *endptr = nptr;
    if(base==1||base>36) return 0;
    char *upper_table = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *lower_table = "0123456789abcdefghijklmnopqrstuvwxyz";
    int64_t sum = 0,breakpoint=strlen(nptr)-1,constant=1,start=0,state=0;

    //start
    int32_t zero_mode = 0;
    int32_t space_mode = 0;
    int32_t loop_break = 1;
    int32_t base_mode = 1;
    for (int i=0; i<strlen(nptr)-1&&loop_break; i++)
    {
        if(i==0)
        {
            if(isspace((int)nptr[0])|(nptr[0]=='0'))
            {
                space_mode = isspace((int)nptr[0]);
                zero_mode = (nptr[0]=='0') ? 1 : 0;
                continue;
            }
        }
        if(isspace((int)nptr[i]))
        {
            if(space_mode)
            {
                continue;
            }
            start = i;
            break;
        }
        else if(nptr[0]=='0')
        {
            if(zero_mode)
            {
                continue;
            }
            start = i;
            break;
        }
        if(nptr[i]=='+'||nptr[i]=='-')
        {
            if(nptr[i]=='-')
            {
                constant *= -1;
            }
            continue;
        }
        if(base==0&&base_mode==1)
        {
            if(nptr[i]=='x'||nptr[i]=='X')
            {
                base_mode = 0;
                base = 16;
                continue;
            }
        }
        for(int j=0;j<base;j++)
        {   
            if((nptr[i]==upper_table[j])||(nptr[i]==lower_table[j]))
            {
                start = i;
                loop_break = 0;
                break;
            }
        }
    }

    //breakpoint
    for(int i=start,j; i<strlen(nptr)-1; i++)
    {
        for(j=0; j<base; j++)
        {   
            if((nptr[i]==upper_table[j])||(nptr[i]==lower_table[j]))
            {
                break;
            }
        }
        if(j==base)
        {
            breakpoint=i;
            break;
        }
    }
    printf("start: %d ",start);
    //result
    *endptr = nptr+breakpoint;
    for (int i = breakpoint-1; i >= start; i--)
    {
        for(int j=0; j<base; j++)
        {   
            if((nptr[i]==upper_table[j])||(nptr[i]==lower_table[j]))
            {
                sum += j*pow(base,breakpoint-i-1);
            }
        }
    }
    return sum*constant;
}

char *mystrchr(const char *s, int c)
{
    for(int i=0;i<strlen(s)-1;i++)
    {
        if(s[i]==(char)c)
        {
            return s+i;
        }
    }
    return NULL;
}

char *mystrrchr(const char *s, int c)
{
    for(int i=strlen(s)-1;i>0;i--)
    {
        if(s[i]==(char)c)
        {
            return s+i;
        }
    }
    return NULL;
}

size_t mystrspn(const char *s, const char *accept)
{
    size_t len_s = strlen(s)-1;
    size_t len_accept = strlen(accept)-1;
    for(int i=0;i<len_s;i++)
    {
        for(int j=0;j<len_accept;j++)
        {
            if(s[i]==accept[j])
            {
                break;
            }
            if(j==len_accept-1)
            {
                return i;
            }
        }
    }
    return 0;
}

size_t mystrcspn(const char *s, const char *reject)
{
    size_t len_s = strlen(s)-1;
    size_t len_reject = strlen(reject)-1;
    for(int i=0;i<len_s;i++)
    {
        for(int j=0;j<len_reject;j++)
        {
            if(s[i]==reject[j])
            {
                return i;
            }
        }
    }
    return 0;
}

char *mystrpbrk(const char *s, const char *accept)
{
    size_t len_s = strlen(s)-1;
    size_t len_accept = strlen(accept)-1;
    for(int i=0;i<len_s;i++)
    {
        for(int j=0;j<len_accept;j++)
        {
            if(s[i]==accept[j])
            {
                return s+i;
            }
        }
    }
    return s+len_s;
}

char *mystrstr(const char *haystack, const char *needle)
{
    size_t len_haystack = strlen(haystack)-1;
    size_t len_needle = strlen(needle)-1;
    for(int i=0;i<len_haystack;i++)
    {
        for(int j=0;j<len_needle;j++)
        {
            if(haystack[i+j]!=needle[j])
            {
                break;
            }
            if(j==len_needle-1)
            {
                return haystack+i;
            }
        }
    }
    return NULL;
}

char *mystrtok(char *str, const char *delim)
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