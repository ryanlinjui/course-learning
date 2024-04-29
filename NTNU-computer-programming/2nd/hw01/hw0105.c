#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysplit.h"

#define num 100

int main()
{   
    char **ppList = NULL;//(char**)malloc(num);
	// for (int i = 0; i < num; i++) 
    // {
	// 	pppList[i] = malloc(num); 
    // }
    int pCounter=0;
    char *pStr = "123 213";
    char *pSeparator = " ";
    // fgets(pStr, 100, stdin);
    // fgets(pSeparator, 100, stdin);
    printf("Orginal String: %s\n",pStr);
    printf("Separator: %s\n",pSeparator);
    int a = mystrsplit(&ppList,&pCounter,pStr,pSeparator);
    //int a = 5;
    printf("Result: %d\n",a);
    /*
    for(int i = 0; i<sizeof(ppList); i++)
    {
        printf("i=0: %s\n",ppList[i]);
    }
    */
    printf("Total elements: %d\n",pCounter);
    //free(pStr);
    //free(pSeparator);
    return 0;   
}