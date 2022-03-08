#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysplit.h"
#define num 100
int main()
{   
    char **pppList = (char**)malloc(num);
	for (int i = 0; i < num; i++) 
    {
		pppList[i] = malloc(num); 
    }
    int pCounter=0;
    char *pStr = malloc(100);
    char *pSeparator = malloc(100);
    fgets(pStr, 100, stdin);
    fgets(pSeparator, 100, stdin);
    printf("Orginal String: %s\n",pStr);
    printf("Separator: %s\n",pSeparator);
    printf("Result: %d\n",mystrsplit(&pppList,&pCounter,pStr,pSeparator));
    for(int i = 0; i<sizeof(pppList); i++)
    {
        printf("i=0: %s\n",pppList[i]);
    }
    printf("Total elements: %d\n",pCounter);
    free(pStr);
    free(pSeparator);
    return 0;   
}