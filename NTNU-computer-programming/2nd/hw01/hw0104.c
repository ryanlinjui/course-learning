#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mystring.h"

int main()
{   
    char *unit = malloc(10);
    char *str = malloc(100);
    fgets(unit,10,stdin);
    if(unit[0] == '1')
    {
        char c = '0';
        fgets(str,100,stdin);
        scanf("%c", &c);
        char *re_str = mystrchr(str,(int)c);
        printf("Orginal String: %s\n",str);
        printf("Character: %c\n",c);
        printf("mystrchr: %s\n",re_str);
        printf("location: %d\n",re_str-str);
    }
    else if(unit[0] == '2')
    {
        char c = '0';
        fgets(str,100,stdin);
        scanf("%c", &c);
        char *re_str = mystrrchr(str,(int)c);
        printf("Orginal String: %s\n",str);
        printf("Character: %c\n",c);
        printf("mystrrchr: %s\n",re_str);
        printf("location: %d\n",re_str-str);
    }
    else if(unit[0] == '3')
    {
        char *a = malloc(100);
        fgets(str,100,stdin);
        fgets(a,100,stdin);
        size_t location = mystrspn(str,a);
        printf("Orginal String: %s\n",str);
        printf("Accept: %s\n",a);
        printf("mystrspn: %u\n",location);
        free(a);
    }
    else if(unit[0] == '4')
    {
        char *r = malloc(100);
        fgets(str,100,stdin);
        fgets(r,100,stdin);
        size_t location = mystrcspn(str,r);
        printf("Orginal String: %s\n",str);
        printf("Reject: %s\n",r);
        printf("mystrcspn: %u\n",location);
        free(r);
    }
    else if(unit[0] == '5')
    {
        char *a = malloc(100);
        fgets(str,100,stdin);
        fgets(a,100,stdin);
        char *re_str = mystrpbrk(str,a);
        printf("Orginal String: %s\n",str);
        printf("Accept: %s\n",a);
        printf("mystrpbrk: %c\n",*re_str);
        printf("location: %d\n",re_str-str);
        free(a);
    }
    else if(unit[0] == '6')
    {
        char *n = malloc(100);
        fgets(str,100,stdin);
        fgets(n,100,stdin);
        char *re_str = mystrstr(str,n);
        printf("Orginal String: %s\n",str);
        printf("Needle: %s\n",n);
        printf("mystrstr: %s\n",re_str);
        free(n);
    }
    else if(unit[0] == '7')
    {
        char *match = malloc(100);
        fgets(str,100,stdin);
        fgets(match,100,stdin);
        char *token = mystrtok(str,match);
        printf("Orginal String: %s\n",str);
        for(int i = 0; token!=NULL; i++)
        {
            printf("%d: %s\n",i,token);
            token = mystrtok(NULL,match);
        }
        free(match);
    }
    free(str);
    return 0;
}