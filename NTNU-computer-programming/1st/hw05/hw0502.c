#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "data.h"

int main()
{
    printf("$ ./hw0502\n");
    int32_t data_num;
    printf("Please input your number of data: ");
    scanf("%d", &data_num);
    if(data_num<1)
    {
        printf("Invalid Input!!\n");
        exit(0);
    }    
    printf("Please input %d data: ", data_num);
    int32_t input[data_num];    
    for(int i=0; i<data_num; i++)
    {   
        scanf("%d", &input[i]);
    }

    printf("mean: %lf\n",get_mean(input,data_num));
    printf("median: %lf\n",get_median(input,data_num));
    printf("mode: %d\n",get_mode(input,data_num));
    printf("stddev: %lf\n",get_stddev(input,data_num));
    return 0;
}