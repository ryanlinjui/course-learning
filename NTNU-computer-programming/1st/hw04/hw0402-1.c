#include <stdio.h>
#include <stdlib.h>
#include "hanoi.h"

int disk_num=0;

void input(){
    printf("Please enter the disk number (2-20): ");
    scanf("%d",&disk_num);
    if(disk_num<2||disk_num>20){
        printf("Invalid Input!!\n");
        exit(0);
    }
}

int main()
{
    printf("$ ./hw0402-1\n");
    input();
    hanoi_recursive(disk_num,1,2,3,disk_num);
    return 0;
}
