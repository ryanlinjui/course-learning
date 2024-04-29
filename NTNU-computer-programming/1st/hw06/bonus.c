#include <stdio.h>
#include <stdint.h>

int main()
{
    printf("$ ./bonus\n");
    int32_t front_index;
    printf("\n===Example===\n");
    printf("This is a%nn apple\n",&front_index);

    printf("\nTruncated string: This is a\n");
    printf("String length: %d\n",front_index);//front_index = 9
    return 0;
}