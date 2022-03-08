#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"

int main()
{   
    char *str = malloc(100);
    char *str_ptr;
    fgets(str,100,stdin);
    printf("Orginal String: %s\n",str);
    for(int i = 0; i <= 37; i++)
    {
        int64_t l = mystrtol(str,&str_ptr,i);
        printf("(Base %d) Value:%ld Remain:%s",i,l,str_ptr);
    }    
    free(str);
    return 0;
}