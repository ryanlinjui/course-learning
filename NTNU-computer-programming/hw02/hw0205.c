#include <stdio.h>
#include <stdint.h>

int main()
{
    int32_t hcp=0,card=0;
    int32_t suit[4] = {0,0,0,0};
    printf("$ ./hw0205\n");
    for (int i=0; i<13;i++)
    {
        printf("%d",i+1);
        if (i==0)
        {
            printf("st card: ");
        }
        else if (i==1)
        {
            printf("nd card: ");
        }
        else if(i==2)
        {
            printf("rd card: ");
        }
        else if(i<=8)
        {
            printf("th card: ");
        }
        else
        {
            printf(" th card: ");
        }
        scanf("%d",&card);
        if(card<=0||card>=53){
            printf("ERROR");
            return 0;
        }
        if (card%13==1){
            hcp+=4;
        }
        else if(card%13==11){
            hcp+=3;
        }
        else if(card%13==12){
            hcp+=2;
        }
        else if(card%13==0){
            hcp+=1;
        }
        suit[(card-1)/13]+=1;
    }
    printf("---\n");
    printf("HCP: %d pts\n",hcp); //1.14,27,40 ==> 16pts(4 A Card)
    printf("Suit: %d-%d-%d-%d\n",suit[0],suit[1],suit[2],suit[3]); //2,1,1,1
    printf("The bidding choice : ");


    if(hcp>=22){
        printf("2♣");
    }
    else if(hcp>=13 && hcp<=21 && (suit[0]>=5 ||suit[1]>=5))
    {
        if(suit[0]>=suit[1]){
            printf("1♠");    
        }
        else{
            printf("1♡");
        }
    }
    else if(hcp>=16 && hcp<=18)
    {
        printf("1NT");
    }
    else if(hcp>=20&&hcp<=21)
    {
        printf("2NT");
    }
    else if(hcp>=13 && hcp<=21 && (suit[2]>=3 ||suit[3]>=3))
    {
        if(suit[2]>=suit[3]){
            printf("1♢");
        }
        else{
            printf("1♣");
        }
    }
    else if(hcp>=10 && hcp<=12 && (suit[0]>=7||suit[1]>=7||suit[2]>=7||suit[3]>=7))
    {
        for(int i=0; i<3;i++){
            if(suit[i]>=7)
            {
                if(i==0)
                {
                    printf("3♠");
                }
                else if(i==1)
                {
                    printf("3♡");
                }
                else if(i==2)
                {
                    printf("3♢");
                }
                else
                {
                    printf("3♣");
                }
            }
        }
    }
    else if (hcp>=10 && hcp<=12 && (suit[0]>=6||suit[1]>=6||suit[2]>=6))
    {
        for(int i=0; i<2;i++){
            if(suit[i]>=6){
                if(i==0){
                    printf("2♠");
                }
                else if(i==1){
                    printf("2♡");
                }
                else{
                    printf("2♢");
                }
            }
        }
    }
    else
    {
        printf("Otherwise");
    }
    printf("\n");
    return 0;
}
