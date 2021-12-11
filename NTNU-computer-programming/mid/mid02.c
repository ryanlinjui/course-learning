#include <stdio.h>
#include <stdint.h>

int main()
{
    int64_t num=0,n=0,position=0,ans=0;
    printf("$ ./mid02\n");
    while(1){
        printf("Please enter the integer: ");
        scanf("%ld",&num);
        n++;
        if(num==0){
            break;
        }
        if((num==13||num==27||num==68)&&position==0){
            ans=num;
            position = n;
        }
        printf("Please enter the integer: ");
        scanf("%ld",&num);
        n++;
        if(num==0){
            break;
        }
        if((num==-5||num==19||num==103||num==27)&&position==0){
            ans=num;
            position = n;
        }
        printf("Please enter the integer: ");
        scanf("%ld",&num);
        n++;
        if(num==0){
            break;
        }
        if((num==-5||num==19||num==103||num==27)&&position==0){
            ans=num;
            position = n;
        }

        printf("Please enter the integer: ");
        scanf("%ld",&num);
        n++;
        if(num==0){
            break;
        }
        if((num==-33)&&position==0){
            ans=num;
            position = n;
        }
    }
    if(position==0){
        printf("None.\n");
    }
    else{
        printf("The first matching series is at position %ld, integer %ld.\n",position,ans);
    }
    return 0;
}
