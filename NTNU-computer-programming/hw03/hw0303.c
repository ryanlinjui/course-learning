//1. input integers的範圍為32bit整數。

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

void start();
void s1();
void s2();
void s3();
void s4();
void s5();
void s6();
void final();
void input_num();
int64_t num=0;

int main()
{
    printf("$ ./hw0303\n");
    start();
    return 0;
}

void input_num(){
    printf("Please enter an integer: ");
    scanf("%ld",&num);
    if(num<-2147483648||num>2147483648-1){
        printf("Invalid Input!!\n");
        exit(0);
    }
}

void start(){
    while(1){
        printf("Start\n");
        input_num();
        if(num==10||num==35){
            s1();
            return;
        }
        else if(num==11){
            s3();
            return;
        }
        else if(num==20||num==78){
            s5();
            return;
        }
    }
}

void s1(){
    while(1){
        printf("S1\n");
        input_num();
        if(num==19){
            s2();
            return;
        }
        else if(num==12||num==36){
            s6();
            return;
        }
    }
}

void s2(){
    while(1){
        printf("S2\n");
        input_num();
        if(num==43){
            continue;
        }
        else if(num==99){
            final();
            return;
        }
        else{
            start();
            return;
        }
    }
}

void s3(){
    while(1){
        printf("S3\n");
        input_num();
        s4();
        return;
    }
}

void s4(){
    while(1){
        printf("S4\n");
        input_num();
        s6();
        return;
    }
}
void s5(){
    while(1){
        printf("S5\n");
        input_num();
        if(num==1){
            s4();
            return;
        }
        else if(num==2){
            s6();
            return;
        }
        else{
            start();
            return;
        }
    }
}
void s6(){
    while(1){
        printf("S6\n");
        input_num();
        if(num==108){
            final();
            return;
        }
        else{
            s5();
            return;
        }
    }
}
void final(){
    printf("Final\n");
    return;
}

