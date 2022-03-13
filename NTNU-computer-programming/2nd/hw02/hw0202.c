#include <stdio.h>
#include <string.h>

#define MAX_LEN 1000 

int main()
{
    char *num = malloc(MAX_LEN);
    printf("$ ./hw0202\n");
    printf("Please enter a floating-point number (double precision): ");
    fgets(num, MAX_LEN, stdin);
    for (int i = 0; i <strlen(num)-1; i++)
    {
        
    }
    
    return 0;
}