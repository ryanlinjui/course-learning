#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

void start(int64_t,int64_t*);
void final(int64_t,int64_t*);
void s1(int64_t,int64_t*);
void s2(int64_t,int64_t*);
void s3(int64_t,int64_t*);
void s4(int64_t,int64_t*);
void s5(int64_t,int64_t*);
void s6(int64_t,int64_t*);

int64_t input()
{
    int64_t num;
    printf("Please enter an integer: ");
    scanf("%"SCNd64,&num);
    return num;
}

void start(int64_t num,int64_t* call_num)
{
    printf("Start\n");
    num = input();
    *call_num = (num==10||num==35)+3*(num==11)+5*(num==20||num==78);
}

void final(int64_t num,int64_t* call_num)
{
    printf("Final\n");
    exit(0);
}

void s1(int64_t num,int64_t* call_num)
{
    printf("S1\n");
    num = input();
    *call_num =  1+(2-1)*(num==19)+(6-1)*(num==12||num==36);
}

void s2(int64_t num,int64_t* call_num)
{
    printf("S2\n");
    num = input();
    *call_num =  2*(num==43)+7*(num==99);
}

void s3(int64_t num,int64_t* call_num)
{
    printf("S3\n");
    num = input();
    *call_num = 4;
}

void s4(int64_t num,int64_t* call_num)
{
    printf("S4\n");
    num = input();
    *call_num = 6;
}

void s5(int64_t num,int64_t* call_num)
{
    printf("S5\n");
    num = input();
    *call_num =  4*(num==1)+6*(num==2);
}

void s6(int64_t num,int64_t* call_num)
{
    printf("S6\n");
    num = input();
    *call_num =  5+2*(num==108);
}

int main()
{
    int64_t num=0,call_num=0;
    void (*func_arr[8])(int64_t,int64_t*) = {start,s1,s2,s3,s4,s5,s6,final};
    while(1)
    {   
        func_arr[call_num](num,&call_num);
    }
    return 0;
}