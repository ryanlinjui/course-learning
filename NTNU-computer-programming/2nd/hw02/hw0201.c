#include <stdio.h>
#include "mymatch.h"

#define MAX_LEN 2048
#define a 2,2,2

void test(char *pStr,char *pPattern)
{
    printf("\n\n==========TESTCASE==========\n");
    char **pppList = NULL;
    int num = mymatch(&pppList, pStr,pPattern);
    printf("string: %s\npattern: %s\n",pStr,pPattern);
    // for(int i = 0; i < num; i++)
    // {
    //     printf("match: %s\n",pppList[i]);
    // }
    printf("total: %d\n",num);
}

int main()
{   
    test("ae","a?e");
    test("ace","a?e");
    // test("ache","a?e");
    // test("ae","a*e");
    // test("aaae","a*e");
    // test("baaae","a*e");
    // test("ace","a*e");
    // test("ache","a*e");
    // test("apple","a*e");
    return 0;
}