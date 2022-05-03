#pragma once
#include "cstd.h"
#include "utils.h"

void read_text_file(char **dest,char *filename) // TODO: array init
{
    FILE *file = fopen(filename, "rb");
    CHECK_VALID(file!=NULL,"File is not exist!");
    fseek(file, 0, SEEK_END);
    uint64_t file_size = ftell(file);
    rewind(file);
    *dest = (char*)calloc(file_size + 1,sizeof(char*));
    fread(*dest, file_size, 1, file);
    fclose(file);
}

void write_text_file(char **src,char *filename) // TODO: check array null
{   
    FILE *file = fopen(filename, "w");
    fprintf(file,"%s",*src);
    fclose(file);
}

int32_t read_text_file_2D(char ***dest,char *filename) //TODO: array init
{
    char *text = NULL;
    *dest = (char**)malloc(1);
    read_text_file(&text,filename);
    int32_t count = 0;
    int i=0,s=0;
    for(;text[i];i++)
    {
        if(text[i]=='\n')
        {   
            *dest = (char**)realloc(*dest,sizeof(char**)*(count+1));
            (*dest)[count] = (char*)calloc(i-s+2,sizeof(char*)); 
            strncpy((*dest)[count],text+s,i-s+1);
            count++;
            s = i+1;
        }
    }
    *dest = (char**)realloc(*dest,sizeof(char**)*(count+1));
    (*dest)[count] = (char*)calloc(i-s+2,sizeof(char*)); 
    strncpy((*dest)[count],text+s,i-s+1);
    count++;
    return count;
}

void write_text_file_2D(char ***src,char *filename,int32_t count) // TODO: check array null
{   
    FILE *file = fopen(filename, "w");
    for(int i=0;i<count;i++)
    {
        fprintf(file,"%s",(*src)[i]);
    }
    fclose(file);
}