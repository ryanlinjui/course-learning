#include <string.h>
#include <stdio.h>

typedef char* string;

int main()
{
    string str = strdup("abc123 abc456 abc789");

    string match = " ";
    string token = strtok(str, match);
    for(int i = 0; token != NULL; i++)
    {
        printf("%d: %s\n", i, token);
        token = strtok(NULL, match);
    }
    return 0;
}
