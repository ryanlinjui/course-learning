#include <stdint.h>
#include <stdio.h>

void k_print(int64_t n){
    int64_t half_k=n/2+1;
    for(int i=0; i<half_k; i++){
        for(int j=0; j<half_k-i;j++){
            if(j==0||j==half_k-i-1){
                printf("*");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
    for(int i=0; i<half_k; i++){
        if(i==0){continue;}
        for(int j=0; j<i+1;j++){
            if(j==0||j==i){
                printf("*");
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
    }
}