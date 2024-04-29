#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define MAX_LEN 500

typedef struct _srt
{
    double start;
    double end;
    char *text;
}SRT;

void analysis_srt(FILE **file,SRT **data,int32_t *size,double speed)
{
    char *input = malloc(MAX_LEN);
    char *token_match = ":, ->";
    for(int i=0;!feof(*file);i++)
    {   
        fgets(input,MAX_LEN,*file);
        if(i%4==1) //get play time
        {
            *data = realloc(*data,(*size+1)*sizeof(SRT));
            (*data)[*size] = (SRT){
                .start = 0,
                .end = 0,
                .text = NULL
            };
            char *token = strtok(input,token_match);
            for(int j = 0; token!=NULL; j++,token = strtok(NULL,token_match))
            {
                if(j==0) //start hour
                {
                    (*data)[*size].start += 60*60*1000*atoi(token);
                }
                else if(j==1) //start minute
                {
                    (*data)[*size].start += 60*1000*atoi(token);
                }
                else if(j==2) //start second
                {
                    (*data)[*size].start += 1000*atoi(token);
                }
                else if(j==3) //start millisecond
                {
                    (*data)[*size].start += atoi(token);
                }
                else if(j==4) //end hour
                {
                    (*data)[*size].end += 60*60*1000*atoi(token);
                }
                else if(j==5) //end minute
                {
                    (*data)[*size].end += 60*1000*atoi(token);
                }
                else if(j==6) //end second
                {
                    (*data)[*size].end += 1000*atoi(token);
                }
                else if(j==7) //end millisecond
                {
                    (*data)[*size].end += atoi(token);
                }
            }
            (*data)[*size].start /= speed;
            (*data)[*size].end /= speed;
            
        }
        else if(i%4==2) //get srt
        {
            
            (*data)[*size].text = malloc(strlen(input)+1);
            strncpy((*data)[*size].text,input,strlen(input));
            *size+=1;
        }   
    }
    free(input);   
}

void play_srt(SRT **data,int32_t size,double speed)
{
    uint64_t last = 0;
    for (int i = 0; i < size; i++)
    {
        system("clear");
        usleep(((*data)[i].start-last)*1000);
        last = (*data)[i].start;
        puts((*data)[i].text);
        usleep(((*data)[i].end-last)*1000);
        last = (*data)[i].end;   
    }
}

int main()
{
    char *filename = malloc(MAX_LEN);
    int32_t size = 0;
    double speed = 0;
    SRT *data=NULL;
    printf("Open a srt file: ");
    fgets(filename,MAX_LEN,stdin);
    filename[strlen(filename)-1] = (filename[strlen(filename)-1]=='\n') ? 0 : filename[strlen(filename)-1];
    FILE *file = fopen(filename,"r");
    if(file==NULL)
    {
        printf("File doesn't exist!!\n");
        return 0;
    }
    printf("Speed (0.5-2): ");
    scanf("%lf",&speed);
    if(speed<0.5||speed>2)
    {
        printf("Invalid input!!\n");
        return 0;
    }
    analysis_srt(&file,&data,&size,speed);
    play_srt(&data,size,speed);
    fclose(file);
    return 0;
}