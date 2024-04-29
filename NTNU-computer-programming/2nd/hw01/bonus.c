#include <stdio.h>
#include <string.h>
#include <errno.h>

int main()
{
    for (int i = -1; i < 108; i++)
    {
        printf("strerror(%d): %40s      ",i,strerror(i));
        if(!(i%3))
        {
            printf("\n");
        }
    }
    printf("\n\n================================================");
    printf("\nCurrently errno nnumber:%d\n",errno);
    perror("Custom String");
    printf("================================================\n");
    return 0;
}