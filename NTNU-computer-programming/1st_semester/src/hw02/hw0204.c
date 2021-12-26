#include <stdio.h>
#include <stdint.h>

int main()
{
    int64_t count=0,service=0,delivery=0;
    float price[4][3] = {{3.4,1.4,1.1},{3.8,2.0,1.2},{4.2,2.3,1.5},{4.6,2.6,2.0}};
    printf("$ ./hw0204\n");
    printf("Word Count\n");
    printf("  Please enter the word count : ");
    scanf("%lld",&count);
    if(count<0)
    {
        printf("ERROR");
        return 0;
    }
    printf("Service Level\n");
    printf("  1) Advanced service\n");
    printf("  2) Standard service\n");
    printf("  3) Basic service\n");
    printf("  Your choice : ");
    scanf("%lld",&service);
    if(service!=1||service!=2||service!=3)
    {
        printf("ERROR");
        return 0;
    }
    printf("Delivery Time\n");
    printf("  1) Economic\n");
    printf("  2) Standard\n");
    printf("  3) Fast\n");
    printf("  4) Deadline\n");
    printf("  Your choice : ");
    scanf("%lld",&delivery);
    if(delivery!=1||delivery!=2||delivery!=3||delivery!=4)
    {
        printf("ERROR");
        return 0;
    }
    count *= price[delivery-1][service-1];     
    if(service==1&&count>=2000)
    {
       count *= 0.75;
    }
    else if(service==2&&count>=6000)
    {
        count *= 0.9;
    }
    else if(service==3&&count>=6000)
    {
        count *=0.95;
    }
    printf("Proofreading fee --> %lld\n",count);
    return 0;
}
