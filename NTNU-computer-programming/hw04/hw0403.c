#include <stdio.h>
#include <stdint.h>
#include "triangle.h"

int main()
{
    int option=0;
    double x=0,y=0;
    printf("$ ./hw0403\n");
    while(1){
        scanf("%d",&option);
        if(option==1){
            scanf("%lf %lf",&x,&y);
            printf("%d\n",set_1_point(x,y));
        }
        else if(option==2){
            scanf("%lf %lf",&x,&y);
            printf("%d\n",set_2_point(x,y));
        }
        else if(option==3){
            scanf("%lf %lf",&x,&y);
            printf("%d\n",set_3_point(x,y));
        }
        else if(option==4){
            printf("%d\n",check());
        }
        else if(option==5){
            printf("%lf\n",get_perimeter());
        }
        else if(option==6){
            printf("%lf\n",get_area());   
        }
        else if(option==7){
            printf("%lf\n",get_1_degree());   
        }
        else if(option==8){
            printf("%lf\n",get_2_degree());
        }
        else if(option==9){
            printf("%lf\n",get_3_degree());
        }
        else if(option==10){
            printf("%lf\n",get_inscribed_center_x());
        }
        else if(option==11){
            printf("%lf\n",get_inscribed_center_y());
        }
        else if(option==12){
            printf("%lf\n",get_inscribed_center_area());
        }
        else if(option==13){
            printf("%lf\n",get_circumscribed_center_x());
        }
        else if(option==14){
            printf("%lf\n",get_circumscribed_center_y());
        }
        else if(option==15){
            printf("%lf\n",get_circumscribed_center_area());
        }
    }
    return 0;
}