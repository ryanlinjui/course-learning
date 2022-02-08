#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main()
{
    int64_t num1=0,num2=0,result=0,num_total=0,num=0;
    int64_t n1=0,n2=0,n3=0,n4=0,n5=0,n6=0,n7=0,n8=0,n9=0,n10=0;
    printf("$ ./mid01\n");
    printf("Please enter the 1st integer: ");
    scanf("%ld",&num1);
    if (num1<0){
        printf("ERROR\n");
        return 0;
    }
    printf("Please enter the 2st integer: ");
    scanf("%ld",&num2);
    if (num2<0){
        printf("ERROR\n");
        return 0;
    }
    if(num1==0&&num2==0){
        result=0;
    }
    else{
        int64_t num1_log10=log10(num1),num2_log10=log10(num2);
        if(num1==0){
            num1_log10=0;
        }
        if(num2==0){
            num2_log10=0;
        }
        num_total=num1_log10+num2_log10+2;
        
        
        if(num1_log10>num2_log10){
            if(num2==0){
                num=num1*10;
            }
            else{
                num = num1*pow(10,num1_log10+1-(num1_log10-num2_log10))+num2; 
            }
        }
        else if(num1_log10<num2_log10){
            if(num1==0){
                num=num2*10;
            }
            else{
                num = num2*pow(10,num2_log10+1-(num2_log10-num1_log10))+num1;
            }
        }
        else{
            num=num1*pow(10,num1_log10+1)+num2;
            if(num2==0){
                num=num1*10;
            }
            if(num1==0){
                num=num2*10;
            }
        }
        for(int i=0,last_num=0;i<num_total;i++){
            int64_t big=-1;
            for(int j=1;j<=num_total;j++){
                int64_t num_d =(num%(int64_t)pow(10,j))/(int64_t)pow(10,j-1);
                if(num_d>big){
                    big=num_d;
                    last_num = j;
                }
            }
            num=num-(num%(int64_t)pow(10,last_num))+(num%(int64_t)pow(10,last_num-1));
            result += big;
            result *= 10;
        }
    }
    printf("Result: %ld\n",(int64_t)result/10);
    return 0;
}
