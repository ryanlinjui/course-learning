#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main()
{
    int32_t x1=0,x2=0,y1=0,y2=0;
    int64_t perimeter=0,area=0;
    printf("$ ./hw0202\n");
    printf("First point (x,y):");
    scanf("%d,%d",&x1,&y1);
    printf("Second point (x,y):");
    scanf("%d,%d",&x2,&y2);
    if(x1==x2||y1==y2)
    {
        printf("ERROR\n");
        return 0;
    }
    perimeter=(abs(x1-x2)+abs(y1-y2))*2;
    area=abs(x1-x2)*abs(y1-y2);
    printf("Perimeter --> %lld\n",perimeter);
    printf("Area --> %lld\n",area);
    return 0;
}
