#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
    double year=0,sigma_x=0,sigma_y=0,sigma_xy=0,sigma_x2=0,temperature=0,a=0,b=0,n=0;
    printf("$ ./hw0305\n");
    while (1){
        printf("Please enter the year: ");
        scanf("%lf",&year);
        if(year==-1){
            if(n<=1){
                printf("The amount of data is not enough to predict.\n");
                exit(0);
            }
            break;
        }
        if(year<1900){
            printf("Invalid Input!!\n");
            exit(0);
        }
        printf("Temperature: ");
        scanf("%lf",&temperature);
        if(temperature==-1){
            if(n<=1){
                printf("The amount of data is not enough to predict.\n");
                exit(0);
            }
            break;
        }
        if(temperature<-273.15){
            printf("Invalid Input!!\n");
            exit(0);
        }
        n++;
        sigma_x += year;
        sigma_y += temperature;
        sigma_xy += year*temperature;
        sigma_x2 += year*year;
    }
    a=(n*sigma_xy-sigma_x*sigma_y)/(n*sigma_x2-sigma_x*sigma_x);
    b=(sigma_y-a*sigma_x)/n;
    printf("Please enter the prediction year: ");
    scanf("%lf",&year);
    temperature=a*year+b;
    printf("Temperature: %.4lf\n",(double)((int)((temperature* 10000) + 0.5) / 10000.0));
    return 0;
}
