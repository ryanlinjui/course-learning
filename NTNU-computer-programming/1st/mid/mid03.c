#include <stdio.h>
#include <stdint.h>
#include <math.h>

int main()
{
    int64_t layer=0;
    double angle=0,shift=0;
    printf("$ ./mid03\n");
    printf("Incudence angle: ");
    scanf("%lf",&angle);
    printf("How many layers: ");
    scanf("%ld",&layer);
    double r=0,h=0;
    if(layer<0||r<0||h<0){
        printf("ERROR\n");
        return 0;
    }

    for(int i=0;i<layer;i++){
        printf("Layer %d's refractive index: ",i+1);
        scanf("%lf",&r);
        printf("Layer %d's height: ",i+1);
        scanf("%lf",&h);
        shift += sqrt((r*r)+(h*h))*sin(3.1415926*(angle/180));
    }
    printf("The shift: %f",shift);
    return 0;
}
