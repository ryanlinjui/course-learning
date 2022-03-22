#include <stdio.h>
#include <stdlib.h>
#include "mymatch.h"

#define MAX_LEN 2048

void test(char *pStr,char *pPattern)
{
    printf("\n\n==========TESTCASE==========\n");
    char **pppList = NULL;
    int num = mymatch(&pppList, pStr,pPattern);
    printf("String: %s\nPattern: %s\n",pStr,pPattern);
    for(int i = 0; i < num; i++)
    {
        printf("Match: %s\n",pppList[i]);
    }
    printf("Total: %d\n",num);
}

int main()
{   
    test("ae","a?e");
    test("ace","a?e");
    test("ache","a?e");
    test("ae","a*e");
    test("aaae","a*e");
    test("baaae","a*e");
    test("ace","a*e");
    test("ache","a*e");
    test("apple","a*e");
    test("apple adse","a*e");
    test("app asd  asd","a*d");
    return 0;
}