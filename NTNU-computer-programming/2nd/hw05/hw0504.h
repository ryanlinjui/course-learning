#pragma once

#include "lib/cstd.h"
#include "lib/string.h"

#define GET_WAV_CMD "curl -o out.wav \'https://hapsing.ithuan.tw/bangtsam?taibun="
#define MAX_LEN 1000

void generate_tone(char *src,char *result)
{
    char *src_copy = calloc(strlen(src)+10,sizeof(char));
    str_copy_(src_copy,src);
    char *match = "- ";   
    char *token = strtok(src_copy,match);
    while(token!=NULL)
    {
        if(token[strlen(token)-1]!='.')
        {
            if(token[strlen(token)-1]=='1')
            {
                token[strlen(token)-1] = '7';
            }
            else if(token[strlen(token)-1]=='2')
            {
                token[strlen(token)-1] = '1';
            }
            else if(token[strlen(token)-1]=='4' && (token[strlen(token)-2]=='p'||token[strlen(token)-2]=='t'||token[strlen(token)-2]=='k'))
            {
                token[strlen(token)-1] = '8';
            }
            else if(token[strlen(token)-1]=='4' && token[strlen(token)-2]=='h')
            {
                token[strlen(token)-1] = '2';
            }
            else if(token[strlen(token)-1]=='5')
            {
                token[strlen(token)-1] = '7';
            }
            else if(token[strlen(token)-1]=='2')
            {
                token[strlen(token)-1] = '1';
            }
            else if(token[strlen(token)-1]=='7')
            {
                token[strlen(token)-1] = '3';
            }
            else if(token[strlen(token)-1]=='8' && (token[strlen(token)-2]=='p'||token[strlen(token)-2]=='t'||token[strlen(token)-2]=='k'))
            {
                token[strlen(token)-1] = '4';
            }
            else if(token[strlen(token)-1]=='8' && token[strlen(token)-2]=='h')
            {
                token[strlen(token)-1] = '3';
            }
        }
        str_insert(&result,token,strlen(result));
        if(token[strlen(token)-1]!='.') 
        {
            str_insert(&result,". ",strlen(result));
        }
        else
        {
            str_insert(&result," ",strlen(result));
        }
        token = strtok(NULL,match);
    }
    str_insert(&result,src,strlen(result));
}

void generate_wav(char *src)
{  
    str_replace(&src," ","+");
    char *cmd = calloc(MAX_LEN,sizeof(char));
    strncpy(cmd,GET_WAV_CMD,strlen(GET_WAV_CMD));
    strncpy(cmd+strlen(GET_WAV_CMD),src,strlen(src));
    strncpy(cmd+strlen(cmd),"\'",strlen("\'"));
    system(cmd);
}