#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "bible.txt"
#define MAX_LEN 1000
#define JSON_SIZE 3

typedef struct _json_data
{
    int32_t cheaper;
    int32_t verse;
    char *text;
    char *book_id;
}JSON_DATA;

void read_json(char *source, JSON_DATA *data);
int8_t match(char *source, char* target);

int main()
{
    int32_t times=0;
    char *input = malloc(MAX_LEN);
    char *target = malloc(MAX_LEN);
    JSON_DATA **founded = (JSON_DATA**)malloc(MAX_LEN);
    
    printf("Please enter the search target: ");
    fgets(target,MAX_LEN,stdin);
    target[strlen(target)-1] = (target[strlen(target)-1]=='\n') ? 0 : target[strlen(target)-1];
    
    FILE *file = fopen(FILE_NAME, "r");
    if(file==NULL)
    {
        printf("File doesn't exist!!\n");
        return 0;
    }
    
    while(!feof(file))
    {   
        JSON_DATA data;
        fgets(input,MAX_LEN,file);
        read_json(input,&data);
        if(match(data.text,target))
        {
            founded[times] = &data;
            times++;
        }
    }
    printf("Found %d time(s)\n",times);
    for(int i=0; i<times; i++)
    {
        printf("%d. %s %d:%d %s\n",i+1,founded[i]->book_id,founded[i]->cheaper,founded[i]->verse,founded[i]->text);
    }

    fclose(file);
    free(input);
    free(founded);
    free(target);
    return 0;
}

void read_json(char *source, JSON_DATA *data)
{
    char *match = "\"";   
    char *token = strtok(source,match);
    for(int i = 0; token!=NULL; i++)
    {
        // printf("%d: %s\n",i,token); //show json elements index of numbers
        if(i==2) //cheapter's element:int
        {
            data->cheaper = atoi(token+1);
        }
        else if(i==4) //verse's element:int
        {
            data->verse = atoi(token+1);
        }
        else if(i==7) //text's element:char*
        {
            data->text = token;
        }
        else if(i==15) //book_id's element:char*
        {
            data->book_id = token;
        }
        token = strtok(NULL,match);
    }
}

int8_t match(char *source, char* target)
{
    int32_t len_target = strlen(target);
    for(int i=0;source[i];i++)
    {
        for(int j=0;target[j];j++)
        {
            if(source[i+j]!=target[j])
            {
                break;
            }
            if(j>=len_target-1)
            {
                return 1;
            }
        }
    }
    return 0;
}