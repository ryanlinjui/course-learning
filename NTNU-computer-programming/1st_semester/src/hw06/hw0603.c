#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

int8_t show_byte(int64_t *num,int64_t position)
{
    int8_t *val = (int8_t*)(num);
    return *(val + (int8_t)position);
}

void set_val(int64_t *num,int64_t position,int64_t new_val)
{

    int8_t *val = (int8_t*)(num);
    *(val + (8-(int8_t)position)) = ((int8_t)(new_val)) & 0xFF;
}

int main()
{
    printf("$ ./hw0603\n");
    int64_t num=0;
    printf("Please input an integer: ");
    scanf("%"SCNd64,&num);
    while(1)
    {
        printf("The integer: %"SCNd64"\n",num);
        for(int8_t i=1; i<=8;i++)
        {
            printf("(%"PRId32") 0x%02"PRIX8" ",i,show_byte(&num,8-i));
        }
        printf("\nPlease enter the position (1-8, 0: End): ");
        int64_t position=0;
        scanf("%"PRId64,&position);
        if(position<0||position>8)
        {
            printf("Invalid Input!!\n");
            exit(0);
        }
        if(position==0)
        {
            break;
        }
        printf("Please enter the new value (0-255): ");
        int64_t new_val = 0;
        scanf("%"SCNd64,&new_val);
        if(new_val>255||new_val<0)
        {
            printf("Invalid Input!!\n");
            exit(0);
        }
        set_val(&num,position,new_val);
        printf("---\n");
    }
    return 0;
}