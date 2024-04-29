#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

long double real_ans=0;

void authentication_max_n(){
    long double n=2,ans=0;
    while(1){
        ans=0;
        for(long double i = n;i>=2;i--){
            ans = 1/(1+1/(1+1/((2*i)+ans)));
        }
        ans = 2+1/(1+1/(2+ans));
        printf("n=%d,Answer: %.19Lf\n",(int)n,ans);
        if(ans==real_ans){
            printf("Close to n=%d\n",(int)n);
            exit(0);
        }
        n++;
    }
}


int main()
{
    long double n=0,ans=0;
    printf("$ ./hw0304\n");
    printf("Please enter n: ");
    scanf("%Lf",&n);
    if(n<2){
        printf("Invalid Input!!\n");
        exit(0);
    }
    for(;n>=2;n--){
       ans = 1/(1+1/(1+1/((2*n)+ans)));
    }
    ans = 2+1/(1+1/(2+ans));
    printf("Answer: %.19Lf\n",ans);
    real_ans = ans;
    //authentication_max_n();
    return 0;
}