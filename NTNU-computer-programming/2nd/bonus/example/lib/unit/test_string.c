#include "../cstd.h"
#include "../string.h"

void test_find()
{
    char *str = "abasdasdcas";
    uint32_t count = 0;
    uint32_t *index = NULL;
    count = str_find(str, "asdasdas",&index);
    printf("count = %d\n",count);
    for(int i = 0; i < count; i++)
    {
        printf("index[%d]: %u\n",i,index[i]);
    }
}

void test_insert()
{
    char *str = calloc(1000,sizeof(char));
    str[0] = 'a';
    str[1] = 'f';
    str_insert(&str, "nn",1);
    puts(str);
}

void test_replace()
{
    char *str = calloc(1000,sizeof(char));
    str[0] = 'c';
    str[1] = 'b';
    str[2] = 'a';
    str[3] = 'c';
    str[4] = 'b';
    str_replace(&str, "ac","");
    puts(str);
}

void test_to_lower()
{
    char *str = calloc(1000,sizeof(char));
    str_copy(str,"ABqwdC990");
    str_to_lower(str);
    puts(str);
}

int main()
{
    test_replace();
    return 0;
}