#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{   
    char *string = malloc(4096);
    char *keyword = malloc(64);
    char *new = malloc(64);
    printf("$ ./hw0102\n");
    printf("Please enter the string: ");
    fgets(string,4096,stdin);
    printf("Please enter the keyword: ");
    fgets(keyword,64,stdin);
    printf("Please enter the new word: ");
    fgets(new,64,stdin);
    int32_t len_string = strlen(string)-1;
    int32_t len_keyword = strlen(keyword)-1;
    int32_t len_new = strlen(new)-1;
    int32_t len_record = 0;
    int32_t record[4096];
    for(int i=0;i<len_string;i++)
    {
        for(int j=0;j<len_keyword;j++)
        {
            if(string[i+j]!=keyword[j]&&abs(string[i+j]-keyword[j])!=32)
            {
                break;
            }
            if(j==len_keyword-1)
            {
                record[len_record] = i;
                len_record++;
            }
        }
    }
    printf("Original: \n");
    
    for (int i=0,count=0;i<len_string;i++)
    {
        if(record[count]==i)
        {
            for(int j=0;j<len_keyword;j++)
            {
                printf("\033[35;1m%c\033[m", string[i+j]);
            }
            count++;
            i+=len_keyword-1;
        }
        else
        {
            printf("%c", string[i]);
        }
    }

    printf("\nNew: \n");
    for (int i=0,count=0;i<len_string;i++)
    {
        if(record[count]==i&&len_record!=0)
        {
            for(int j=0;j<len_new;j++)
            {
                printf("\033[35;1m%c\033[m", new[j]);
            }
            count++;
            i+=len_keyword-1;
        }
        else
        {
            printf("%c", string[i]);
        }
    }
    printf("\n");
    free(string);
    free(keyword);
    free(new);
    return 0;
}