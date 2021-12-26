#include <stdio.h>
#include <stdlib.h>
#include "euqivalent_r.h"

double r=0,ans=0;
int n=0;

void input(){
    printf("Please enter the resistance (1-100): ");
    scanf("%lf",&r);
    if(r<1||r>100){
        printf("Invalid Input!!!");
        exit(0);
    }
    printf("Please enter n (1-100): ");
    scanf("%d",&n);
    if(n<1||n>100){
        printf("Invalid Input!!!");
        exit(0);
    }
}

int main()
{
    printf("$ ./hw0404\n");
    input();
    ans = calculate(r,n);
    printf("Ans: %.1lf\n",ans);
    return 0;
}